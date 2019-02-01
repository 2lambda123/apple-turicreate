#include <pch/pch.hpp>

#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>
#include <util/test_macros.hpp>
#include <util/cityhash_tc.hpp>

#include <numerics/armadillo.hpp>

// SFrame and Flex type
#include <unity/lib/flex_dict_view.hpp>

// ML-Data Utils
#include <unity/toolkits/ml_data_2/ml_data.hpp>
#include <unity/toolkits/ml_data_2/ml_data_iterators.hpp>
#include <sframe/sframe_iterators.hpp>
#include <unity/toolkits/ml_data_2/ml_data_entry.hpp>
#include <unity/toolkits/ml_data_2/metadata.hpp>
#include <unity/toolkits/ml_data_2/sframe_index_mapping.hpp>

// Testing utils common to all of ml_data
#include <sframe/testing_utils.hpp>
#include <util/testing_utils.hpp>

// Testing utils common to all of ml_data
#include <unity/toolkits/ml_data_2/testing_utils.hpp>

#include <globals/globals.hpp>

using namespace turi;

typedef arma::vec DenseVector;
typedef sparse_vector<double, size_t> SparseVector;

namespace std {

// Define this so we can use unordered sets of vectors.
template<>
struct hash<std::vector<turi::flexible_type> > {
  inline size_t operator()(const std::vector<turi::flexible_type>& s) const {
    size_t h = hash64(s.size());
    for(const turi::flexible_type& f : s)
      h = turi::hash64_combine(h, f.hash());
    return h;
  }
};

}

struct numerics  {

  // Answers
  std::vector<std::shared_ptr<v2::ml_metadata> > metadata_v;
  std::vector<std::vector<flexible_type> > raw_x;
  std::vector<std::vector<flexible_type> > raw_y;
  sframe X;
  sframe y;
  std::vector<v2::ml_data> data_v, saved_data_v;
  std::vector<std::vector<flexible_type> > mapped_x;
  std::vector<size_t> column_size;
  std::vector<std::vector<double>> mean;
  std::vector<std::vector<double>> stdev;

  public:

