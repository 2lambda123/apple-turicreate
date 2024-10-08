#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include <core/util/test_macros.hpp>
#include <stdlib.h>
#include <vector>
#include <string>
#include <functional>
#include <random>

#include <core/data/sframe/gl_sframe.hpp>
#include <model_server/lib/variant_deep_serialize.hpp>
#include <toolkits/feature_engineering/one_hot_encoder.hpp>
#include <core/storage/sframe_interface/unity_sframe.hpp>

#include <cfenv>

using namespace turi;
using namespace turi::sdk_model::feature_engineering;

/**
 * Generate the data from the model.
 */
gl_sframe generate_data(std::map<std::string, flexible_type> opts) {

  // Create a random SFrame.
  size_t features = opts.at("features");
  size_t examples = opts.at("examples");
  std::vector<std::string> feature_names;
  std::vector<flex_type_enum> feature_types;

  for (size_t i = 0; i < features; i++){
    feature_names.push_back(std::to_string(i));
    feature_types.push_back(flex_type_enum::STRING);
  }

  gl_sframe_writer writer(feature_names, feature_types, 1);
  for(size_t i=0; i < examples; i++){
    std::vector<flexible_type> row (features, std::to_string(i));
    writer.write(row, 0);
  }
  return writer.close();
}


/**
 * Construct a model from data and options.
 */
std::shared_ptr<one_hot_encoder> init_model(gl_sframe data,
                       std::map<std::string, flexible_type> opts) {

  std::shared_ptr<one_hot_encoder> model;
  model.reset(new one_hot_encoder);
  std::map<std::string, flexible_type> options;
  for (const auto& kvp: opts){
    if (kvp.first != "examples" && kvp.first != "features") {
      options[kvp.first] = kvp.second;
    }
  }
  options["features"] = FLEX_UNDEFINED;
  model->init_transformer(options);
  model->fit(data);
  return model;

}

/**
 * Save the model and load it back.
 */
std::shared_ptr<one_hot_encoder> save_and_load_model(
                                std::shared_ptr<one_hot_encoder> model) {

  std::shared_ptr<one_hot_encoder> loaded_model;
  loaded_model.reset(new one_hot_encoder);

  dir_archive archive_write;
  archive_write.open_directory_for_write("one_hot_encoder_tests");
  turi::oarchive oarc(archive_write);
  oarc << *model;
  archive_write.close();

  dir_archive archive_read;
  archive_read.open_directory_for_read("one_hot_encoder_tests");
  turi::iarchive iarc(archive_read);
  iarc >> *loaded_model;
  return loaded_model;
}

/**
 * Save the model and load it back.
 */
void check_model(std::shared_ptr<one_hot_encoder> model,
                 gl_sframe data,
                 std::map<std::string, flexible_type> opts) {

  std::map<std::string, flexible_type> _options;
  std::vector<std::string> _list_fields;
  flexible_type _get;

  // Answers.
  std::map<std::string, flexible_type> default_options = {
    {"output_column_name", "encoded_features"},
    {"max_categories", FLEX_UNDEFINED},
  };
  std::vector<std::string> _list_fields_ans = {
        "excluded_features",
        "max_categories",
        "output_column_name",
        "features",
        "feature_encoding",
  };
  std::map<std::string, flexible_type> options;
  for (const auto& kvp: default_options){
    if (opts.count(kvp.first) == 0) {
      options[kvp.first] = kvp.second;
    } else {
      options[kvp.first] = opts[kvp.first];
    }
  }

  // Check the model
  // ----------------------------------------------------------------------
  TS_ASSERT(data.column_names() == variant_get_value<std::vector<std::string>>(
                            model->get_value_from_state("features")));

  // Check options
  _options = model->get_current_options();
  for (auto& kvp: options){
    TS_ASSERT_EQUALS(_options[kvp.first],  kvp.second);
  }
  TS_ASSERT_EQUALS(_options.size(), options.size());

  // Default options
  _options = model->get_default_options();
  for (auto& kvp: default_options){
    TS_ASSERT_EQUALS(_options[kvp.first],  kvp.second);
  }
  TS_ASSERT_EQUALS(_options.size(), default_options.size());

  // Check list_fields
  _list_fields = model->list_fields();
  for(const auto& f: _list_fields_ans){
    TS_ASSERT(std::find(_list_fields.begin(), _list_fields.end(), f)
                                                    != _list_fields.end());
  }
  TS_ASSERT_EQUALS(_list_fields.size(), _list_fields_ans.size());

  // Check that transformations don't die.
  // ----------------------------------------------------------------------
  gl_sframe out_sf = model->transform(data);
  TS_ASSERT(out_sf.size() == data.size());

  // Uncomment for printing
  //((out_sf.get_proxy())->get_underlying_sframe())->debug_print();
}

void run_one_hot_encoder_test(std::map<std::string, flexible_type> opts) {

  gl_sframe data = generate_data(opts);
  std::shared_ptr<one_hot_encoder> model = init_model(data, opts);
  std::shared_ptr<one_hot_encoder> loaded_model = save_and_load_model(model);
  check_model(model, data, opts);
  check_model(loaded_model, data, opts);
}


/**
 *  Run tests.
*/
struct one_hot_encoder_test  {

  public:

  void test_one_hot_encoder_basic_2d() {
    std::map<std::string, flexible_type> opts = {
      {"examples", 10},
      {"exclude", false},
      {"max_categories", 10000},
      {"features", 1}};
    run_one_hot_encoder_test(opts);
  }

  void test_one_hot_encoder_small() {
    std::map<std::string, flexible_type> opts = {
      {"examples", 100},
      {"exclude", false},
      {"max_categories", 10000},
      {"features", 10}};
    run_one_hot_encoder_test(opts);
  }

  void test_one_hot_encoder_medium() {
    std::map<std::string, flexible_type> opts = {
      {"examples", 10000},
      {"exclude", false},
      {"max_categories", 10000},
      {"features", 10}};
    run_one_hot_encoder_test(opts);
  }

};

BOOST_FIXTURE_TEST_SUITE(_one_hot_encoder_test, one_hot_encoder_test)
BOOST_AUTO_TEST_CASE(test_one_hot_encoder_basic_2d) {
  one_hot_encoder_test::test_one_hot_encoder_basic_2d();
}
BOOST_AUTO_TEST_CASE(test_one_hot_encoder_small) {
  one_hot_encoder_test::test_one_hot_encoder_small();
}
BOOST_AUTO_TEST_CASE(test_one_hot_encoder_medium) {
  one_hot_encoder_test::test_one_hot_encoder_medium();
}
BOOST_AUTO_TEST_SUITE_END()
