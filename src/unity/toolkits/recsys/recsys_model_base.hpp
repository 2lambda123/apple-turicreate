/* Copyright © 2017 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef TURI_RECSYS_MODEL_BASE_H_
#define TURI_RECSYS_MODEL_BASE_H_

#include <map>
#include <string>
#include <set>

#include <unity/lib/toolkit_function_specification.hpp>
#include <unity/lib/unity_base_types.hpp>
#include <unity/toolkits/options/option_manager.hpp>
#include <unity/toolkits/ml_data_2/ml_data.hpp>
#include <unity/toolkits/ml_data_2/ml_data_iterators.hpp>
#include <util/fast_top_k.hpp>

// Interfaces
#include <unity/lib/extensions/ml_model.hpp>
#include <export.hpp>

namespace turi {

class iarchive;
class oarchive;
class sframe;
class flexible_type;
class column_metadata;

namespace recsys {

class recsys_popularity;


/** The base class for recsys model classes.  Individual models are
 *  expected to implement all of the pure virtual functions below,
 *  along with (optionally) overriding any of the other virtual
 *  methods.
 */
class EXPORT recsys_model_base : public ml_model_base {
 public:

  static constexpr size_t RECSYS_MODEL_BASE_VERSION = 2;

  /// Default constructor
  recsys_model_base() {}

  virtual ~recsys_model_base() {}

 protected:

  /** Train the algorithm.
   * Takes a training/validation split. Returns a map of information about the run.
   */
  virtual std::map<std::string, flexible_type> train(const v2::ml_data& training_data) = 0;

  /**
   * Takes two datasets for training.
   * \param[in] training_data_by_user ML-Data sorted by user
   * \param[in] training_data_by_item ML-Data sorted by item
   */
  virtual std::map<std::string, flexible_type> train(
                  const v2::ml_data& training_data_by_user,
                  const v2::ml_data& training_data_by_item){
    log_and_throw("Internal error. ALS not implemented");
  }

 public:
  virtual bool use_target_column(bool target_is_present) const = 0;
  virtual bool include_columns_beyond_user_item() const { return false; }

 public:
  /** Run predictions on each element in the test data set.  Returns a
   * vector corresponding to the response prediction of each
   * observation in the test_data set.
   * Also takes a ml_data in the same format containing observations
   * that are considered "available" during prediction time.
   */
  virtual sframe predict(const v2::ml_data& test_data) const = 0;

  /**
   * Get the nearest k users for each of the provided users.
   * If no users are provided, then similar users are retrieved
   * for all items observed during training.
   */
  virtual sframe get_similar_users(
      std::shared_ptr<sarray<flexible_type> > users, size_t k) const = 0;

  /**
   * Get the nearest k items for each of the provided items.
   * If no items are provided, then similar items are retrieved
   * for all items observed during training.
   */
  virtual sframe get_similar_items(
      std::shared_ptr<sarray<flexible_type> > items, size_t k) const = 0;

  /** For each of the items in sim_scores (first part of tuple), sets
   * a similarity score (second part of tuple) that is higher for
   * items similar to item.
   */
  virtual void get_item_similarity_scores(
      size_t item, std::vector<std::pair<size_t, double> >& sim_scores) const {}

  /**
   *  Returns information about all the users in the overlap of the
   *  item pairs listed in two columns in unindexed_item_pairs.  All
   *  these items must be present in the training data.
   *
   *  Returns an sframe with information about this
   *  intersection. Columns are item_1, item_2, num_users_1, num_users_2, item_intersection (dict, user ->
   */
  virtual sframe get_item_intersection_info(const sframe& unindexed_item_pairs) const;

protected:

  /** Utility function to aid in the retrieval of similar items.
   *
   *  GetSimilarFunction is a function called as
   *     f(size_t idx, std::vector<std::pair<size_t, double> >& idx_dist_dest);
   */
  template <typename GetSimilarFunction>
      sframe _create_similar_sframe(size_t column_index, std::shared_ptr<sarray<flexible_type> > items,
                                   size_t k, GetSimilarFunction&& similar) const;


public:

  /** For a given base observation, predict the score for all the
   * items with all non-item columns replaced by the values in the
   * base observation.
   *
   * The base_observation vector is used to generate all the
   * observations predicted.  New observations are generated by
   * repeatedly copying template_observation, then replacing the
   * values in item_column_index by each possible item value.
   */
  virtual void score_all_items(
      std::vector<std::pair<size_t, double> >& scores,
      const std::vector<v2::ml_data_entry>& query_row,
      size_t top_k,
      const std::vector<std::pair<size_t, double> >& user_item_list,
      const std::vector<std::pair<size_t, double> >& new_user_item_data,
      const std::vector<v2::ml_data_row_reference>& new_observation_data,
      const std::shared_ptr<v2::ml_data_side_features>& known_side_features) const = 0;


