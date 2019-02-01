/* Copyright © 2017 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */

#include <pch/pch.hpp>

#ifndef TURI_SYSERR_REPORTING_H_
#define TURI_SYSERR_REPORTING_H_

/**
 * \ingroup util
 * Portable version of strerror
 */
std::string get_last_err_str(unsigned err_code);

#endif //TURI_SYSERR_REPORTING_H_
