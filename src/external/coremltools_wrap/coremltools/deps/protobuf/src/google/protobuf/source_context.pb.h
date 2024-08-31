// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/source_context.proto

#ifndef PROTOBUF_google_2fprotobuf_2fsource_5fcontext_2eproto__INCLUDED
#define PROTOBUF_google_2fprotobuf_2fsource_5fcontext_2eproto__INCLUDED

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
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace google {
namespace protobuf {
class SourceContext;
class SourceContextDefaultTypeInternal;
LIBPROTOBUF_EXPORT extern SourceContextDefaultTypeInternal _SourceContext_default_instance_;
}  // namespace protobuf
}  // namespace google

namespace google {
namespace protobuf {

namespace protobuf_google_2fprotobuf_2fsource_5fcontext_2eproto {
// Internal implementation detail -- do not call these.
struct LIBPROTOBUF_EXPORT TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void LIBPROTOBUF_EXPORT AddDescriptors();
void LIBPROTOBUF_EXPORT InitDefaults();
}  // namespace protobuf_google_2fprotobuf_2fsource_5fcontext_2eproto

// ===================================================================

class LIBPROTOBUF_EXPORT SourceContext : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:google.protobuf.SourceContext) */ {
 public:
  SourceContext();
  virtual ~SourceContext();

  SourceContext(const SourceContext& from);

  inline SourceContext& operator=(const SourceContext& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SourceContext& default_instance();

  static inline const SourceContext* internal_default_instance() {
    return reinterpret_cast<const SourceContext*>(
               &_SourceContext_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(SourceContext* other);

  // implements Message ----------------------------------------------

  inline SourceContext* New() const PROTOBUF_FINAL { return New(NULL); }

  SourceContext* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const SourceContext& from);
  void MergeFrom(const SourceContext& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(SourceContext* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string file_name = 1;
  void clear_file_name();
  static const int kFileNameFieldNumber = 1;
  const ::std::string& file_name() const;
  void set_file_name(const ::std::string& value);
  #if LANG_CXX11
  void set_file_name(::std::string&& value);
  #endif
  void set_file_name(const char* value);
  void set_file_name(const char* value, size_t size);
  ::std::string* mutable_file_name();
  ::std::string* release_file_name();
  void set_allocated_file_name(::std::string* file_name);

  // @@protoc_insertion_point(class_scope:google.protobuf.SourceContext)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr file_name_;
  mutable int _cached_size_;
  friend struct protobuf_google_2fprotobuf_2fsource_5fcontext_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// SourceContext

// string file_name = 1;
inline void SourceContext::clear_file_name() {
  file_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& SourceContext::file_name() const {
  // @@protoc_insertion_point(field_get:google.protobuf.SourceContext.file_name)
  return file_name_.GetNoArena();
}
inline void SourceContext::set_file_name(const ::std::string& value) {

  file_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:google.protobuf.SourceContext.file_name)
}
#if LANG_CXX11
inline void SourceContext::set_file_name(::std::string&& value) {

  file_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:google.protobuf.SourceContext.file_name)
}
#endif
inline void SourceContext::set_file_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);

  file_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:google.protobuf.SourceContext.file_name)
}
inline void SourceContext::set_file_name(const char* value, size_t size) {

  file_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:google.protobuf.SourceContext.file_name)
}
inline ::std::string* SourceContext::mutable_file_name() {

  // @@protoc_insertion_point(field_mutable:google.protobuf.SourceContext.file_name)
  return file_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* SourceContext::release_file_name() {
  // @@protoc_insertion_point(field_release:google.protobuf.SourceContext.file_name)

  return file_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SourceContext::set_allocated_file_name(::std::string* file_name) {
  if (file_name != NULL) {

  } else {

  }
  file_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), file_name);
  // @@protoc_insertion_point(field_set_allocated:google.protobuf.SourceContext.file_name)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_google_2fprotobuf_2fsource_5fcontext_2eproto__INCLUDED
