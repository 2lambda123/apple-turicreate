#ifndef MPS_FLOAT_ARRAY_HPP_
#define MPS_FLOAT_ARRAY_HPP_

#include <cstddef>
#include <memory>
#include <vector>

namespace turi {
namespace mps {

// Pure virtual (but low-level) interface for an n-dimensional array. The inputs
// and outputs of the TCMPS library are largely expressed with this type.
class float_array {
public:
  virtual ~float_array() = default;

  // Returns a pointer to the first float value in the data. This pointer is
  // guaranteed to remain valid for the lifetime of this float_array instance.
  virtual const float* data() const = 0;

  // Returns the total number of float values present, beginning at the pointer
  // returned by data(). This number must equal the product of all the sizes in
  // the shape array.
  virtual size_t size() const = 0;

  // Returns a pointer to the first element of the shape array. This pointer is
  // guaranteed to remain valid for the lifetime of this float_array instance.
  virtual const size_t* shape() const = 0;

  // Returns the total number of elements in the array returned by shape().
  virtual size_t dim() const = 0;
};

// Wrapper around raw C pointers into an external n-dimensional array. Users
// must manually ensure that the external array outlives instances of this
// wrapper.
class external_float_array: public float_array {
public:
  external_float_array(const float* data, size_t size, const size_t* shape,
                       size_t dim);

  const float* data() const override { return data_; }
  size_t size() const override { return size_; }

  const size_t* shape() const override { return shape_; }
  size_t dim() const override { return dim_; }

private:
  const float* data_ = nullptr;
  size_t size_ = 0;

  const size_t* shape_ = nullptr;
  size_t dim_ = 0;
};

// A float_array implementation that directly owns the memory containing the
// float data.
class float_buffer: public float_array {
public:
  // Copies enough float values from `data` to fill the given `shape`.
  float_buffer(const float* data, std::vector<size_t> shape);

  const float* data() const override { return data_.data(); }
  size_t size() const override { return size_; }

  const size_t* shape() const override { return shape_.data(); }
  size_t dim() const override { return shape_.size(); }

private:
  std::vector<size_t> shape_;
  size_t size_;
  std::vector<float> data_;
};

// A float_array implementation that maintains a view into another float_array
// (that is possibly shared with others shared_float_array instances). Instances
// of this class can be efficiently copied (in constant time and incurring no
// additional allocations).
class shared_float_array: public float_array {
public:
  // Convenience function for creating a shared float_buffer.
  static shared_float_array copy(const float* data, std::vector<size_t> shape) {
    return shared_float_array(
        std::make_shared<float_buffer>(data, std::move(shape)));
  }

  // Simply wraps an existing float_array shared_ptr.
  explicit shared_float_array(std::shared_ptr<float_array> impl)
    : shared_float_array(impl, impl->data(), impl->shape(), impl->dim())
  {}

  // Creates an array containing the scalar 0.f.
  shared_float_array(): shared_float_array(default_value()) {}

  const float* data() const override { return data_; }
  size_t size() const override { return size_; }

  const size_t* shape() const override { return shape_; }
  size_t dim() const override { return dim_; }

protected:
  shared_float_array(std::shared_ptr<float_array> impl, const float* data,
                     const size_t* shape, size_t dim);

private:
  static std::shared_ptr<float_array> default_value();

  std::shared_ptr<float_array> impl_;

  const float* data_ = nullptr;
  const size_t* shape_ = nullptr;
  size_t dim_ = 0;
  size_t size_ = 0;
};

}  // namespace mps
}  // namespace turi

#endif  // MPS_FLOAT_ARRAY_HPP_
