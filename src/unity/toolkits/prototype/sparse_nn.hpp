#ifndef SPARSE_NN_HPP
#define SPARSE_NN_HPP

#include <export.hpp>
#include <unity/lib/extensions/ml_model.hpp>
#include <unity/lib/gl_sframe.hpp>
#include <unity/lib/toolkit_class_macros.hpp>

namespace turi {
namespace prototype {

class EXPORT sparse_nn : public ml_model_base {
 public:
  static constexpr size_t SPARSE_NN_VERSION = 0;

  // Call this function to set up the training data.  All columns must be string
  // or integer columns and are treated as categorical indicators.
  void train(const gl_sframe& data, const std::string& id_column);

  // Returns a dictionary of id to  distance for the top k values
  flex_dict query(const flex_dict& x, size_t k) const;

  // Serialization
  void save_impl(oarchive& oarc) const override;
  void load_version(iarchive& iarc, size_t version) override;

  BEGIN_CLASS_MEMBER_REGISTRATION("_sparse_nn")
  IMPORT_BASE_CLASS_REGISTRATION(ml_model_base);
  REGISTER_CLASS_MEMBER_FUNCTION(sparse_nn::train, "data", "id_column");
  REGISTER_CLASS_MEMBER_FUNCTION(sparse_nn::query, "x", "k");
  END_CLASS_MEMBER_REGISTRATION

 private:
  // Some metadata.
  size_t num_columns = 0;
  std::vector<flexible_type> ids;

  // This is optimized for extremely efficient lookup on small, in-memory
  // datasets.
  //
  // Query Algorithm:
  //
  // 1. For each feature, do bisection search to determine which index is the
  // correct one for the given column/feature combo.
  //
  // 2. Increment the corresponding values in hit_indices that are denoted by
  // the bounds given in access_bounds at the index of the found hash in hashes.
  std::vector<uint128_t> hashes;

  std::vector<std::pair<uint32_t, uint32_t> > access_bounds;
  std::vector<uint32_t> hit_indices;

  inline uint128_t feature_hash(const std::string& column,
                                const flexible_type& feature) const {
    return hash128_combine(hash128(column), feature.hash128());
  }
};

}  // namespace prototype
}  // namespace turi

#endif