  // Set additional data for the method
  virtual void set_extra_data(const std::map<std::string, variant_type>& other_data) {}

 protected:
  virtual size_t internal_get_version() const = 0;

  /** Implement serialization (save).  The model subclass should
   * reimplement this particular function.  The syntax follows the
   * standard turicreate save() method.
   */
  virtual void internal_save(turi::oarchive& oarc) const = 0;

  /** Implement serialization (load).  The model subclass should
   * reimplement this particular function.  The syntax follows the
   * standard turicreate load() method.
   *
   * When this method is called, all the model options have been set
   * up in the base class and are readily accessible.  Furthermore,
   * once this function is called, the model is treated as trained and
   * ready to be used for prediction and ranking. Thus loading a model
   * can effectively replace the training stage.
   */
  virtual void internal_load(turi::iarchive& iarc, size_t version) = 0;

  ////////////////////////////////////////////////////////////////////////////////
  //
  //  Interacting with the data set by the train part of the model
  //
  ////////////////////////////////////////////////////////////////////////////////

 public:

  /// The metadata needed for translating the data back and forth
  static constexpr size_t USER_COLUMN_INDEX = 0;
  static constexpr size_t ITEM_COLUMN_INDEX = 1;

  std::shared_ptr<v2::ml_metadata> metadata;
  std::shared_ptr<sarray<std::vector<std::pair<size_t, double> > > > trained_user_items;

 /** Creates an ml_data object according to the given schema.  No
   * target column.
   */
  v2::ml_data create_ml_data(const sframe& data,
                             const sframe& new_user_side_data=sframe(),
                             const sframe& new_item_side_data=sframe()) const;

 private:
  /// Returns an sframe with the columns renamed such that they will
  /// not conflict with anything.
  sframe _sanitize_side_column_names(size_t main_index, sframe side_table) const;

 public:

  /**  Returns the flexible data type of the user column;
   *  The model must be trained at this point.
   */
  flex_type_enum user_type() const {
    return metadata->column_type(USER_COLUMN_INDEX);
  }

  /**  Returns the flexible data type of the item column;
   *  The model must be trained at this point.
   */
  flex_type_enum item_type() const {
    return metadata->column_type(ITEM_COLUMN_INDEX);
  }

  ////////////////////////////////////////////////////////////////////////////////
  //
  //  The methods for train, test, etc.
  //
  ////////////////////////////////////////////////////////////////////////////////

 public:

  /** Train the model using an sframe as the primary observations.
   * This method constructs the internal ml_data objects from the
   * current options.
   *
   * \param observation_data An SFrame containing at least a column containing
   * user ids and a column containing item ids.
   * \param user_side_data An SFrame containing side information about users,
   * where one column matches with the user column of observation data.
   * \param item_side_data An SFrame containing side information about items,
   * where one column matches with the item column of observation data.
   * \param other_data When provided, each model can implement a method set_extra_data
   * in order to use this argument during training.
   * \returns Statistics about the training.
   */
  void setup_and_train(const sframe& observation_data,
      const sframe& user_side_data=sframe(),
      const sframe& item_side_data=sframe(),
      const std::map<std::string, variant_type>& other_data=(std::map<std::string, variant_type>()));

  /**  Some of the models, such as popularity, can be built entirely
   *  from data already contained in the model.  This method allows us
   *  to create a new model while bypassing the typical
   *  setup_and_train method.  This simply imports all the relevant
   *  variables over; the final training is left up to the model.
   */
  void import_all_from_other_model(const recsys_model_base* other);

  recsys_model_base& operator=(const recsys_model_base&) = default;


  /** Creates and returns a popularity baseline
   *
   */
  std::shared_ptr<recsys_popularity> get_popularity_baseline() const;

  flex_dict get_data_schema() const;
  
private:

  /** Choose some things diversely.
   */
  struct diversity_choice_buffer {
    std::vector<size_t> current_candidates;
    std::vector<size_t> chosen_items;
    std::vector<size_t> current_diversity_score;
    std::vector<std::pair<size_t, double> > sim_scores;
  };

  void choose_diversely(size_t top_k,
                        std::vector<std::pair<size_t, double> >& candidates,
                        size_t random_seed,
                        diversity_choice_buffer& dv_buffer) const;

public:

  /** Return the top_k ranks for this model based on sorted
   * predictions.
   *
   * Here, for each user in users, the top_k ranks are returned in the
   * same format as the previous function.
   *
   * If exclude_observations is given, these observations are excluded
   * from the returned values.
   *
   * \overload
   */
  sframe recommend(const sframe& reference_data,
                   size_t top_k,
                   const sframe& restriction_data = sframe(),
                   const sframe& exclusion_data = sframe(),
                   const sframe& new_observation_data = sframe(),
                   const sframe& new_user_data = sframe(),
                   const sframe& new_item_data = sframe(),
                   bool exclude_training_interactions = true,
                   double diversity_factor = 0,
                   size_t random_seed = 0) const;

