// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: OneHotEncoder.proto

#ifndef PROTOBUF_OneHotEncoder_2eproto__INCLUDED
#define PROTOBUF_OneHotEncoder_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_util.h>
#include "DataStructures.pb.h"  // IWYU pragma: export
// @@protoc_insertion_point(includes)
namespace CoreML {
namespace Specification {
class ArrayFeatureType;
class ArrayFeatureTypeDefaultTypeInternal;
extern ArrayFeatureTypeDefaultTypeInternal _ArrayFeatureType_default_instance_;
class ArrayFeatureType_EnumeratedShapes;
class ArrayFeatureType_EnumeratedShapesDefaultTypeInternal;
extern ArrayFeatureType_EnumeratedShapesDefaultTypeInternal _ArrayFeatureType_EnumeratedShapes_default_instance_;
class ArrayFeatureType_Shape;
class ArrayFeatureType_ShapeDefaultTypeInternal;
extern ArrayFeatureType_ShapeDefaultTypeInternal _ArrayFeatureType_Shape_default_instance_;
class ArrayFeatureType_ShapeRange;
class ArrayFeatureType_ShapeRangeDefaultTypeInternal;
extern ArrayFeatureType_ShapeRangeDefaultTypeInternal _ArrayFeatureType_ShapeRange_default_instance_;
class DictionaryFeatureType;
class DictionaryFeatureTypeDefaultTypeInternal;
extern DictionaryFeatureTypeDefaultTypeInternal _DictionaryFeatureType_default_instance_;
class DoubleFeatureType;
class DoubleFeatureTypeDefaultTypeInternal;
extern DoubleFeatureTypeDefaultTypeInternal _DoubleFeatureType_default_instance_;
class DoubleRange;
class DoubleRangeDefaultTypeInternal;
extern DoubleRangeDefaultTypeInternal _DoubleRange_default_instance_;
class DoubleVector;
class DoubleVectorDefaultTypeInternal;
extern DoubleVectorDefaultTypeInternal _DoubleVector_default_instance_;
class FeatureType;
class FeatureTypeDefaultTypeInternal;
extern FeatureTypeDefaultTypeInternal _FeatureType_default_instance_;
class FloatVector;
class FloatVectorDefaultTypeInternal;
extern FloatVectorDefaultTypeInternal _FloatVector_default_instance_;
class ImageFeatureType;
class ImageFeatureTypeDefaultTypeInternal;
extern ImageFeatureTypeDefaultTypeInternal _ImageFeatureType_default_instance_;
class ImageFeatureType_EnumeratedImageSizes;
class ImageFeatureType_EnumeratedImageSizesDefaultTypeInternal;
extern ImageFeatureType_EnumeratedImageSizesDefaultTypeInternal _ImageFeatureType_EnumeratedImageSizes_default_instance_;
class ImageFeatureType_ImageSize;
class ImageFeatureType_ImageSizeDefaultTypeInternal;
extern ImageFeatureType_ImageSizeDefaultTypeInternal _ImageFeatureType_ImageSize_default_instance_;
class ImageFeatureType_ImageSizeRange;
class ImageFeatureType_ImageSizeRangeDefaultTypeInternal;
extern ImageFeatureType_ImageSizeRangeDefaultTypeInternal _ImageFeatureType_ImageSizeRange_default_instance_;
class Int64FeatureType;
class Int64FeatureTypeDefaultTypeInternal;
extern Int64FeatureTypeDefaultTypeInternal _Int64FeatureType_default_instance_;
class Int64Range;
class Int64RangeDefaultTypeInternal;
extern Int64RangeDefaultTypeInternal _Int64Range_default_instance_;
class Int64Set;
class Int64SetDefaultTypeInternal;
extern Int64SetDefaultTypeInternal _Int64Set_default_instance_;
class Int64ToDoubleMap;
class Int64ToDoubleMapDefaultTypeInternal;
extern Int64ToDoubleMapDefaultTypeInternal _Int64ToDoubleMap_default_instance_;
class Int64ToDoubleMap_MapEntry;
class Int64ToDoubleMap_MapEntryDefaultTypeInternal;
extern Int64ToDoubleMap_MapEntryDefaultTypeInternal _Int64ToDoubleMap_MapEntry_default_instance_;
class Int64ToStringMap;
class Int64ToStringMapDefaultTypeInternal;
extern Int64ToStringMapDefaultTypeInternal _Int64ToStringMap_default_instance_;
class Int64ToStringMap_MapEntry;
class Int64ToStringMap_MapEntryDefaultTypeInternal;
extern Int64ToStringMap_MapEntryDefaultTypeInternal _Int64ToStringMap_MapEntry_default_instance_;
class Int64Vector;
class Int64VectorDefaultTypeInternal;
extern Int64VectorDefaultTypeInternal _Int64Vector_default_instance_;
class OneHotEncoder;
class OneHotEncoderDefaultTypeInternal;
extern OneHotEncoderDefaultTypeInternal _OneHotEncoder_default_instance_;
class SequenceFeatureType;
class SequenceFeatureTypeDefaultTypeInternal;
extern SequenceFeatureTypeDefaultTypeInternal _SequenceFeatureType_default_instance_;
class SizeRange;
class SizeRangeDefaultTypeInternal;
extern SizeRangeDefaultTypeInternal _SizeRange_default_instance_;
class StringFeatureType;
class StringFeatureTypeDefaultTypeInternal;
extern StringFeatureTypeDefaultTypeInternal _StringFeatureType_default_instance_;
class StringToDoubleMap;
class StringToDoubleMapDefaultTypeInternal;
extern StringToDoubleMapDefaultTypeInternal _StringToDoubleMap_default_instance_;
class StringToDoubleMap_MapEntry;
class StringToDoubleMap_MapEntryDefaultTypeInternal;
extern StringToDoubleMap_MapEntryDefaultTypeInternal _StringToDoubleMap_MapEntry_default_instance_;
class StringToInt64Map;
class StringToInt64MapDefaultTypeInternal;
extern StringToInt64MapDefaultTypeInternal _StringToInt64Map_default_instance_;
class StringToInt64Map_MapEntry;
class StringToInt64Map_MapEntryDefaultTypeInternal;
extern StringToInt64Map_MapEntryDefaultTypeInternal _StringToInt64Map_MapEntry_default_instance_;
class StringVector;
class StringVectorDefaultTypeInternal;
extern StringVectorDefaultTypeInternal _StringVector_default_instance_;
}  // namespace Specification
}  // namespace CoreML

