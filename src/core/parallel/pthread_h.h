/* Copyright © 2017 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef TURI_PARALLEL_PTHREAD_INDIRECT_INCLUDE_HPP
#define TURI_PARALLEL_PTHREAD_INDIRECT_INCLUDE_HPP
#ifdef _WIN32
#include <core/parallel/winpthreadsll.h>
#else
#include <pthread.h>
#endif
#endif