  std::shared_ptr<unity_sframe_base> recommend_extension_wrapper(
    std::shared_ptr<unity_sframe_base> reference_data,
    std::shared_ptr<unity_sframe_base> new_observation_data,
    flex_int top_k) const;

  virtual void export_to_coreml(
    std::shared_ptr<recsys_model_base> recsys_model,
    const std::string& filename);

  /**
   * Compute the precision and recall for a (potentially held out) set of
   * observations.
   *
   * \param validation_data A ml_data giving the validation set the
   * precision and recall should be calculated on.
   *
   * \param recommend_output The output of the recommend method.  Note
   * that recommend should be called with top_k larger than the max
   * value in cutoffs.
   *
   * \param cutoffs A vector of cutoffs for computing e.g. the top
   * [5,10,50] rankings.
   *
   * \return An sframe with 5 columns -- user, cutoff, precision,
   * recall, and item counts.
   */
   sframe precision_recall_stats(const sframe& indexed_validation_data,
                                 const sframe& recommend_output,
                                 const std::vector<size_t>& cutoffs) const;


  /**
   * Return an SFrame containing each user id and the number of
   * observations with that user in the training set.
   */
  sframe get_num_items_per_user() const;

  /**
   * Return an SFrame containing each item and the number of
   * observations with that item in the training set.
   */
  sframe get_num_users_per_item() const;


  inline size_t get_version() const {
    return RECSYS_MODEL_BASE_VERSION;
  }

  /// Serialization -- save
  virtual void save_impl(turi::oarchive& oarc) const override;

  /// Serialization -- load
  void load_version(turi::iarchive& iarc, size_t version);

  /// Get stats about algorithm runtime
  std::map<std::string, flexible_type> get_train_stats();

};

////////////////////////////////////////////////////////////////////////////////
// Implementation of the get_similar utility functions

template <typename GetSimilarFunction>
sframe recsys_model_base::_create_similar_sframe(
    size_t column_index, std::shared_ptr<sarray<flexible_type> > query,
    size_t k, GetSimilarFunction&& similar) const {

  sframe res;
  size_t num_segments = thread::cpu_count();

  const bool use_all_values = (query == nullptr);

  size_t n = use_all_values ? metadata->index_size(column_index) : query->size();

  decltype(query->get_reader()) reader;

  if(!use_all_values) {
    reader = query->get_reader();
  }

  auto indexer = metadata->indexer(column_index);

  flex_type_enum t = metadata->column_type(column_index);

  res.open_for_write(
      {metadata->column_name(column_index), "similar", "score", "rank"},
      {t, t, flex_type_enum::FLOAT, flex_type_enum::INTEGER},
      "", num_segments);

  in_parallel([&](size_t thread_idx, size_t num_threads) {

      std::vector<flexible_type> data;

      arma::fvec similarities;
      typedef std::pair<size_t, double> item_score_pair;
      std::vector<item_score_pair> score_list(metadata->index_size(column_index));

      auto it_out = res.get_output_iterator(thread_idx);

      size_t start_idx = (n * thread_idx) / num_threads;
      size_t end_idx = (n * (thread_idx+1)) / num_threads;
      size_t n_in_block = 1000;

      for(size_t block_start = start_idx; block_start < end_idx; block_start += 1000) {

        if(!use_all_values) {
          reader->read_rows(block_start, std::min(end_idx, block_start + 1000), data);
          n_in_block = data.size();
        } else {
          n_in_block = std::min(end_idx, block_start + 1000) - block_start;
        }

        for(size_t i = 0; i < n_in_block; ++i) {

          size_t query_idx = use_all_values ? block_start + i : indexer->immutable_map_value_to_index(data[i]);

          if(query_idx == -1)
            continue;

          similar(query_idx, score_list);

          // Assume that higher scores are better.
          auto score_sorter = [](const item_score_pair& vi1, const item_score_pair& vi2) {
            return vi1.second < vi2.second;
          };

          // get an extra item in case the query_idx is in there.
          // Then ignore it if it is.
          extract_and_sort_top_k(score_list, k + 1, score_sorter);

          // Write out the top-k items in indexed format to an output
          // sframe with the original values.  Skip the current query
          // index if it's in there.
          const flexible_type& query_item = use_all_values ? indexer->map_index_to_value(query_idx) : data[i];

          for(size_t j = 0, rank = 1; j < score_list.size(); ++j, ++it_out) {
            if(score_list[j].first == query_idx)
              continue;


            flexible_type ref_datum = indexer->map_index_to_value(score_list[j].first);
            *it_out = {query_item, ref_datum, score_list[j].second, rank};
            ++rank;

            if(rank > k)
              break;
          }
        }
      }
    });

  res.close();
  return res;
}

}}

#endif /* TURI_RECSYS_ALGORITHM_TEMPLATE_H_ */


