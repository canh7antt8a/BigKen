// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: prepare_new_match.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "prepare_new_match.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* BINPrepareNewMatchRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BINPrepareNewMatchRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* BINPrepareNewMatchResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  BINPrepareNewMatchResponse_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_prepare_5fnew_5fmatch_2eproto() {
  protobuf_AddDesc_prepare_5fnew_5fmatch_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "prepare_new_match.proto");
  GOOGLE_CHECK(file != NULL);
  BINPrepareNewMatchRequest_descriptor_ = file->message_type(0);
  static const int BINPrepareNewMatchRequest_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchRequest, roomindex_),
  };
  BINPrepareNewMatchRequest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BINPrepareNewMatchRequest_descriptor_,
      BINPrepareNewMatchRequest::default_instance_,
      BINPrepareNewMatchRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchRequest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchRequest, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BINPrepareNewMatchRequest));
  BINPrepareNewMatchResponse_descriptor_ = file->message_type(1);
  static const int BINPrepareNewMatchResponse_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchResponse, responsecode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchResponse, message_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchResponse, countdowntimer_),
  };
  BINPrepareNewMatchResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      BINPrepareNewMatchResponse_descriptor_,
      BINPrepareNewMatchResponse::default_instance_,
      BINPrepareNewMatchResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(BINPrepareNewMatchResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(BINPrepareNewMatchResponse));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_prepare_5fnew_5fmatch_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BINPrepareNewMatchRequest_descriptor_, &BINPrepareNewMatchRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    BINPrepareNewMatchResponse_descriptor_, &BINPrepareNewMatchResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_prepare_5fnew_5fmatch_2eproto() {
  delete BINPrepareNewMatchRequest::default_instance_;
  delete BINPrepareNewMatchRequest_reflection_;
  delete BINPrepareNewMatchResponse::default_instance_;
  delete BINPrepareNewMatchResponse_reflection_;
}

void protobuf_AddDesc_prepare_5fnew_5fmatch_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\027prepare_new_match.proto\".\n\031BINPrepareN"
    "ewMatchRequest\022\021\n\troomIndex\030\001 \002(\005\"[\n\032BIN"
    "PrepareNewMatchResponse\022\024\n\014responseCode\030"
    "\001 \002(\010\022\017\n\007message\030\002 \001(\t\022\026\n\016countDownTimer"
    "\030\003 \001(\005B\036\n\034com.mi.game.network.data.bin", 198);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "prepare_new_match.proto", &protobuf_RegisterTypes);
  BINPrepareNewMatchRequest::default_instance_ = new BINPrepareNewMatchRequest();
  BINPrepareNewMatchResponse::default_instance_ = new BINPrepareNewMatchResponse();
  BINPrepareNewMatchRequest::default_instance_->InitAsDefaultInstance();
  BINPrepareNewMatchResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_prepare_5fnew_5fmatch_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_prepare_5fnew_5fmatch_2eproto {
  StaticDescriptorInitializer_prepare_5fnew_5fmatch_2eproto() {
    protobuf_AddDesc_prepare_5fnew_5fmatch_2eproto();
  }
} static_descriptor_initializer_prepare_5fnew_5fmatch_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int BINPrepareNewMatchRequest::kRoomIndexFieldNumber;
#endif  // !_MSC_VER

BINPrepareNewMatchRequest::BINPrepareNewMatchRequest()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void BINPrepareNewMatchRequest::InitAsDefaultInstance() {
}

BINPrepareNewMatchRequest::BINPrepareNewMatchRequest(const BINPrepareNewMatchRequest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void BINPrepareNewMatchRequest::SharedCtor() {
  _cached_size_ = 0;
  roomindex_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BINPrepareNewMatchRequest::~BINPrepareNewMatchRequest() {
  SharedDtor();
}

void BINPrepareNewMatchRequest::SharedDtor() {
  if (this != default_instance_) {
  }
}

void BINPrepareNewMatchRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BINPrepareNewMatchRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BINPrepareNewMatchRequest_descriptor_;
}

const BINPrepareNewMatchRequest& BINPrepareNewMatchRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_prepare_5fnew_5fmatch_2eproto();
  return *default_instance_;
}

BINPrepareNewMatchRequest* BINPrepareNewMatchRequest::default_instance_ = NULL;

BINPrepareNewMatchRequest* BINPrepareNewMatchRequest::New() const {
  return new BINPrepareNewMatchRequest;
}

