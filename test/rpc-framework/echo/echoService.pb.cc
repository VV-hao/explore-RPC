// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: echoService.proto

#include "echoService.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace example {
class RequestDataDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<RequestData>
      _instance;
} _RequestData_default_instance_;
class ResponseDataDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ResponseData>
      _instance;
} _ResponseData_default_instance_;
}  // namespace example
namespace protobuf_echoService_2eproto {
static void InitDefaultsRequestData() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::example::_RequestData_default_instance_;
    new (ptr) ::example::RequestData();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::example::RequestData::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_RequestData =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsRequestData}, {}};

static void InitDefaultsResponseData() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::example::_ResponseData_default_instance_;
    new (ptr) ::example::ResponseData();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::example::ResponseData::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_ResponseData =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsResponseData}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_RequestData.base);
  ::google::protobuf::internal::InitSCC(&scc_info_ResponseData.base);
}

::google::protobuf::Metadata file_level_metadata[2];
const ::google::protobuf::ServiceDescriptor* file_level_service_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::example::RequestData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::example::RequestData, data_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::example::ResponseData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::example::ResponseData, data_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::example::RequestData)},
  { 6, -1, sizeof(::example::ResponseData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::example::_RequestData_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::example::_ResponseData_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "echoService.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, file_level_service_descriptors);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\021echoService.proto\022\007example\"\033\n\013RequestD"
      "ata\022\014\n\004data\030\001 \001(\t\"\034\n\014ResponseData\022\014\n\004dat"
      "a\030\001 \001(\t2E\n\016ExampleService\0223\n\004Echo\022\024.exam"
      "ple.RequestData\032\025.example.ResponseDataB\003"
      "\200\001\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 171);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "echoService.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_echoService_2eproto
namespace example {

// ===================================================================

void RequestData::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int RequestData::kDataFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

RequestData::RequestData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_echoService_2eproto::scc_info_RequestData.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:example.RequestData)
}
RequestData::RequestData(const RequestData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.data().size() > 0) {
    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  // @@protoc_insertion_point(copy_constructor:example.RequestData)
}

void RequestData::SharedCtor() {
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

RequestData::~RequestData() {
  // @@protoc_insertion_point(destructor:example.RequestData)
  SharedDtor();
}

void RequestData::SharedDtor() {
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void RequestData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* RequestData::descriptor() {
  ::protobuf_echoService_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_echoService_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const RequestData& RequestData::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_echoService_2eproto::scc_info_RequestData.base);
  return *internal_default_instance();
}


void RequestData::Clear() {
// @@protoc_insertion_point(message_clear_start:example.RequestData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool RequestData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:example.RequestData)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string data = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_data()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->data().data(), static_cast<int>(this->data().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "example.RequestData.data"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:example.RequestData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:example.RequestData)
  return false;
#undef DO_
}

void RequestData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:example.RequestData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string data = 1;
  if (this->data().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "example.RequestData.data");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->data(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:example.RequestData)
}

::google::protobuf::uint8* RequestData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:example.RequestData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string data = 1;
  if (this->data().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "example.RequestData.data");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->data(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:example.RequestData)
  return target;
}

size_t RequestData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:example.RequestData)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string data = 1;
  if (this->data().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->data());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void RequestData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:example.RequestData)
  GOOGLE_DCHECK_NE(&from, this);
  const RequestData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const RequestData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:example.RequestData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:example.RequestData)
    MergeFrom(*source);
  }
}

void RequestData::MergeFrom(const RequestData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:example.RequestData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.data().size() > 0) {

    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
}