  numerics() {
    // Int-Double dictionary
    std::vector<std::vector<std::vector<flexible_type>>> raw_int_dbl = \
    {{{0,2.0}},
      {{1,1.0}},
      {{2,1.0}},
      {{2,1.0}, {3,2.0}},
      {{4,1.0}, {5,2.0}},
      {{6,1.0}, {7,2.0}},
      {{2,1.0}, {3,2.0}},
      {{2,2.0}, {5,1.0}},
      {{0,2.0}, {1,1.0}, {2,2.0}},
      {{0,2.0}, {1,1.0}, {3,2.0}}};

    std::vector<std::vector<std::pair<flexible_type,flexible_type>>> int_dbl;
    std::vector<std::vector<std::pair<flexible_type,flexible_type>>> str_dbl;
    for (const auto& row : raw_int_dbl){
      std::vector<std::pair<flexible_type,flexible_type>> m;
      std::vector<std::pair<flexible_type,flexible_type>> str_m;
      for (const auto& entry : row){
        m.push_back(std::make_pair(entry[0],entry[1]));
        str_m.push_back(std::make_pair(std::to_string((size_t)entry[0]),entry[1]));
      }
      int_dbl.push_back(m);
      str_dbl.push_back(str_m);
    }

    // Step 1: Make the raw data.
    // ---------------------------------------------------------------------
    std::vector<std::vector<flexible_type> > raw_x = \
    {{"0",10,10.0, {1.0,10.1}, int_dbl[0], str_dbl[0]},
      {"1",11,21.0, {1.1,21.1}, int_dbl[1], str_dbl[1]},
      {"2",22,22.0, {2.2,22.1}, int_dbl[2], str_dbl[2]},
      {"0",33,23.0, {3.3,23.1}, int_dbl[3], str_dbl[3]},
      {"1",44,24.0, {4.4,24.1}, int_dbl[4], str_dbl[4]},
      {"2",55,25.0, {5.5,25.1}, int_dbl[5], str_dbl[5]},
      {"0",26,26.0, {2.6,26.1}, int_dbl[6], str_dbl[6]},
      {"1",27,27.0, {2.7,27.1}, int_dbl[7], str_dbl[7]},
      {"2",28,28.0, {2.8,28.1}, int_dbl[8], str_dbl[8]},
      {"3",39,49.0, {3.9,49.1}, int_dbl[9], str_dbl[9]} };

    std::vector<std::vector<flexible_type> > mapped_x = \
    {{0,10,10.0, {1.0,10.1}, int_dbl[0], int_dbl[0]},
      {1,11,21.0, {1.1,21.1}, int_dbl[1], int_dbl[1]},
      {2,22,22.0, {2.2,22.1}, int_dbl[2], int_dbl[2]},
      {0,33,23.0, {3.3,23.1}, int_dbl[3], int_dbl[3]},
      {1,44,24.0, {4.4,24.1}, int_dbl[4], int_dbl[4]},
      {2,55,25.0, {5.5,25.1}, int_dbl[5], int_dbl[5]},
      {0,26,26.0, {2.6,26.1}, int_dbl[6], int_dbl[6]},
      {1,27,27.0, {2.7,27.1}, int_dbl[7], int_dbl[7]},
      {2,28,28.0, {2.8,28.1}, int_dbl[8], int_dbl[8]},
      {3,39,49.0, {3.9,49.1}, int_dbl[9], int_dbl[9]} };

    std::vector<std::vector<flexible_type> > raw_y = \
    {{0},
      {1},
      {2},
      {3},
      {4},
      {5},
      {2},
      {2},
      {2},
      {3} };

    std::vector<size_t> column_size = {4,1,1,2,8,8};
    std::vector<std::vector<double>> mean = {{0.3,0.3,0.3,0.1}, {29.5}, {25.5},
      {2.95, 25.6},
      {0.6, 0.3, 0.7, 0.6, 0.1, 0.3, 0.1, 0.2},
      {0.6, 0.3, 0.7, 0.6, 0.1, 0.3, 0.1, 0.2}};

    std::vector<std::vector<double>> stdev
        = {{.48304589153964794,.4830458915396479,.4830458915396479,.31622776601683794},
          {13.994046353122222},{9.675283515799995},
          {1.399404635312222,9.675283515799995},
          {.9660917830792958, .4830458915396479, .8232726023485646,
            .9660917830792959,.31622776601683794, .6749485577105528,
            .31622776601683794, .6324555320336759},
          {.9660917830792958, .4830458915396479, .8232726023485646,
            .9660917830792959, .31622776601683794, .6749485577105528,
            .31622776601683794,.6324555320336759}};


    sframe X = make_testing_sframe(
        {"string","int","float","vector","int-dbl-dict","str-dbl-dict"},
        {flex_type_enum::STRING,
        flex_type_enum::INTEGER,
        flex_type_enum::FLOAT,
        flex_type_enum::VECTOR,
        flex_type_enum::DICT,
        flex_type_enum::DICT},
        raw_x);

    sframe y = make_testing_sframe(
        {"response"},
        {flex_type_enum::FLOAT},
        raw_y);

    // Step 2: Convert to ML-Data
    // ---------------------------------------------------------------------

    // Since parallel and non-parallel values are handled
    // differently depending on whether they are past this
    // threshold.
    std::vector<size_t> par_threshhold_values = {0, 1, 2, 3, 4, 5, 100000};

    this->data_v.resize(par_threshhold_values.size());
    this->saved_data_v.resize(par_threshhold_values.size());
    this->metadata_v.resize(par_threshhold_values.size());

    for(size_t i= 0; i < par_threshhold_values.size(); ++i) {
      globals::set_global("TURI_ML_DATA_STATS_PARALLEL_ACCESS_THRESHOLD", par_threshhold_values[i]);

      v2::ml_data data;
      data.set_data(X, y);
      data.fill();

      this->data_v[i] = std::move(data);
      save_and_load_object(this->saved_data_v[i], this->data_v[i]);

      this->metadata_v[i] = data.metadata();
    }

    this->X = X;
    this->y = y;
    this->raw_y = raw_y;
    this->raw_x = raw_x;
    this->mapped_x = mapped_x;
    this->column_size = column_size;
    this->mean = mean;
    this->stdev = stdev;
  }

