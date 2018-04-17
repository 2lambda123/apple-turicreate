/* Copyright © 2018 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */
#include <capi/impl/capi_wrapper_structs.hpp>
#include <capi/impl/capi_error_handling.hpp>
#include <capi/impl/capi_initialization_internal.hpp>
#include <unity/lib/unity_global.hpp>

/******************************************************************************/
/*                                                                            */
/*   Models                                                                   */
/*                                                                            */
/******************************************************************************/

struct tc_model_struct; 
typedef struct tc_model_struct tc_model;

EXPORT tc_model* tc_model_new(const char* model_name, tc_error** error) { 
  ERROR_HANDLE_START();
  turi::ensure_server_initialized();
  turi::ensure_server_initialized();

  std::shared_ptr<turi::model_base> model 
    = turi::get_unity_global_singleton()->create_toolkit_class(model_name); 

  return new_tc_model(std::move(model));

  ERROR_HANDLE_END(error, NULL);
}

EXPORT tc_model* tc_model_load(const char* url, tc_error** error) {
  ERROR_HANDLE_START();
  turi::ensure_server_initialized();
  CHECK_NOT_NULL(error, url, "url", nullptr);

  turi::variant_map_type result =
      turi::get_unity_global_singleton()->load_model(url);
  turi::flex_int version =
      turi::safe_varmap_get<turi::flexible_type>(result, "archive_version");
  switch (version) {
  case 0:
    return new_tc_model(
        turi::safe_varmap_get<std::shared_ptr<turi::model_base>>(
            result, "model_base"));
  case 1:
    return new_tc_model(
        turi::safe_varmap_get<std::shared_ptr<turi::model_base>>(
            result, "model"));
  default:
    set_error(error, "Unknown model archive version");
    return nullptr;
  }

  ERROR_HANDLE_END(error, nullptr);
}

EXPORT void tc_model_save(
    const tc_model* model, const char* url, tc_error** error) {
  ERROR_HANDLE_START();
  turi::ensure_server_initialized();
  CHECK_NOT_NULL(error, model, "model");
  CHECK_NOT_NULL(error, url, "url");

  turi::get_unity_global_singleton()->save_model(model->value, {}, url);

  ERROR_HANDLE_END(error);
}

EXPORT const char* tc_model_name(const tc_model* model, tc_error **error) { 
  ERROR_HANDLE_START();
  turi::ensure_server_initialized();

  return model->value->name().c_str();
  ERROR_HANDLE_END(error, "");
}

// Will be changed to
EXPORT tc_variant* tc_model_call_method(const tc_model* model, const char* method,
                                        const tc_parameters* arguments, tc_error** error) {
  
  ERROR_HANDLE_START();
  turi::ensure_server_initialized();

  turi::variant_type result = model->value->call_function(method, arguments->value); 

  return new_tc_variant(result);
  
  ERROR_HANDLE_END(error, NULL);
}