namespace CoreML {
namespace Specification {

namespace protobuf_OneHotEncoder_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_OneHotEncoder_2eproto

enum OneHotEncoder_HandleUnknown {
  OneHotEncoder_HandleUnknown_ErrorOnUnknown = 0,
  OneHotEncoder_HandleUnknown_IgnoreUnknown = 1,
  OneHotEncoder_HandleUnknown_OneHotEncoder_HandleUnknown_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  OneHotEncoder_HandleUnknown_OneHotEncoder_HandleUnknown_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool OneHotEncoder_HandleUnknown_IsValid(int value);
const OneHotEncoder_HandleUnknown OneHotEncoder_HandleUnknown_HandleUnknown_MIN = OneHotEncoder_HandleUnknown_ErrorOnUnknown;
const OneHotEncoder_HandleUnknown OneHotEncoder_HandleUnknown_HandleUnknown_MAX = OneHotEncoder_HandleUnknown_IgnoreUnknown;
const int OneHotEncoder_HandleUnknown_HandleUnknown_ARRAYSIZE = OneHotEncoder_HandleUnknown_HandleUnknown_MAX + 1;

// ===================================================================

class OneHotEncoder : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:CoreML.Specification.OneHotEncoder) */ {
 public:
  OneHotEncoder();
  virtual ~OneHotEncoder();

  OneHotEncoder(const OneHotEncoder& from);

  inline OneHotEncoder& operator=(const OneHotEncoder& from) {
    CopyFrom(from);
    return *this;
  }

  static const OneHotEncoder& default_instance();

  enum CategoryTypeCase {
    kStringCategories = 1,
    kInt64Categories = 2,
    CATEGORYTYPE_NOT_SET = 0,
  };

