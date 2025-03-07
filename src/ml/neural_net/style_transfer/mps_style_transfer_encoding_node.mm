/* Copyright © 2019 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */

#import <ml/neural_net/style_transfer/mps_style_transfer_encoding_node.h>

#import <ml/neural_net/mps_layer_helper.h>
#import <ml/neural_net/mps_layer_instance_norm_data_loader.h>
#import <ml/neural_net/mps_weight.h>

@interface TCMPSStyleTransferEncodingNode ()
@property (nonatomic) MPSCNNConvolutionNode *conv;
@property (nonatomic) MPSCNNInstanceNormalizationNode* instNorm;
@property (nonatomic) MPSCNNNeuronReLUNode* relu;
@end

@implementation TCMPSStyleTransferEncodingNode

- (instancetype) initWithParameters:(NSString *)name
                          inputNode:(MPSNNImageNode *)inputNode
                             device:(id<MTLDevice>)dev
                           cmdQueue:(id<MTLCommandQueue>)cmdQ
                         descriptor:(TCMPSEncodingDescriptor *)descriptor
                        initWeights:(NSDictionary<NSString *, NSData *> *) weights {
  self = [super init];

  if (self) {
    // No bias
    NSMutableData* zeroedConvBiases = [NSMutableData dataWithLength:descriptor.conv.outputFeatureChannels*sizeof(float)];
    _conv = [MPSCNNConvolutionNode createConvolutional:inputNode
                                           kernelWidth:descriptor.conv.kernelWidth
                                          kernelHeight:descriptor.conv.kernelHeight
                                  inputFeatureChannels:descriptor.conv.inputFeatureChannels
                                 outputFeatureChannels:descriptor.conv.outputFeatureChannels
                                           strideWidth:descriptor.conv.strideWidth
                                          strideHeight:descriptor.conv.strideHeight
                                          paddingWidth:descriptor.conv.paddingWidth
                                         paddingHeight:descriptor.conv.paddingHeight
                                               weights:weights[[NSString stringWithFormat:@"%@%@", name, @"conv_weight"]]
                                                biases:zeroedConvBiases
                                                 label:descriptor.conv.label
                                         updateWeights:descriptor.conv.updateWeights
                                                device:dev
                                              cmdQueue:cmdQ];

    _instNorm = [MPSCNNInstanceNormalizationNode createInstanceNormalization:[_conv resultImage]
                                                                    channels:descriptor.inst.channels
                                                                      styles:descriptor.inst.styles
                                                                       gamma:weights[[NSString stringWithFormat:@"%@%@", name, @"inst_gamma_weight"]]
                                                                        beta:weights[[NSString stringWithFormat:@"%@%@", name, @"inst_beta_weight"]]
                                                                       label:descriptor.inst.label
                                                                      device:dev
                                                                    cmdQueue:cmdQ];

    _relu = [MPSCNNNeuronReLUNode nodeWithSource: [_instNorm resultImage]];

    _output = [_relu resultImage];
  }

  return self;
}

- (MPSNNImageNode *) backwardPass:(MPSNNImageNode *) inputNode {
  MPSNNGradientFilterNode* reluGrad = [_relu gradientFilterWithSource: inputNode];
  MPSNNGradientFilterNode* instNormGrad = [_instNorm gradientFilterWithSource: [reluGrad resultImage]];
  MPSNNGradientFilterNode* convGrad = [_conv gradientFilterWithSource: [instNormGrad resultImage]];

  return [convGrad resultImage];
}

- (void) setStyleIndex:(NSUInteger)styleIndex {
  _instNorm.tc_weightsData.styleIndex = styleIndex;
  [_instNorm.tc_weightsData checkpoint];
}

- (void) setLearningRate:(float)lr {
  [_conv.tc_weightsData setLearningRate:lr];
  [_instNorm.tc_weightsData setLearningRate:lr];
}

- (NSDictionary<NSString *, TCMPSStyleTransferWeights *> *)exportWeights:(NSString *)prefix {
  NSMutableDictionary<NSString *, TCMPSStyleTransferWeights *> *weights = [[NSMutableDictionary alloc] init];

  NSUInteger convWeightSize = (NSUInteger)([_conv.tc_weightsData weightSize] * sizeof(float));
  NSMutableData* convDataWeight = [NSMutableData dataWithLength:convWeightSize];
  memcpy(convDataWeight.mutableBytes, [_conv.tc_weightsData weights], convWeightSize);

  NSString* convWeight = [NSString stringWithFormat:@"%@%@", prefix, @"conv_weight"];

  NSArray<NSNumber *>* convWeightShape = [_conv.tc_weightsData weightShape];

  TCMPSStyleTransferWeights* convWeightWrapper = [[TCMPSStyleTransferWeights alloc] init];

  convWeightWrapper.data = convDataWeight;
  convWeightWrapper.shape = convWeightShape;

  weights[convWeight] = convWeightWrapper;

  NSUInteger instNormSize = (NSUInteger)([_instNorm.tc_weightsData styles] * [_instNorm.tc_weightsData numberOfFeatureChannels] * sizeof(float));
  NSMutableData* instNormDataGamma = [NSMutableData dataWithLength:instNormSize];
  NSMutableData* instNormDataBeta = [NSMutableData dataWithLength:instNormSize];

  memcpy(instNormDataGamma.mutableBytes, [_instNorm.tc_weightsData gammaWeights], instNormSize);
  memcpy(instNormDataBeta.mutableBytes, [_instNorm.tc_weightsData betaWeights], instNormSize);

  NSArray<NSNumber *>* instNormGammaShape = @[@([_instNorm.tc_weightsData styles]), @([_instNorm.tc_weightsData numberOfFeatureChannels])];
  NSArray<NSNumber *>* instNormBetaShape = @[@([_instNorm.tc_weightsData styles]), @([_instNorm.tc_weightsData numberOfFeatureChannels])];

  TCMPSStyleTransferWeights* instNormGammaWrapper = [[TCMPSStyleTransferWeights alloc] init];
  TCMPSStyleTransferWeights* instNormBetaWrapper = [[TCMPSStyleTransferWeights alloc] init];

  instNormGammaWrapper.data = instNormDataGamma;
  instNormGammaWrapper.shape = instNormGammaShape;

  instNormBetaWrapper.data = instNormDataBeta;
  instNormBetaWrapper.shape = instNormBetaShape;

  NSString* instNormGamma = [NSString stringWithFormat:@"%@%@", prefix, @"inst_gamma_weight"];
  NSString* instNormBeta = [NSString stringWithFormat:@"%@%@", prefix, @"inst_beta_weight"];

  weights[instNormGamma] = instNormGammaWrapper;
  weights[instNormBeta] = instNormBetaWrapper;

  return weights;
}

@end
