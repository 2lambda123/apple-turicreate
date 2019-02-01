#include <pch/pch.hpp>

#ifndef MPS_GRAPH_MODULE_H_
#define MPS_GRAPH_MODULE_H_

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <MetalPerformanceShaders/MetalPerformanceShaders.h>

#include <unity/toolkits/neural_net/cnn_module.hpp>
#include <unity/toolkits/neural_net/float_array.hpp>

#import "mps_utils.h"
#import "mps_graph_networks.h"

NS_ASSUME_NONNULL_BEGIN

namespace turi {
namespace neural_net {

class mps_graph_cnn_module: public cnn_module {
public:

  mps_graph_cnn_module();
  mps_graph_cnn_module(id <MTLDevice> dev);

  void init(int network_id, int n, int c_in, int h_in, int w_in, int c_out,
            int h_out, int w_out,
            const float_array_map& config, const float_array_map& weights);

  // The graph mode used to initialize the module determines which of the
  // following functions are allowed.
  // TODO: Parameters such as graph mode should be more explicit than just a
  // component of the `config` map.

  // Training
  void set_learning_rate(float lr) override;
  deferred_float_array train(const float_array& input_batch,
                             const float_array& label_batch) override;

  // Inference
  deferred_float_array predict(const float_array& input_batch) const override;

  // Forward-backward pass with specified input and top-gradient images
  deferred_float_array train_return_grad(const float_array& input_batch,
                                         const float_array& gradient_batch);

  float_array_map export_weights() const override;

private:
  MPSImageBatch *create_image_batch(MPSImageDescriptor *desc) const;
  MPSImageBatch *copy_input(const float_array& input) const;
  MPSImageBatch *copy_grad(const float_array& gradient) const;
  MPSCNNLossLabelsBatch *copy_labels(const float_array& labels) const;

  id<MTLDevice> dev_;
  id<MTLCommandQueue> cmd_queue_;

  GraphMode mode_;
  std::unique_ptr<MPSGraphNetwork> network_;
  std::vector<size_t> result_shape_;

  MPSImageDescriptor * _Nullable input_desc_ = nil;
  MPSImageDescriptor * _Nullable output_desc_ = nil;

  NSMutableArray<MPSImageBatch *> *recycled_inputs_ = nil;
  NSMutableArray<MPSImageBatch *> *recycled_grads_ = nil;
};

}  // namespace neural_net
}  // namespace turi

NS_ASSUME_NONNULL_END

#endif