  static inline const OneHotEncoder* internal_default_instance() {
    return reinterpret_cast<const OneHotEncoder*>(
               &_OneHotEncoder_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(OneHotEncoder* other);

  // implements Message ----------------------------------------------

  inline OneHotEncoder* New() const PROTOBUF_FINAL { return New(NULL); }

  OneHotEncoder* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const OneHotEncoder& from);
  void MergeFrom(const OneHotEncoder& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(OneHotEncoder* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef OneHotEncoder_HandleUnknown HandleUnknown;
  static const HandleUnknown ErrorOnUnknown =
    OneHotEncoder_HandleUnknown_ErrorOnUnknown;
  static const HandleUnknown IgnoreUnknown =
    OneHotEncoder_HandleUnknown_IgnoreUnknown;
  static inline bool HandleUnknown_IsValid(int value) {
    return OneHotEncoder_HandleUnknown_IsValid(value);
  }
  static const HandleUnknown HandleUnknown_MIN =
    OneHotEncoder_HandleUnknown_HandleUnknown_MIN;
  static const HandleUnknown HandleUnknown_MAX =
    OneHotEncoder_HandleUnknown_HandleUnknown_MAX;
  static const int HandleUnknown_ARRAYSIZE =
    OneHotEncoder_HandleUnknown_HandleUnknown_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // bool outputSparse = 10;
  void clear_outputsparse();
  static const int kOutputSparseFieldNumber = 10;
  bool outputsparse() const;
  void set_outputsparse(bool value);

  // .CoreML.Specification.OneHotEncoder.HandleUnknown handleUnknown = 11;
  void clear_handleunknown();
  static const int kHandleUnknownFieldNumber = 11;
  ::CoreML::Specification::OneHotEncoder_HandleUnknown handleunknown() const;
  void set_handleunknown(::CoreML::Specification::OneHotEncoder_HandleUnknown value);

  // .CoreML.Specification.StringVector stringCategories = 1;
  bool has_stringcategories() const;
  void clear_stringcategories();
  static const int kStringCategoriesFieldNumber = 1;
  const ::CoreML::Specification::StringVector& stringcategories() const;
  ::CoreML::Specification::StringVector* mutable_stringcategories();
  ::CoreML::Specification::StringVector* release_stringcategories();
  void set_allocated_stringcategories(::CoreML::Specification::StringVector* stringcategories);

  // .CoreML.Specification.Int64Vector int64Categories = 2;
  bool has_int64categories() const;
  void clear_int64categories();
  static const int kInt64CategoriesFieldNumber = 2;
  const ::CoreML::Specification::Int64Vector& int64categories() const;
  ::CoreML::Specification::Int64Vector* mutable_int64categories();
  ::CoreML::Specification::Int64Vector* release_int64categories();
  void set_allocated_int64categories(::CoreML::Specification::Int64Vector* int64categories);

  CategoryTypeCase CategoryType_case() const;
  // @@protoc_insertion_point(class_scope:CoreML.Specification.OneHotEncoder)
 private:
  void set_has_stringcategories();
  void set_has_int64categories();

  inline bool has_CategoryType() const;
  void clear_CategoryType();
  inline void clear_has_CategoryType();

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  bool outputsparse_;
  int handleunknown_;
  union CategoryTypeUnion {
    CategoryTypeUnion() {}
    ::CoreML::Specification::StringVector* stringcategories_;
    ::CoreML::Specification::Int64Vector* int64categories_;
  } CategoryType_;
  mutable int _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct protobuf_OneHotEncoder_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// OneHotEncoder

// .CoreML.Specification.StringVector stringCategories = 1;
inline bool OneHotEncoder::has_stringcategories() const {
  return CategoryType_case() == kStringCategories;
}
inline void OneHotEncoder::set_has_stringcategories() {
  _oneof_case_[0] = kStringCategories;
}
inline void OneHotEncoder::clear_stringcategories() {
  if (has_stringcategories()) {
    delete CategoryType_.stringcategories_;
    clear_has_CategoryType();
  }
}
inline  const ::CoreML::Specification::StringVector& OneHotEncoder::stringcategories() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.OneHotEncoder.stringCategories)
  return has_stringcategories()
      ? *CategoryType_.stringcategories_
      : ::CoreML::Specification::StringVector::default_instance();
}
inline ::CoreML::Specification::StringVector* OneHotEncoder::mutable_stringcategories() {
  if (!has_stringcategories()) {
    clear_CategoryType();
    set_has_stringcategories();
    CategoryType_.stringcategories_ = new ::CoreML::Specification::StringVector;
  }
  // @@protoc_insertion_point(field_mutable:CoreML.Specification.OneHotEncoder.stringCategories)
  return CategoryType_.stringcategories_;
}
inline ::CoreML::Specification::StringVector* OneHotEncoder::release_stringcategories() {
  // @@protoc_insertion_point(field_release:CoreML.Specification.OneHotEncoder.stringCategories)
  if (has_stringcategories()) {
    clear_has_CategoryType();
    ::CoreML::Specification::StringVector* temp = CategoryType_.stringcategories_;
    CategoryType_.stringcategories_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
inline void OneHotEncoder::set_allocated_stringcategories(::CoreML::Specification::StringVector* stringcategories) {
  clear_CategoryType();
  if (stringcategories) {
    set_has_stringcategories();
    CategoryType_.stringcategories_ = stringcategories;
  }
  // @@protoc_insertion_point(field_set_allocated:CoreML.Specification.OneHotEncoder.stringCategories)
}

// .CoreML.Specification.Int64Vector int64Categories = 2;
inline bool OneHotEncoder::has_int64categories() const {
  return CategoryType_case() == kInt64Categories;
}
inline void OneHotEncoder::set_has_int64categories() {
  _oneof_case_[0] = kInt64Categories;
}
inline void OneHotEncoder::clear_int64categories() {
  if (has_int64categories()) {
    delete CategoryType_.int64categories_;
    clear_has_CategoryType();
  }
}
inline  const ::CoreML::Specification::Int64Vector& OneHotEncoder::int64categories() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.OneHotEncoder.int64Categories)
  return has_int64categories()
      ? *CategoryType_.int64categories_
      : ::CoreML::Specification::Int64Vector::default_instance();
}
inline ::CoreML::Specification::Int64Vector* OneHotEncoder::mutable_int64categories() {
  if (!has_int64categories()) {
    clear_CategoryType();
    set_has_int64categories();
    CategoryType_.int64categories_ = new ::CoreML::Specification::Int64Vector;
  }
  // @@protoc_insertion_point(field_mutable:CoreML.Specification.OneHotEncoder.int64Categories)
  return CategoryType_.int64categories_;
}
inline ::CoreML::Specification::Int64Vector* OneHotEncoder::release_int64categories() {
  // @@protoc_insertion_point(field_release:CoreML.Specification.OneHotEncoder.int64Categories)
  if (has_int64categories()) {
    clear_has_CategoryType();
    ::CoreML::Specification::Int64Vector* temp = CategoryType_.int64categories_;
    CategoryType_.int64categories_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
inline void OneHotEncoder::set_allocated_int64categories(::CoreML::Specification::Int64Vector* int64categories) {
  clear_CategoryType();
  if (int64categories) {
    set_has_int64categories();
    CategoryType_.int64categories_ = int64categories;
  }
  // @@protoc_insertion_point(field_set_allocated:CoreML.Specification.OneHotEncoder.int64Categories)
}

// bool outputSparse = 10;
inline void OneHotEncoder::clear_outputsparse() {
  outputsparse_ = false;
}
inline bool OneHotEncoder::outputsparse() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.OneHotEncoder.outputSparse)
  return outputsparse_;
}
inline void OneHotEncoder::set_outputsparse(bool value) {

  outputsparse_ = value;
  // @@protoc_insertion_point(field_set:CoreML.Specification.OneHotEncoder.outputSparse)
}

// .CoreML.Specification.OneHotEncoder.HandleUnknown handleUnknown = 11;
inline void OneHotEncoder::clear_handleunknown() {
  handleunknown_ = 0;
}
inline ::CoreML::Specification::OneHotEncoder_HandleUnknown OneHotEncoder::handleunknown() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.OneHotEncoder.handleUnknown)
  return static_cast< ::CoreML::Specification::OneHotEncoder_HandleUnknown >(handleunknown_);
}
inline void OneHotEncoder::set_handleunknown(::CoreML::Specification::OneHotEncoder_HandleUnknown value) {

  handleunknown_ = value;
  // @@protoc_insertion_point(field_set:CoreML.Specification.OneHotEncoder.handleUnknown)
}

inline bool OneHotEncoder::has_CategoryType() const {
  return CategoryType_case() != CATEGORYTYPE_NOT_SET;
}
inline void OneHotEncoder::clear_has_CategoryType() {
  _oneof_case_[0] = CATEGORYTYPE_NOT_SET;
}
inline OneHotEncoder::CategoryTypeCase OneHotEncoder::CategoryType_case() const {
  return OneHotEncoder::CategoryTypeCase(_oneof_case_[0]);
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace Specification
}  // namespace CoreML

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::CoreML::Specification::OneHotEncoder_HandleUnknown> : ::google::protobuf::internal::true_type {};

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_OneHotEncoder_2eproto__INCLUDED
