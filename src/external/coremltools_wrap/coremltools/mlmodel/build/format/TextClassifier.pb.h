// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TextClassifier.proto

#ifndef PROTOBUF_TextClassifier_2eproto__INCLUDED
#define PROTOBUF_TextClassifier_2eproto__INCLUDED

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
namespace CoreMLModels {
class TextClassifier;
class TextClassifierDefaultTypeInternal;
extern TextClassifierDefaultTypeInternal _TextClassifier_default_instance_;
}  // namespace CoreMLModels
}  // namespace Specification
}  // namespace CoreML

namespace CoreML {
namespace Specification {
namespace CoreMLModels {

namespace protobuf_TextClassifier_2eproto {
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
}  // namespace protobuf_TextClassifier_2eproto

// ===================================================================

class TextClassifier : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:CoreML.Specification.CoreMLModels.TextClassifier) */ {
 public:
  TextClassifier();
  virtual ~TextClassifier();

  TextClassifier(const TextClassifier& from);

  inline TextClassifier& operator=(const TextClassifier& from) {
    CopyFrom(from);
    return *this;
  }

  static const TextClassifier& default_instance();

  enum ClassLabelsCase {
    kStringClassLabels = 200,
    CLASSLABELS_NOT_SET = 0,
  };

  static inline const TextClassifier* internal_default_instance() {
    return reinterpret_cast<const TextClassifier*>(
               &_TextClassifier_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(TextClassifier* other);

  // implements Message ----------------------------------------------

  inline TextClassifier* New() const PROTOBUF_FINAL { return New(NULL); }

  TextClassifier* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const TextClassifier& from);
  void MergeFrom(const TextClassifier& from);
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
  void InternalSwap(TextClassifier* other);
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

  // accessors -------------------------------------------------------

  // string language = 10;
  void clear_language();
  static const int kLanguageFieldNumber = 10;
  const ::std::string& language() const;
  void set_language(const ::std::string& value);
  #if LANG_CXX11
  void set_language(::std::string&& value);
  #endif
  void set_language(const char* value);
  void set_language(const char* value, size_t size);
  ::std::string* mutable_language();
  ::std::string* release_language();
  void set_allocated_language(::std::string* language);

  // bytes modelParameterData = 100;
  void clear_modelparameterdata();
  static const int kModelParameterDataFieldNumber = 100;
  const ::std::string& modelparameterdata() const;
  void set_modelparameterdata(const ::std::string& value);
  #if LANG_CXX11
  void set_modelparameterdata(::std::string&& value);
  #endif
  void set_modelparameterdata(const char* value);
  void set_modelparameterdata(const void* value, size_t size);
  ::std::string* mutable_modelparameterdata();
  ::std::string* release_modelparameterdata();
  void set_allocated_modelparameterdata(::std::string* modelparameterdata);

  // uint32 revision = 1;
  void clear_revision();
  static const int kRevisionFieldNumber = 1;
  ::google::protobuf::uint32 revision() const;
  void set_revision(::google::protobuf::uint32 value);

  // .CoreML.Specification.StringVector stringClassLabels = 200;
  bool has_stringclasslabels() const;
  void clear_stringclasslabels();
  static const int kStringClassLabelsFieldNumber = 200;
  const ::CoreML::Specification::StringVector& stringclasslabels() const;
  ::CoreML::Specification::StringVector* mutable_stringclasslabels();
  ::CoreML::Specification::StringVector* release_stringclasslabels();
  void set_allocated_stringclasslabels(::CoreML::Specification::StringVector* stringclasslabels);

  ClassLabelsCase ClassLabels_case() const;
  // @@protoc_insertion_point(class_scope:CoreML.Specification.CoreMLModels.TextClassifier)
 private:
  void set_has_stringclasslabels();

  inline bool has_ClassLabels() const;
  void clear_ClassLabels();
  inline void clear_has_ClassLabels();

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr language_;
  ::google::protobuf::internal::ArenaStringPtr modelparameterdata_;
  ::google::protobuf::uint32 revision_;
  union ClassLabelsUnion {
    ClassLabelsUnion() {}
    ::CoreML::Specification::StringVector* stringclasslabels_;
  } ClassLabels_;
  mutable int _cached_size_;
  ::google::protobuf::uint32 _oneof_case_[1];

  friend struct protobuf_TextClassifier_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// TextClassifier

// uint32 revision = 1;
inline void TextClassifier::clear_revision() {
  revision_ = 0u;
}
inline ::google::protobuf::uint32 TextClassifier::revision() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.CoreMLModels.TextClassifier.revision)
  return revision_;
}
inline void TextClassifier::set_revision(::google::protobuf::uint32 value) {

  revision_ = value;
  // @@protoc_insertion_point(field_set:CoreML.Specification.CoreMLModels.TextClassifier.revision)
}

// string language = 10;
inline void TextClassifier::clear_language() {
  language_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TextClassifier::language() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.CoreMLModels.TextClassifier.language)
  return language_.GetNoArena();
}
inline void TextClassifier::set_language(const ::std::string& value) {

  language_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CoreML.Specification.CoreMLModels.TextClassifier.language)
}
#if LANG_CXX11
inline void TextClassifier::set_language(::std::string&& value) {

  language_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:CoreML.Specification.CoreMLModels.TextClassifier.language)
}
#endif
inline void TextClassifier::set_language(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  language_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CoreML.Specification.CoreMLModels.TextClassifier.language)
}
inline void TextClassifier::set_language(const char* value, size_t size) {

  language_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CoreML.Specification.CoreMLModels.TextClassifier.language)
}
inline ::std::string* TextClassifier::mutable_language() {

  // @@protoc_insertion_point(field_mutable:CoreML.Specification.CoreMLModels.TextClassifier.language)
  return language_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TextClassifier::release_language() {
  // @@protoc_insertion_point(field_release:CoreML.Specification.CoreMLModels.TextClassifier.language)

  return language_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TextClassifier::set_allocated_language(::std::string* language) {
  if (language != NULL) {

  } else {

  }
  language_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), language);
  // @@protoc_insertion_point(field_set_allocated:CoreML.Specification.CoreMLModels.TextClassifier.language)
}

