/* Copyright © 2018 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */

#ifndef TURI_LOGGINC_ERROR_H_
#define TURI_LOGGINC_ERROR_H_

/*
 * Error types to distinguish Turi Create errors from arbitrary C++ exceptions
 */

#include <ios>
#include <system_error>

namespace turi {
namespace error {

class io_error : public std::ios_base::failure {
  private:
    std::string m_message;

  public:
    explicit io_error(const std::string &message);

  virtual const char *what() const COMPILER_MODIFIER_ON_EXCEPTION_WHAT override;
};

} // namespace error
} // namespace turi

#endif
