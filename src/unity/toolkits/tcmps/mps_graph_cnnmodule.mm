#include "mps_graph_cnnmodule.h"

#import "mps_device_manager.h"

NS_ASSUME_NONNULL_BEGIN

// Represents one batch submitted to MPS.
@interface TCMPSGraphModuleBatch : NSObject

- (instancetype)initWithCommandBuffer:(id<MTLCommandBuffer>)commandBuffer;

@property (nonatomic, readonly) id<MTLCommandBuffer> commandBuffer;
@property (nonatomic, nullable) MPSImageBatch *input;
@property (nonatomic, nullable) MPSImageBatch *grad;
@property (nonatomic, nullable) MPSCNNLossLabelsBatch *lossState;
@property (nonatomic, nullable) MPSImageBatch *output;

@end

NS_ASSUME_NONNULL_END

@implementation TCMPSGraphModuleBatch

- (instancetype)initWithCommandBuffer:(id<MTLCommandBuffer>)commandBuffer {
  self = [super init];
  if (self) {
    _commandBuffer = commandBuffer;
  }
  return self;
}

@end

namespace turi {
namespace mps {

MPSGraphModule::MPSGraphModule() {
  @autoreleasepool {
    dev_ = [[TCMPSDeviceManager sharedInstance] preferredDevice];
    assert(dev_ && "No valid Metal device. Availability should be checked before creating MPSGraphModule.");
    id<MTLCommandQueue> cq = [dev_ newCommandQueue];
    assert(cq);
    cmd_queue_ = cq;

#if VERBOSE
    NSLog(@"Selected dev: %@", dev_.name);
#endif

    pending_batches_ = [[NSMutableArray alloc] init];
  }
}

void MPSGraphModule::Init(int network_id, int n, int c_in, int h_in, int w_in,
                          int c_out, int h_out, int w_out,
                          const float_array_map& config,
                          const float_array_map& weights) {
  @autoreleasepool {
    mode_ = (GraphMode)get_array_map_scalar(config, "mode", kGraphModeTrainReturnGrad);
    
    input_desc_ = [MPSImageDescriptor
        imageDescriptorWithChannelFormat:MPSImageFeatureChannelFormatFloat32
                                   width:w_in
                                  height:h_in
                         featureChannels:c_in
                          numberOfImages:1
                                   usage:MTLTextureUsageShaderWrite |
                                         MTLTextureUsageShaderRead];
    output_desc_ = [MPSImageDescriptor
        imageDescriptorWithChannelFormat:MPSImageFeatureChannelFormatFloat32
                                   width:w_out
                                  height:h_out
                         featureChannels:c_out
                          numberOfImages:1
                                   usage:MTLTextureUsageShaderWrite |
                                         MTLTextureUsageShaderRead];

    network_ = createNetworkGraph((GraphNetworkType)network_id, {n, h_in, w_in, c_in, h_out, w_out, c_out}, config);
    network_->batch_size = n;
    network_->Init(dev_, cmd_queue_, mode_, config, weights);
  }
}

void MPSGraphModule::StartTrainingBatch(const float_array& input_batch,
                                        const float_array& label_batch) {
  @autoreleasepool {

  assert(mode_ == kGraphModeTrain);

  id<MTLCommandBuffer> cb = [cmd_queue_ commandBuffer];
  TCMPSGraphModuleBatch *batch = [[TCMPSGraphModuleBatch alloc] initWithCommandBuffer:cb];

  // Copy from raw C inputs to MPS images and loss labels.
  batch.input = CopyInput(input_batch);
  batch.lossState = CopyLabels(label_batch);

  // Encode the forward-backward pass.
  batch.output = network_->RunGraph(cb, batch.input, batch.lossState);

  // Schedule synchronization of the loss from GPU to CPU.
  for (MPSCNNLossLabels *lossState in batch.lossState) {
    [lossState synchronizeOnCommandBuffer:cb];
  }

  // Dispatch this batch to MPS.
  [cb commit];
  [pending_batches_ addObject:batch];

  }  // @autoreleasepool
}

void MPSGraphModule::WaitForTrainingBatch(float *loss) {
  @autoreleasepool {

  assert(mode_ == kGraphModeTrain);
  assert(pending_batches_.count > 0);

  TCMPSGraphModuleBatch *batch = pending_batches_[0];
  [pending_batches_ removeObjectAtIndex:0];

  // Wait until this batch's command buffer has finished executing.
  [batch.commandBuffer waitUntilCompleted];

  // Copy out the loss data and compute the scalar loss for each training
  // instance.
  float *loss_ptr = loss;
  for (MPSCNNLossLabels *lossState in batch.lossState) {
    *loss_ptr = sumImage([lossState lossImage]);
    ++loss_ptr;
  }

  // Recycle the MPSImage instances used for inputs.
  recycled_input_ = batch.input;

  }  // @autoreleasepool
}

void MPSGraphModule::StartInferenceBatch(const float_array& input_batch) {
  @autoreleasepool {

  assert(mode_ == kGraphModeInference);

  id<MTLCommandBuffer> cb = [cmd_queue_ commandBuffer];
  TCMPSGraphModuleBatch *batch = [[TCMPSGraphModuleBatch alloc] initWithCommandBuffer:cb];

  // Copy from raw C inputs to MPS images. Encode the forward pass.
  batch.input = CopyInput(input_batch);
  batch.output = network_->RunGraph(cb, @{@"input" : batch.input});

  // Schedule synchronization of the output from GPU to CPU.
  for (MPSImage *image in batch.output) {
    [image synchronizeOnCommandBuffer:cb];
  }

  // Dispatch this batch to MPS.
  [cb commit];
  [pending_batches_ addObject:batch];

  }  // @autoreleasepool
}

void MPSGraphModule::WaitForInferenceBatch(float *out_ptr) {
  @autoreleasepool {

  assert(mode_ == kGraphModeInference);
  assert(pending_batches_.count > 0);

  TCMPSGraphModuleBatch *batch = pending_batches_[0];
  [pending_batches_ removeObjectAtIndex:0];

  // Wait until this batch's command buffer has finished executing.
  [batch.commandBuffer waitUntilCompleted];

  // Copy out the results.
  MPSImage2Blob(out_ptr, batch.output);

  // Recycle the MPSImage instances used for inputs.
  recycled_input_ = batch.input;

  }  // @autoreleasepool
}

void MPSGraphModule::StartTrainReturnGradBatch(
    const float_array& input_batch, const float_array& gradient_batch) {
  @autoreleasepool {

  assert(mode_ == kGraphModeTrainReturnGrad);

  id<MTLCommandBuffer> cb = [cmd_queue_ commandBuffer];
  TCMPSGraphModuleBatch *batch = [[TCMPSGraphModuleBatch alloc] initWithCommandBuffer:cb];

  // Copy from raw C inputs to MPS images. Encode the forward-backward pass.
  batch.input = CopyInput(input_batch);
  batch.grad = CopyGrad(gradient_batch);
  batch.output = network_->RunGraph(cb, @{@"input" : batch.input,
                                          @"grad"  : batch.grad   });

  // Schedule synchronization of the output from GPU to CPU.
  for (MPSImage *image in batch.output) {
    [image synchronizeOnCommandBuffer:cb];
  }

  // Dispatch this batch to MPS.
  [cb commit];
  [pending_batches_ addObject:batch];

  }  // @autoreleasepool
}

void MPSGraphModule::WaitForTrainReturnGradBatch(float *out_ptr) {
  @autoreleasepool {

  assert(mode_ == kGraphModeTrainReturnGrad);
  assert(pending_batches_.count > 0);

  TCMPSGraphModuleBatch *batch = pending_batches_[0];
  [pending_batches_ removeObjectAtIndex:0];

  // Wait until this batch's command buffer has finished executing.
  [batch.commandBuffer waitUntilCompleted];

  // Copy out the results.
  MPSImage2Blob(out_ptr, batch.output);

  // Recycle the MPSImage instances used for inputs.
  recycled_input_ = batch.input;
  recycled_grad_ = batch.grad;

  }  // @autoreleasepool
}

float_array_map MPSGraphModule::Export() const {
  @autoreleasepool {
    return network_->Export();
  }
}

int MPSGraphModule::NumParams() { return network_->NumParams(); }

void MPSGraphModule::SetLearningRate(float lr) {
  @autoreleasepool {
    for (int i = 0; i < network_->layers.size(); ++i) {
      network_->layers[i]->SetLearningRate(lr);
    }
  }
}

MPSImageBatch *MPSGraphModule::CreateImageBatch(MPSImageDescriptor *desc) {
  NSUInteger batchSize = (NSUInteger)network_->batch_size;
  NSMutableArray<MPSImage *> *result = [[NSMutableArray alloc] initWithCapacity:batchSize];
  for (NSUInteger i = 0; i < batchSize; ++i) {
    [result addObject:[[MPSImage alloc] initWithDevice:dev_ imageDescriptor:desc]];
  }
  return [result copy];
}

MPSImageBatch *MPSGraphModule::CopyInput(const float_array& input) {
  @autoreleasepool {
    // may check shape

    // Use a recycled MPSImageBatch if available.
    MPSImageBatch *batch = recycled_input_;
    recycled_input_ = nil;
    if (!batch) {
      // Allocate a new MPSImageBatch if necessary.
      batch = CreateImageBatch(input_desc_);
    }
    Blob2MPSImage(input, batch);
    return batch;
  }
}

MPSImageBatch *MPSGraphModule::CopyGrad(const float_array& gradient) {
  @autoreleasepool {
    // may check shape

    // Use a recycled MPSImageBatch if available.
    MPSImageBatch *batch = recycled_grad_;
    recycled_grad_ = nil;
    if (!batch) {
      // Allocate a new MPSImageBatch if necessary.
      batch = CreateImageBatch(output_desc_);
    }
    Blob2MPSImage(gradient, batch);
    return batch;
  }
}

MPSCNNLossLabelsBatch *MPSGraphModule::CopyLabels(const float_array& labels) {
  @autoreleasepool {
    return network_->loss_layer_->CreateLossState(dev_, labels);
  }
}

void MPSGraphModule::Blob2MPSImage(const float_array& blob,
                                   MPSImageBatch *batch) {
  // add size chcek later
  assert([batch count] > 0);
  const float* ptr = blob.data();
  MPSImage *img = batch[0];
  int stride = [img width] * [img height] * [img featureChannels];
  for (int i = 0; i < [batch count]; ++i) {
    MPSImage *img = batch[i];
    [img writeBytes:ptr + stride * i
         dataLayout:(MPSDataLayoutHeightxWidthxFeatureChannels)imageIndex:0];
  }
}

void MPSGraphModule::MPSImage2Blob(float *ptr, MPSImageBatch *batch) {
  // add size chcek later
  assert([batch count] > 0);
  __fp16 *dptr = (__fp16 *)ptr;
  MPSImage *img = batch[0];
  int stride = [img width] * [img height] * [img featureChannels];
  for (int i = 0; i < [batch count]; ++i) {
    MPSImage *img = batch[i];
    [img readBytes:dptr + stride * i
        dataLayout:(MPSDataLayoutHeightxWidthxFeatureChannels)imageIndex:0];
  }
}

}  // namespace mps
}  // namespace turi