  /**
   * Test size.
   */
  void test_column_size(){
    for(const auto& data : data_v) {
      for(size_t c_idx = 0; c_idx < data.metadata()->num_columns(); ++c_idx) {
        TS_ASSERT_EQUALS(column_size[c_idx], data.metadata()->column_size(c_idx));
      }
    }
  }

  /**
   * Test size.
   */
  void test_column_size_saved(){
    for(const auto& saved_data : saved_data_v) {
      for(size_t c_idx = 0; c_idx < saved_data.metadata()->num_columns(); ++c_idx) {
        TS_ASSERT_EQUALS(column_size[c_idx], saved_data.metadata()->column_size(c_idx));
      }
    }
  }

  /**
   * Test mean.
   */
  void test_mean(){
    for(const auto& data : data_v) {
      for(size_t c_idx = 0; c_idx < data.metadata()->num_columns(); ++c_idx) {
        TS_ASSERT_EQUALS(mean[c_idx].size(), data.metadata()->column_size(c_idx));
        for(size_t i=0; i < data.metadata()->column_size(c_idx); ++i) {
          ASSERT_TRUE(std::abs(mean[c_idx][i] - data.metadata()->statistics(c_idx)->mean(i)) < 1e-4);
        }
      }
    }
  }

  /**
   * Test mean.
   */
  void test_mean_saved(){
    for(size_t i = 0; i < saved_data_v.size(); ++i) {
      const auto& saved_data = saved_data_v[i];

      for(size_t c_idx = 0; c_idx < saved_data.metadata()->num_columns(); ++c_idx) {
        TS_ASSERT_EQUALS(mean[c_idx].size(), saved_data.metadata()->column_size(c_idx));
        for(size_t i=0; i < saved_data.metadata()->column_size(c_idx); ++i) {
          ASSERT_TRUE(std::abs(mean[c_idx][i] - saved_data.metadata()->statistics(c_idx)->mean(i)) < 1e-4);
        }
      }
    }
  }



  /**
   * Test column sizes.
   */
  void test_stdev(){
    for(const auto& data : data_v) {
      for(size_t c_idx = 0; c_idx < data.metadata()->num_columns(); ++c_idx) {
        TS_ASSERT_EQUALS(stdev[c_idx].size(), data.metadata()->column_size(c_idx));
        for(size_t i=0; i < data.metadata()->column_size(c_idx); ++i) {
          ASSERT_TRUE(std::abs(stdev[c_idx][i] - data.metadata()->statistics(c_idx)->stdev(i) ) < 1e-4);
        }
      }
    }
  }

  /**
   * Test column sizes.
   */
  void test_stdev_saved(){
    for(const auto& saved_data : saved_data_v) {
      for(size_t c_idx = 0; c_idx < saved_data.metadata()->num_columns(); ++c_idx) {
        TS_ASSERT_EQUALS(stdev[c_idx].size(), saved_data.metadata()->column_size(c_idx));
        for(size_t i=0; i < saved_data.metadata()->column_size(c_idx); ++i) {
          ASSERT_TRUE(std::abs(stdev[c_idx][i] - saved_data.metadata()->statistics(c_idx)->stdev(i) ) < 1e-4);
        }
      }
    }
  }

};

BOOST_FIXTURE_TEST_SUITE(_numerics, numerics)
BOOST_AUTO_TEST_CASE(test_column_size) {
  numerics::test_column_size();
}
BOOST_AUTO_TEST_CASE(test_column_size_saved) {
  numerics::test_column_size_saved();
}
BOOST_AUTO_TEST_CASE(test_mean) {
  numerics::test_mean();
}
BOOST_AUTO_TEST_CASE(test_mean_saved) {
  numerics::test_mean_saved();
}
BOOST_AUTO_TEST_CASE(test_stdev) {
  numerics::test_stdev();
}
BOOST_AUTO_TEST_CASE(test_stdev_saved) {
  numerics::test_stdev_saved();
}
BOOST_AUTO_TEST_SUITE_END()
