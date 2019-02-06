/* Copyright © 2017 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef TURI_DRAWING_REGISTRATION_H_
#define TURI_DRAWING_REGISTRATION_H_

//#include <unity/lib/toolkit_class_macros.hpp>
#include <unity/lib/toolkit_function_macros.hpp>

namespace turi {
namespace sdk_model {
namespace drawing_recognition {

//std::vector<turi::toolkit_class_specification> get_toolkit_class_registration();
std::vector<toolkit_function_specification> get_toolkit_function_registration();

}// drawing_recognition
}// sdk_model
}// turicreate

#endif
