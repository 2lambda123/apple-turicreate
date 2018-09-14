#import "mps_graph_trainer.h"

#include <tuple>

#include "mps_float_array.hpp"

#import "mps_device_manager.h"
#import "mps_graph_cnnmodule.h"

using turi::mps::MPSGraphModule;
using turi::mps::float_array;
using turi::mps::float_array_map;
using turi::mps::make_array_map;

int TCMPSHasHighPowerMetalDevice(bool *has_device) {
  API_BEGIN();
  if (has_device) {
    id <MTLDevice> dev = [[TCMPSDeviceManager sharedInstance] preferredDevice];
    *has_device = ((dev != nil) && (!dev.isLowPower));
  }
  API_END();
}

int TCMPSMetalDeviceName(char *name, int max_len) {
  API_BEGIN();
  id <MTLDevice> dev = [[TCMPSDeviceManager sharedInstance] preferredDevice];
  if (dev == nil) {
    return 1;
  }
  strlcpy(name, [dev.name cStringUsingEncoding:NSUTF8StringEncoding], max_len);
  API_END();
}

int TCMPSMetalDeviceMemoryLimit(uint64_t *size) {
  API_BEGIN();

  id <MTLDevice> dev = [[TCMPSDeviceManager sharedInstance] preferredDevice];
  if (dev == nil) {
    return 1;
  }

  *size = dev.recommendedMaxWorkingSetSize;

  API_END();
}

int TCMPSCreateGraphModule(MPSHandle *out) {
  API_BEGIN();
  MPSGraphModule *mps = new MPSGraphModule();
  *out = (void *)mps;
  API_END();
}

int TCMPSDeleteGraphModule(MPSHandle handle) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  delete obj;
  API_END();
}

int TCMPSStartTrainingBatchGraph(
    MPSHandle handle, TCMPSFloatArrayRef inputs, TCMPSFloatArrayRef labels) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  float_array* inputs_ptr = reinterpret_cast<float_array*>(inputs);
  float_array* labels_ptr = reinterpret_cast<float_array*>(labels);
  obj->StartTrainingBatch(*inputs_ptr, *labels_ptr);
  API_END();
}

int TCMPSWaitForTrainingBatchGraph(MPSHandle handle, float *loss) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  obj->WaitForTrainingBatch(loss);
  API_END();
}

int TCMPSStartInferenceBatchGraph(MPSHandle handle, TCMPSFloatArrayRef inputs) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  float_array* inputs_ptr = reinterpret_cast<float_array*>(inputs);
  obj->StartInferenceBatch(*inputs_ptr);
  API_END();
}

int TCMPSWaitForInferenceBatchGraph(MPSHandle handle, float *out_ptr) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  obj->WaitForInferenceBatch(out_ptr);
  API_END();
}

int TCMPSStartTrainReturnGradBatchGraph(
    MPSHandle handle, TCMPSFloatArrayRef inputs, TCMPSFloatArrayRef gradient) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  float_array* inputs_ptr = reinterpret_cast<float_array*>(inputs);
  float_array* gradient_ptr = reinterpret_cast<float_array*>(gradient);
  obj->StartTrainReturnGradBatch(*inputs_ptr, *gradient_ptr);
  API_END();
}

int TCMPSWaitForTrainReturnGradBatchGraph(MPSHandle handle, float *out_ptr) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  obj->WaitForTrainReturnGradBatch(out_ptr);
  API_END();
}

int TCMPSInitGraph(MPSHandle handle, int network_id, int n, int c_in, int h_in, int w_in,
              int c_out, int h_out, int w_out,
              char **config_names, void **config_arrays,
              int64_t *config_sizes, int config_len,
              char **weight_names, void **weight_arrays,
              int64_t *weight_sizes, int weight_len) {
  API_BEGIN();
  
  float_array_map config =
      make_array_map(config_names, config_arrays, config_sizes, config_len);
  float_array_map weights =
      make_array_map(weight_names, weight_arrays, weight_sizes, weight_len);

  MPSGraphModule *obj = (MPSGraphModule *)handle;
  obj->Init(network_id, n, c_in, h_in, w_in, c_out, h_out, w_out,
            config, weights);
  API_END();
}

int TCMPSNumParamsGraph(MPSHandle handle, int *num) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  *num = obj->NumParams();
  API_END();
}

int TCMPSExportGraph(MPSHandle handle, char **names, void **arrs, int64_t *dim,
           int **shape) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  obj->Export();
  auto &table = obj->table_;
  int cnt = 0;
  for (auto &p : table) {
    names[cnt] = (char *)std::get<0>(p.second).c_str();
    arrs[cnt] = (void *)std::get<1>(p.second);
    dim[cnt] = std::get<2>(p.second);
    shape[cnt++] = &(std::get<3>(p.second)[0]);
  }
  API_END();
}

int TCMPSSetLearningRateGraph(MPSHandle handle, float new_lr) {
  API_BEGIN();
  MPSGraphModule *obj = (MPSGraphModule *)handle;
  obj->SetLearningRate(new_lr);
  API_END();
}
