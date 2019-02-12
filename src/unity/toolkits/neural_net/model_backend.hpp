/* Copyright © 2018 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef UNITY_TOOLKITS_NEURAL_NET_MODEL_BACKEND_HPP_
#define UNITY_TOOLKITS_NEURAL_NET_MODEL_BACKEND_HPP_

#include <memory>
#include <string>
#include <vector>

#include <unity/toolkits/neural_net/float_array.hpp>

namespace turi {
namespace neural_net {

/**
 * A pure virtual interface for neural networks, used to abstract across model
 * architectures and backend implementations.
 */
class model_backend {
public:

  virtual ~model_backend() = default;

  /**
   * Sets the learning rate to be used for future calls to train.
   */
  virtual void set_learning_rate(float lr) = 0;

  /**
   * Performs one forward-backward pass.
   */
  virtual deferred_float_array train(const float_array& input_batch,
                                     const float_array& label_batch) = 0;

  /**
   * Performs a forward pass.
   */
  virtual deferred_float_array predict(
      const float_array& input_batch) const = 0;

  /**
   * Exports the network weights.
   *
   * \todo Someday, once no Python frontend depends on this method, this could
   *       just take a mutable model_spec (updating the one used to initialize
   *       the model_backend).
   */
  virtual float_array_map export_weights() const = 0;
};

}  // namespace neural_net
}  // namespace turi

#endif  // UNITY_TOOLKITS_NEURAL_NET_MODEL_BACKEND_HPP_