// bytes modelParameterData = 100;
inline void TextClassifier::clear_modelparameterdata() {
  modelparameterdata_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& TextClassifier::modelparameterdata() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
  return modelparameterdata_.GetNoArena();
}
inline void TextClassifier::set_modelparameterdata(const ::std::string& value) {

  modelparameterdata_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
}
#if LANG_CXX11
inline void TextClassifier::set_modelparameterdata(::std::string&& value) {

  modelparameterdata_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
}
#endif
inline void TextClassifier::set_modelparameterdata(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  modelparameterdata_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
}
inline void TextClassifier::set_modelparameterdata(const void* value, size_t size) {

  modelparameterdata_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
}
inline ::std::string* TextClassifier::mutable_modelparameterdata() {

  // @@protoc_insertion_point(field_mutable:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
  return modelparameterdata_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* TextClassifier::release_modelparameterdata() {
  // @@protoc_insertion_point(field_release:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)

  return modelparameterdata_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void TextClassifier::set_allocated_modelparameterdata(::std::string* modelparameterdata) {
  if (modelparameterdata != NULL) {

  } else {

  }
  modelparameterdata_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), modelparameterdata);
  // @@protoc_insertion_point(field_set_allocated:CoreML.Specification.CoreMLModels.TextClassifier.modelParameterData)
}

// .CoreML.Specification.StringVector stringClassLabels = 200;
inline bool TextClassifier::has_stringclasslabels() const {
  return ClassLabels_case() == kStringClassLabels;
}
inline void TextClassifier::set_has_stringclasslabels() {
  _oneof_case_[0] = kStringClassLabels;
}
inline void TextClassifier::clear_stringclasslabels() {
  if (has_stringclasslabels()) {
    delete ClassLabels_.stringclasslabels_;
    clear_has_ClassLabels();
  }
}
inline  const ::CoreML::Specification::StringVector& TextClassifier::stringclasslabels() const {
  // @@protoc_insertion_point(field_get:CoreML.Specification.CoreMLModels.TextClassifier.stringClassLabels)
  return has_stringclasslabels()
      ? *ClassLabels_.stringclasslabels_
      : ::CoreML::Specification::StringVector::default_instance();
}
inline ::CoreML::Specification::StringVector* TextClassifier::mutable_stringclasslabels() {
  if (!has_stringclasslabels()) {
    clear_ClassLabels();
    set_has_stringclasslabels();
    ClassLabels_.stringclasslabels_ = new ::CoreML::Specification::StringVector;
  }
  // @@protoc_insertion_point(field_mutable:CoreML.Specification.CoreMLModels.TextClassifier.stringClassLabels)
  return ClassLabels_.stringclasslabels_;
}
inline ::CoreML::Specification::StringVector* TextClassifier::release_stringclasslabels() {
  // @@protoc_insertion_point(field_release:CoreML.Specification.CoreMLModels.TextClassifier.stringClassLabels)
  if (has_stringclasslabels()) {
    clear_has_ClassLabels();
    ::CoreML::Specification::StringVector* temp = ClassLabels_.stringclasslabels_;
    ClassLabels_.stringclasslabels_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
inline void TextClassifier::set_allocated_stringclasslabels(::CoreML::Specification::StringVector* stringclasslabels) {
  clear_ClassLabels();
  if (stringclasslabels) {
    set_has_stringclasslabels();
    ClassLabels_.stringclasslabels_ = stringclasslabels;
  }
  // @@protoc_insertion_point(field_set_allocated:CoreML.Specification.CoreMLModels.TextClassifier.stringClassLabels)
}

inline bool TextClassifier::has_ClassLabels() const {
  return ClassLabels_case() != CLASSLABELS_NOT_SET;
}
inline void TextClassifier::clear_has_ClassLabels() {
  _oneof_case_[0] = CLASSLABELS_NOT_SET;
}
inline TextClassifier::ClassLabelsCase TextClassifier::ClassLabels_case() const {
  return TextClassifier::ClassLabelsCase(_oneof_case_[0]);
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace CoreMLModels
}  // namespace Specification
}  // namespace CoreML

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_TextClassifier_2eproto__INCLUDED