void RequestData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:example.RequestData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RequestData::CopyFrom(const RequestData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:example.RequestData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RequestData::IsInitialized() const {
  return true;
}

void RequestData::Swap(RequestData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void RequestData::InternalSwap(RequestData* other) {
  using std::swap;
  data_.Swap(&other->data_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata RequestData::GetMetadata() const {
  protobuf_echoService_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_echoService_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void ResponseData::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ResponseData::kDataFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ResponseData::ResponseData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_echoService_2eproto::scc_info_ResponseData.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:example.ResponseData)
}
ResponseData::ResponseData(const ResponseData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.data().size() > 0) {
    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  // @@protoc_insertion_point(copy_constructor:example.ResponseData)
}

void ResponseData::SharedCtor() {
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

ResponseData::~ResponseData() {
  // @@protoc_insertion_point(destructor:example.ResponseData)
  SharedDtor();
}

void ResponseData::SharedDtor() {
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void ResponseData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* ResponseData::descriptor() {
  ::protobuf_echoService_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_echoService_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ResponseData& ResponseData::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_echoService_2eproto::scc_info_ResponseData.base);
  return *internal_default_instance();
}


void ResponseData::Clear() {
// @@protoc_insertion_point(message_clear_start:example.ResponseData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool ResponseData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:example.ResponseData)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string data = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_data()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->data().data(), static_cast<int>(this->data().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "example.ResponseData.data"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:example.ResponseData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:example.ResponseData)
  return false;
#undef DO_
}

void ResponseData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:example.ResponseData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string data = 1;
  if (this->data().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "example.ResponseData.data");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->data(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:example.ResponseData)
}

::google::protobuf::uint8* ResponseData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:example.ResponseData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string data = 1;
  if (this->data().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->data().data(), static_cast<int>(this->data().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "example.ResponseData.data");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->data(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:example.ResponseData)
  return target;
}

size_t ResponseData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:example.ResponseData)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string data = 1;
  if (this->data().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->data());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ResponseData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:example.ResponseData)
  GOOGLE_DCHECK_NE(&from, this);
  const ResponseData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ResponseData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:example.ResponseData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:example.ResponseData)
    MergeFrom(*source);
  }
}

void ResponseData::MergeFrom(const ResponseData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:example.ResponseData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.data().size() > 0) {

    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
}

void ResponseData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:example.ResponseData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ResponseData::CopyFrom(const ResponseData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:example.ResponseData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ResponseData::IsInitialized() const {
  return true;
}

void ResponseData::Swap(ResponseData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ResponseData::InternalSwap(ResponseData* other) {
  using std::swap;
  data_.Swap(&other->data_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata ResponseData::GetMetadata() const {
  protobuf_echoService_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_echoService_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

ExampleService::~ExampleService() {}

const ::google::protobuf::ServiceDescriptor* ExampleService::descriptor() {
  protobuf_echoService_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_echoService_2eproto::file_level_service_descriptors[0];
}

const ::google::protobuf::ServiceDescriptor* ExampleService::GetDescriptor() {
  return descriptor();
}

void ExampleService::Echo(::google::protobuf::RpcController* controller,
                         const ::example::RequestData*,
                         ::example::ResponseData*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method Echo() not implemented.");
  done->Run();
}

void ExampleService::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                             ::google::protobuf::RpcController* controller,
                             const ::google::protobuf::Message* request,
                             ::google::protobuf::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), protobuf_echoService_2eproto::file_level_service_descriptors[0]);
  switch(method->index()) {
    case 0:
      Echo(controller,
             ::google::protobuf::down_cast<const ::example::RequestData*>(request),
             ::google::protobuf::down_cast< ::example::ResponseData*>(response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::google::protobuf::Message& ExampleService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::example::RequestData::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::google::protobuf::Message& ExampleService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::example::ResponseData::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

ExampleService_Stub::ExampleService_Stub(::google::protobuf::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
ExampleService_Stub::ExampleService_Stub(
    ::google::protobuf::RpcChannel* channel,
    ::google::protobuf::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::google::protobuf::Service::STUB_OWNS_CHANNEL) {}
ExampleService_Stub::~ExampleService_Stub() {
  if (owns_channel_) delete channel_;
}

void ExampleService_Stub::Echo(::google::protobuf::RpcController* controller,
                              const ::example::RequestData* request,
                              ::example::ResponseData* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace example
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::example::RequestData* Arena::CreateMaybeMessage< ::example::RequestData >(Arena* arena) {
  return Arena::CreateInternal< ::example::RequestData >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::example::ResponseData* Arena::CreateMaybeMessage< ::example::ResponseData >(Arena* arena) {
  return Arena::CreateInternal< ::example::ResponseData >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
