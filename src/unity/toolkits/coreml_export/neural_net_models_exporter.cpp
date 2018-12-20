/* Copyright © 2018 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */

#include <unity/toolkits/coreml_export/neural_net_models_exporter.hpp>

#include <logger/assertions.hpp>
#include <unity/toolkits/coreml_export/mlmodel_include.hpp>


using CoreML::Specification::ArrayFeatureType;
using CoreML::Specification::FeatureDescription;
using CoreML::Specification::ImageFeatureType;
using CoreML::Specification::ModelDescription;
using CoreML::Specification::NeuralNetworkLayer;
using turi::coreml::MLModelWrapper;

  
namespace turi {

void featuretype_c(FeatureDescription* feature_desc, std::string feature_name, 
    size_t num_predictions, size_t num_classes, bool include_shape, bool include_bounds) {
  feature_desc->set_name(feature_name);
  size_t bound;
  if (feature_name.find("confidence") != std::string::npos) {
    bound = 6;
    if (feature_name.find("raw") == std::string::npos) {
      feature_desc->set_shortdescription(
      "Boxes × Class confidence (see user-defined metadata \"classes\")");
    }
  }
  if (feature_name.find("coordinates") != std::string::npos) {
    bound = 4;
    if (feature_name.find("raw") == std::string::npos) {
      feature_desc->set_shortdescription(
      "Boxes × [x, y, width, height] (relative to image size)");
    }
  }
  ArrayFeatureType* feature_desc_feature =
      feature_desc->mutable_type()->mutable_multiarraytype();
  if (include_shape) {
    feature_desc_feature->add_shape(num_predictions);
    feature_desc_feature->add_shape(num_classes);
  }
  feature_desc_feature->set_datatype(ArrayFeatureType::DOUBLE);

  if (include_bounds) {
    auto *shape1 = feature_desc_feature->mutable_shaperange()
        ->add_sizeranges();
    shape1->set_upperbound(-1);
    auto *shape2 = feature_desc_feature->mutable_shaperange()
        ->add_sizeranges();
    shape2->set_lowerbound(bound);
    shape2->set_upperbound(bound);
  }
}

void featuretype_t(FeatureDescription* feature_desc, std::string feature_name, 
    bool include_description) {
  feature_desc->set_name(feature_name);
  if (include_description) {
    if (feature_name.find("iou") != std::string::npos) {
      feature_desc->set_shortdescription("(optional) IOU Threshold override (default: 0.45)");
    } else {
      feature_desc->set_shortdescription("(optional) Confidence Threshold override (default: 0.25)");
    }
  }
  feature_desc->mutable_type()->mutable_doubletype();
}

void featuretype_i(FeatureDescription* feature_desc, size_t image_width, 
    size_t image_height, bool include_description) {
  feature_desc->set_name("image");
  if (include_description)
    feature_desc->set_shortdescription("Input image");
  ImageFeatureType* image_feature =
      feature_desc->mutable_type()->mutable_imagetype();
  image_feature->set_width(image_width);
  image_feature->set_height(image_height);
  image_feature->set_colorspace(ImageFeatureType::RGB);
}

std::shared_ptr<MLModelWrapper> export_object_detector_model(
    const neural_net::model_spec& nn_spec, size_t image_width,
    size_t image_height, size_t num_classes, size_t num_predictions,
    flex_dict user_defined_metadata, flex_list class_labels, 
    std::map<std::string, flexible_type> options) {

  // Set up Pipeline 
  CoreML::Specification::Model model_pipeline;
  model_pipeline.set_specificationversion(3); 
  ModelDescription* pipeline_desc = model_pipeline.mutable_description();

  // Add NeuralNetwork model to pipeline
  auto* model_nn = model_pipeline.mutable_pipeline()->add_models();

  // Scale pixel values 0..255 to [0,1]
  NeuralNetworkLayer* first_layer =
      model_nn->mutable_neuralnetwork()->add_layers();
  first_layer->set_name("_divscalar0");
  first_layer->add_input("image");
  first_layer->add_output("_divscalar0");
  first_layer->mutable_scale()->add_shapescale(1);
  first_layer->mutable_scale()->mutable_scale()->add_floatvalue(1 / 255.f);

  // Copy the NeuralNetwork layers from nn_spec.
  // TODO: This copies ~60MB at present. Should object_detector be responsible
  // for _divscalar0, even though this isn't performed by the cnn_module?
  model_nn->mutable_neuralnetwork()->MergeFrom(nn_spec.get_coreml_spec());
  ASSERT_GT(model_nn->neuralnetwork().layers_size(), 1);

  // Wire up the input layer from the copied layers to _divscalar0.
  // TODO: This assumes that the first copied layer is the (only) one to take
  // the input from "image".
  NeuralNetworkLayer* second_layer = 
      model_nn->mutable_neuralnetwork()->mutable_layers(1);
  ASSERT_EQ(second_layer->input_size(), 1);
  ASSERT_EQ(second_layer->input(0), "image");
  second_layer->set_input(0, "_divscalar0");

  // Write the ModelDescription.
  ModelDescription* model_desc = model_nn->mutable_description();

  // Write FeatureDescription for the image input.
  FeatureDescription* input_image_desc = model_desc->add_input();
  featuretype_i(input_image_desc, image_width, image_height, false);

  if (!options["include_non_maximum_suppression"].to<bool>()){
    
    // Write FeatureDescription for the confidence output.
    FeatureDescription* confidence_desc = model_desc->add_output();
    featuretype_c(confidence_desc, "confidence", num_predictions, num_classes, true, false);

    // Write FeatureDescription for the coordinates output.
    FeatureDescription* output_coordinates_nn = model_desc->add_output();
    featuretype_c(output_coordinates_nn, "coordinates", num_predictions, 4, true, false);

    // Set CoreML spec version.
    model_nn->set_specificationversion(1);
    auto model_wrapper = std::make_shared<MLModelWrapper>(
      std::make_shared<CoreML::Model>(*model_nn));

    // Add metadata.
    model_wrapper->add_metadata({
        { "user_defined", std::move(user_defined_metadata) }
    });

    return model_wrapper;
  }
  
  model_nn->set_specificationversion(3);

  // Write FeatureDescription for the raw confidence output.
  FeatureDescription* output_rconfidence_nn = model_desc->add_output();
  featuretype_c(output_rconfidence_nn, "raw_confidence", num_predictions, num_classes, true, true);

  // Write FeatureDescription for the coordinates output.
  FeatureDescription* output_rcoordinates_nn = model_desc->add_output();
  featuretype_c(output_rcoordinates_nn, "raw_coordinates", num_predictions, 4, true, true);

  // Add Non Maximum Suppression model to pipeline
  auto* model_nms = model_pipeline.mutable_pipeline()->add_models();
  model_nms->set_specificationversion(3);

  ModelDescription* nms_desc = model_nms->mutable_description();

  // Write FeatureDescription for the Raw Confidence input.
  FeatureDescription* input_rconfidence_nms = nms_desc->add_input();
  featuretype_c(input_rconfidence_nms, "raw_confidence", num_predictions, num_classes, true, true);

  // Write FeatureDescription for the Raw Coordinates input.
  FeatureDescription* input_rcoordinates_nms = nms_desc->add_input();
  featuretype_c(input_rcoordinates_nms, "raw_coordinates", num_predictions, 4, true, true);

  // Write FeatureDescription for the IOU Threshold input.
  FeatureDescription* input_iou_nms = nms_desc->add_input();
  featuretype_t(input_iou_nms, "iouThreshold", false);

  // Write FeatureDescription for the Confidence Threshold input.
  FeatureDescription* input_cthreshold_nms = nms_desc->add_input();
  featuretype_t(input_cthreshold_nms, "confidenceThreshold", false);

  // Write FeatureDescription for the Confidence output.
  FeatureDescription* output_confidence_nms = nms_desc->add_output();
  featuretype_c(output_confidence_nms, "confidence", num_predictions, num_classes, false, true);

  // Write FeatureDescription for the Coordinates input.
  FeatureDescription* output_coordinates_nms = nms_desc->add_output();
  featuretype_c(output_coordinates_nms, "coordinates", num_predictions, num_classes, false, true);
  
  CoreML::Specification::NonMaximumSuppression* first_layer_nms =
    model_nms->mutable_nonmaximumsuppression();
  
  // Write Class Labels
  auto* string_class_labels = first_layer_nms->mutable_stringclasslabels(); 
  for (size_t i = 0; i < class_labels.size(); ++i) {
    string_class_labels->add_vector(class_labels[i]);
  }

  //Write Features for Non Maximum Suppression
  first_layer_nms->set_iouthreshold(options["iou_threshold"]);
  first_layer_nms->set_confidencethreshold(options["confidence_threshold"]);
  first_layer_nms->set_confidenceinputfeaturename("raw_confidence");
  first_layer_nms->set_coordinatesinputfeaturename("raw_coordinates");
  first_layer_nms->set_iouthresholdinputfeaturename("iouThreshold");
  first_layer_nms->set_confidencethresholdinputfeaturename("confidenceThreshold");
  first_layer_nms->set_confidenceoutputfeaturename("confidence");
  first_layer_nms->set_coordinatesoutputfeaturename("coordinates");

  // Write FeatureDescription for the image input.
  FeatureDescription* input_image_pipeline = pipeline_desc->add_input();
  featuretype_i(input_image_pipeline, image_width, image_height, true);

  // Write FeatureDescription for the IOU Threshold input.
  FeatureDescription* input_iou_pipeline = pipeline_desc->add_input();
  featuretype_t(input_iou_pipeline, "iouThreshold", true);
  
  // Write FeatureDescription for the Confidence Threshold input.
  FeatureDescription* input_cthreshold_pipeline = pipeline_desc->add_input();
  featuretype_t(input_cthreshold_pipeline, "confidenceThreshold", true);

  // Write FeatureDescription for the Confidence output.
  FeatureDescription* output_confidence_pipeline = pipeline_desc->add_output();
  featuretype_c(output_confidence_pipeline, "confidence", num_predictions, num_classes, false, true);

  // Write FeatureDescription for the Coordinates output.
  FeatureDescription* output_coordinates_pipeline = pipeline_desc->add_output();
  featuretype_c(output_coordinates_pipeline, "coordinates", num_predictions, num_classes, false, true);

  
  // Wrap the pipeline
  auto pipeline_wrapper = std::make_shared<MLModelWrapper>(
    std::make_shared<CoreML::Model>(model_pipeline));
  
  // Add metadata.
  pipeline_wrapper->add_metadata({{ "user_defined", std::move(user_defined_metadata)}});

  return pipeline_wrapper;
}

}  // namespace turi
