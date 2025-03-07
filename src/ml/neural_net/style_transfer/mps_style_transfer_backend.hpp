/* Copyright © 2019 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at
 * https://opensource.org/licenses/BSD-3-Clause
 */

#pragma once

#include <functional>
#include <map>
#include <memory>

#include <core/export.hpp>
#include <ml/neural_net/float_array.hpp>
#include <ml/neural_net/model_backend.hpp>
#include <ml/neural_net/mps_command_queue.hpp>

#ifdef HAS_MACOS_10_15

namespace turi {
namespace style_transfer {

class EXPORT mps_style_transfer : public turi::neural_net::model_backend {
public:
  mps_style_transfer(const turi::neural_net::float_array_map &config,
                     const turi::neural_net::float_array_map &weights);

  mps_style_transfer(const turi::neural_net::float_array_map &config,
                     const turi::neural_net::float_array_map &weights,
                     const turi::neural_net::mps_command_queue& command_queue);

  ~mps_style_transfer();

  turi::neural_net::float_array_map export_weights() const override;
  turi::neural_net::float_array_map predict(const turi::neural_net::float_array_map& inputs) const override;
  void set_learning_rate(float lr) override;
  turi::neural_net::float_array_map train(const turi::neural_net::float_array_map& inputs) override;
private:
  struct impl;
  std::unique_ptr<impl> m_impl;

  void init(const turi::neural_net::float_array_map &config,
            const turi::neural_net::float_array_map &weights,
            const turi::neural_net::mps_command_queue& command_queue);
};

} // namespace style_transfer
} // namespace turi

#endif // #ifdef HAS_MACOS_10_15