void BINPrepareNewMatchRequest::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    roomindex_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BINPrepareNewMatchRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 roomIndex = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &roomindex_)));
          set_has_roomindex();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void BINPrepareNewMatchRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 roomIndex = 1;
  if (has_roomindex()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->roomindex(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* BINPrepareNewMatchRequest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 roomIndex = 1;
  if (has_roomindex()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->roomindex(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int BINPrepareNewMatchRequest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 roomIndex = 1;
    if (has_roomindex()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->roomindex());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BINPrepareNewMatchRequest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BINPrepareNewMatchRequest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BINPrepareNewMatchRequest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BINPrepareNewMatchRequest::MergeFrom(const BINPrepareNewMatchRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_roomindex()) {
      set_roomindex(from.roomindex());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BINPrepareNewMatchRequest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BINPrepareNewMatchRequest::CopyFrom(const BINPrepareNewMatchRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BINPrepareNewMatchRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void BINPrepareNewMatchRequest::Swap(BINPrepareNewMatchRequest* other) {
  if (other != this) {
    std::swap(roomindex_, other->roomindex_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BINPrepareNewMatchRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BINPrepareNewMatchRequest_descriptor_;
  metadata.reflection = BINPrepareNewMatchRequest_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int BINPrepareNewMatchResponse::kResponseCodeFieldNumber;
const int BINPrepareNewMatchResponse::kMessageFieldNumber;
const int BINPrepareNewMatchResponse::kCountDownTimerFieldNumber;
#endif  // !_MSC_VER

BINPrepareNewMatchResponse::BINPrepareNewMatchResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void BINPrepareNewMatchResponse::InitAsDefaultInstance() {
}

BINPrepareNewMatchResponse::BINPrepareNewMatchResponse(const BINPrepareNewMatchResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void BINPrepareNewMatchResponse::SharedCtor() {
  _cached_size_ = 0;
  responsecode_ = false;
  message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  countdowntimer_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

BINPrepareNewMatchResponse::~BINPrepareNewMatchResponse() {
  SharedDtor();
}

void BINPrepareNewMatchResponse::SharedDtor() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    delete message_;
  }
  if (this != default_instance_) {
  }
}

void BINPrepareNewMatchResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* BINPrepareNewMatchResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return BINPrepareNewMatchResponse_descriptor_;
}

const BINPrepareNewMatchResponse& BINPrepareNewMatchResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_prepare_5fnew_5fmatch_2eproto();
  return *default_instance_;
}

BINPrepareNewMatchResponse* BINPrepareNewMatchResponse::default_instance_ = NULL;

BINPrepareNewMatchResponse* BINPrepareNewMatchResponse::New() const {
  return new BINPrepareNewMatchResponse;
}

void BINPrepareNewMatchResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    responsecode_ = false;
    if (has_message()) {
      if (message_ != &::google::protobuf::internal::kEmptyString) {
        message_->clear();
      }
    }
    countdowntimer_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool BINPrepareNewMatchResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required bool responseCode = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &responsecode_)));
          set_has_responsecode();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_message;
        break;
      }

      // optional string message = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_message:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_message()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->message().data(), this->message().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_countDownTimer;
        break;
      }

      // optional int32 countDownTimer = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_countDownTimer:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &countdowntimer_)));
          set_has_countdowntimer();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void BINPrepareNewMatchResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required bool responseCode = 1;
  if (has_responsecode()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->responsecode(), output);
  }

  // optional string message = 2;
  if (has_message()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->message(), output);
  }

  // optional int32 countDownTimer = 3;
  if (has_countdowntimer()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->countdowntimer(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* BINPrepareNewMatchResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required bool responseCode = 1;
  if (has_responsecode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->responsecode(), target);
  }

  // optional string message = 2;
  if (has_message()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->message().data(), this->message().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->message(), target);
  }

  // optional int32 countDownTimer = 3;
  if (has_countdowntimer()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->countdowntimer(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int BINPrepareNewMatchResponse::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required bool responseCode = 1;
    if (has_responsecode()) {
      total_size += 1 + 1;
    }

    // optional string message = 2;
    if (has_message()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->message());
    }

    // optional int32 countDownTimer = 3;
    if (has_countdowntimer()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->countdowntimer());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void BINPrepareNewMatchResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const BINPrepareNewMatchResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const BINPrepareNewMatchResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void BINPrepareNewMatchResponse::MergeFrom(const BINPrepareNewMatchResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_responsecode()) {
      set_responsecode(from.responsecode());
    }
    if (from.has_message()) {
      set_message(from.message());
    }
    if (from.has_countdowntimer()) {
      set_countdowntimer(from.countdowntimer());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void BINPrepareNewMatchResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void BINPrepareNewMatchResponse::CopyFrom(const BINPrepareNewMatchResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool BINPrepareNewMatchResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void BINPrepareNewMatchResponse::Swap(BINPrepareNewMatchResponse* other) {
  if (other != this) {
    std::swap(responsecode_, other->responsecode_);
    std::swap(message_, other->message_);
    std::swap(countdowntimer_, other->countdowntimer_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata BINPrepareNewMatchResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = BINPrepareNewMatchResponse_descriptor_;
  metadata.reflection = BINPrepareNewMatchResponse_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
