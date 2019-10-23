/* Copyright © 2019 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at
 * https://opensource.org/licenses/BSD-3-Clause
 */

#define BOOST_TEST_MODULE

#include <boost/test/unit_test.hpp>
#include <core/util/test_macros.hpp>
#include <toolkits/style_transfer/style_transfer.hpp>

#include <map>
#include <memory>

#include "utils.hpp"

/**
 * Since the only backend is MPS, these tests won't pass on any system other
 * than 10.15.
 */
#ifdef HAS_MACOS_10_15

using namespace turi::style_transfer;


BOOST_AUTO_TEST_CASE(test_init) {
  style_transfer model;

  const size_t NUM_STYLES = 8;

  std::string VGG_16_MODEL_PATH = get_vgg16_model();
  std::string RESNET_MODEL_PATH = get_resnet_model();

  turi::gl_sarray style_sarray = random_image_sarray(NUM_STYLES);
  turi::gl_sarray content_sarray = random_image_sarray(50);

  std::map<std::string, turi::flexible_type> opts = {
    {"resnet_mlmodel_path", RESNET_MODEL_PATH},
    {"vgg_mlmodel_path", VGG_16_MODEL_PATH},
    {"num_styles", NUM_STYLES},
  };

  model.init_train(style_sarray, content_sarray, opts);
}

BOOST_AUTO_TEST_CASE(test_iteration) {
  style_transfer model;

  const size_t NUM_STYLES = 8;

  std::string VGG_16_MODEL_PATH = get_vgg16_model();
  std::string RESNET_MODEL_PATH = get_resnet_model();

  turi::gl_sarray style_sarray = random_image_sarray(NUM_STYLES);
  turi::gl_sarray content_sarray = random_image_sarray(50);

  std::map<std::string, turi::flexible_type> opts = {
    {"resnet_mlmodel_path", RESNET_MODEL_PATH},
    {"vgg_mlmodel_path", VGG_16_MODEL_PATH},
    {"num_styles", NUM_STYLES},
  };

  model.init_train(style_sarray, content_sarray, opts);
  model.iterate_training();
}

BOOST_AUTO_TEST_CASE(test_finalization) {
  style_transfer model;

  const size_t NUM_STYLES = 8;

  std::string VGG_16_MODEL_PATH = get_vgg16_model();
  std::string RESNET_MODEL_PATH = get_resnet_model();

  turi::gl_sarray style_sarray = random_image_sarray(NUM_STYLES);
  turi::gl_sarray content_sarray = random_image_sarray(50);

  std::map<std::string, turi::flexible_type> opts = {
    {"resnet_mlmodel_path", RESNET_MODEL_PATH},
    {"vgg_mlmodel_path", VGG_16_MODEL_PATH},
    {"num_styles", NUM_STYLES},
  };

  model.init_train(style_sarray, content_sarray, opts);

  /**
   * Loop through a couple of iterations to see if we seg-fault
   */
  for (size_t x = 0; x < 100; x++)
    model.iterate_training();
  model.finalize_training();
}



BOOST_AUTO_TEST_CASE(test_train) {
  style_transfer model;

  const size_t NUM_STYLES = 8;

  std::string VGG_16_MODEL_PATH = get_vgg16_model();
  std::string RESNET_MODEL_PATH = get_resnet_model();

  turi::gl_sarray style_sarray = random_image_sarray(NUM_STYLES);
  turi::gl_sarray content_sarray = random_image_sarray(50);

  std::map<std::string, turi::flexible_type> opts = {
    {"resnet_mlmodel_path", RESNET_MODEL_PATH},
    {"vgg_mlmodel_path", VGG_16_MODEL_PATH},
    {"num_styles", NUM_STYLES},
  };

  model.train(style_sarray, content_sarray, opts);
}

// TODO: add more tests for predict
BOOST_AUTO_TEST_CASE(test_predict) {
  TS_ASSERT(true);
}

// TODO: add more tests for export_core_ml
BOOST_AUTO_TEST_CASE(test_export_core_ml) {
  TS_ASSERT(true);
}

#endif