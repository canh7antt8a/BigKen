// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: instant_message.proto

#ifndef PROTOBUF_instant_5fmessage_2eproto__INCLUDED
#define PROTOBUF_instant_5fmessage_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_instant_5fmessage_2eproto();
void protobuf_AssignDesc_instant_5fmessage_2eproto();
void protobuf_ShutdownFile_instant_5fmessage_2eproto();

class BINInstantMessageRequest;
class BINInstantMessageResponse;

// ===================================================================

class BINInstantMessageRequest : public ::google::protobuf::Message {
 public:
  BINInstantMessageRequest();
  virtual ~BINInstantMessageRequest();

  BINInstantMessageRequest(const BINInstantMessageRequest& from);

  inline BINInstantMessageRequest& operator=(const BINInstantMessageRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BINInstantMessageRequest& default_instance();

  void Swap(BINInstantMessageRequest* other);

  // implements Message ----------------------------------------------

  BINInstantMessageRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINInstantMessageRequest& from);
  void MergeFrom(const BINInstantMessageRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 scope = 1;
  inline bool has_scope() const;
  inline void clear_scope();
  static const int kScopeFieldNumber = 1;
  inline ::google::protobuf::int32 scope() const;
  inline void set_scope(::google::protobuf::int32 value);

  // required string instantMessage = 2;
  inline bool has_instantmessage() const;
  inline void clear_instantmessage();
  static const int kInstantMessageFieldNumber = 2;
  inline const ::std::string& instantmessage() const;
  inline void set_instantmessage(const ::std::string& value);
  inline void set_instantmessage(const char* value);
  inline void set_instantmessage(const char* value, size_t size);
  inline ::std::string* mutable_instantmessage();
  inline ::std::string* release_instantmessage();
  inline void set_allocated_instantmessage(::std::string* instantmessage);

  // optional string receiverUserName = 3;
  inline bool has_receiverusername() const;
  inline void clear_receiverusername();
  static const int kReceiverUserNameFieldNumber = 3;
  inline const ::std::string& receiverusername() const;
  inline void set_receiverusername(const ::std::string& value);
  inline void set_receiverusername(const char* value);
  inline void set_receiverusername(const char* value, size_t size);
  inline ::std::string* mutable_receiverusername();
  inline ::std::string* release_receiverusername();
  inline void set_allocated_receiverusername(::std::string* receiverusername);

  // optional int64 receiverUserId = 4;
  inline bool has_receiveruserid() const;
  inline void clear_receiveruserid();
  static const int kReceiverUserIdFieldNumber = 4;
  inline ::google::protobuf::int64 receiveruserid() const;
  inline void set_receiveruserid(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:BINInstantMessageRequest)
 private:
  inline void set_has_scope();
  inline void clear_has_scope();
  inline void set_has_instantmessage();
  inline void clear_has_instantmessage();
  inline void set_has_receiverusername();
  inline void clear_has_receiverusername();
  inline void set_has_receiveruserid();
  inline void clear_has_receiveruserid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* instantmessage_;
  ::std::string* receiverusername_;
  ::google::protobuf::int64 receiveruserid_;
  ::google::protobuf::int32 scope_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_instant_5fmessage_2eproto();
  friend void protobuf_AssignDesc_instant_5fmessage_2eproto();
  friend void protobuf_ShutdownFile_instant_5fmessage_2eproto();

  void InitAsDefaultInstance();
  static BINInstantMessageRequest* default_instance_;
};
// -------------------------------------------------------------------

class BINInstantMessageResponse : public ::google::protobuf::Message {
 public:
  BINInstantMessageResponse();
  virtual ~BINInstantMessageResponse();

  BINInstantMessageResponse(const BINInstantMessageResponse& from);

  inline BINInstantMessageResponse& operator=(const BINInstantMessageResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const BINInstantMessageResponse& default_instance();

  void Swap(BINInstantMessageResponse* other);

  // implements Message ----------------------------------------------

  BINInstantMessageResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINInstantMessageResponse& from);
  void MergeFrom(const BINInstantMessageResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required bool responseCode = 1;
  inline bool has_responsecode() const;
  inline void clear_responsecode();
  static const int kResponseCodeFieldNumber = 1;
  inline bool responsecode() const;
  inline void set_responsecode(bool value);

  // optional string message = 2;
  inline bool has_message() const;
  inline void clear_message();
  static const int kMessageFieldNumber = 2;
  inline const ::std::string& message() const;
  inline void set_message(const ::std::string& value);
  inline void set_message(const char* value);
  inline void set_message(const char* value, size_t size);
  inline ::std::string* mutable_message();
  inline ::std::string* release_message();
  inline void set_allocated_message(::std::string* message);

  // optional int32 scope = 3;
  inline bool has_scope() const;
  inline void clear_scope();
  static const int kScopeFieldNumber = 3;
  inline ::google::protobuf::int32 scope() const;
  inline void set_scope(::google::protobuf::int32 value);

  // optional string senderUserName = 4;
  inline bool has_senderusername() const;
  inline void clear_senderusername();
  static const int kSenderUserNameFieldNumber = 4;
  inline const ::std::string& senderusername() const;
  inline void set_senderusername(const ::std::string& value);
  inline void set_senderusername(const char* value);
  inline void set_senderusername(const char* value, size_t size);
  inline ::std::string* mutable_senderusername();
  inline ::std::string* release_senderusername();
  inline void set_allocated_senderusername(::std::string* senderusername);

  // optional int64 senderUserId = 5;
  inline bool has_senderuserid() const;
  inline void clear_senderuserid();
  static const int kSenderUserIdFieldNumber = 5;
  inline ::google::protobuf::int64 senderuserid() const;
  inline void set_senderuserid(::google::protobuf::int64 value);

  // optional string instantMessage = 6;
  inline bool has_instantmessage() const;
  inline void clear_instantmessage();
  static const int kInstantMessageFieldNumber = 6;
  inline const ::std::string& instantmessage() const;
  inline void set_instantmessage(const ::std::string& value);
  inline void set_instantmessage(const char* value);
  inline void set_instantmessage(const char* value, size_t size);
  inline ::std::string* mutable_instantmessage();
  inline ::std::string* release_instantmessage();
  inline void set_allocated_instantmessage(::std::string* instantmessage);

  // optional int64 sentTime = 7;
  inline bool has_senttime() const;
  inline void clear_senttime();
  static const int kSentTimeFieldNumber = 7;
  inline ::google::protobuf::int64 senttime() const;
  inline void set_senttime(::google::protobuf::int64 value);

  // optional int32 zoneId = 8;
  inline bool has_zoneid() const;
  inline void clear_zoneid();
  static const int kZoneIdFieldNumber = 8;
  inline ::google::protobuf::int32 zoneid() const;
  inline void set_zoneid(::google::protobuf::int32 value);

  // optional int32 roomIndex = 9;
  inline bool has_roomindex() const;
  inline void clear_roomindex();
  static const int kRoomIndexFieldNumber = 9;
  inline ::google::protobuf::int32 roomindex() const;
  inline void set_roomindex(::google::protobuf::int32 value);

  // optional string receiverUserName = 10;
  inline bool has_receiverusername() const;
  inline void clear_receiverusername();
  static const int kReceiverUserNameFieldNumber = 10;
  inline const ::std::string& receiverusername() const;
  inline void set_receiverusername(const ::std::string& value);
  inline void set_receiverusername(const char* value);
  inline void set_receiverusername(const char* value, size_t size);
  inline ::std::string* mutable_receiverusername();
  inline ::std::string* release_receiverusername();
  inline void set_allocated_receiverusername(::std::string* receiverusername);

  // optional int64 receiverUserId = 11;
  inline bool has_receiveruserid() const;
  inline void clear_receiveruserid();
  static const int kReceiverUserIdFieldNumber = 11;
  inline ::google::protobuf::int64 receiveruserid() const;
  inline void set_receiveruserid(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:BINInstantMessageResponse)
 private:
  inline void set_has_responsecode();
  inline void clear_has_responsecode();
  inline void set_has_message();
  inline void clear_has_message();
  inline void set_has_scope();
  inline void clear_has_scope();
  inline void set_has_senderusername();
  inline void clear_has_senderusername();
  inline void set_has_senderuserid();
  inline void clear_has_senderuserid();
  inline void set_has_instantmessage();
  inline void clear_has_instantmessage();
  inline void set_has_senttime();
  inline void clear_has_senttime();
  inline void set_has_zoneid();
  inline void clear_has_zoneid();
  inline void set_has_roomindex();
  inline void clear_has_roomindex();
  inline void set_has_receiverusername();
  inline void clear_has_receiverusername();
  inline void set_has_receiveruserid();
  inline void clear_has_receiveruserid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* message_;
  bool responsecode_;
  ::google::protobuf::int32 scope_;
  ::std::string* senderusername_;
  ::google::protobuf::int64 senderuserid_;
  ::std::string* instantmessage_;
  ::google::protobuf::int64 senttime_;
  ::google::protobuf::int32 zoneid_;
  ::google::protobuf::int32 roomindex_;
  ::std::string* receiverusername_;
  ::google::protobuf::int64 receiveruserid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(11 + 31) / 32];

  friend void  protobuf_AddDesc_instant_5fmessage_2eproto();
  friend void protobuf_AssignDesc_instant_5fmessage_2eproto();
  friend void protobuf_ShutdownFile_instant_5fmessage_2eproto();

  void InitAsDefaultInstance();
  static BINInstantMessageResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// BINInstantMessageRequest

// required int32 scope = 1;
inline bool BINInstantMessageRequest::has_scope() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINInstantMessageRequest::set_has_scope() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINInstantMessageRequest::clear_has_scope() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINInstantMessageRequest::clear_scope() {
  scope_ = 0;
  clear_has_scope();
}
inline ::google::protobuf::int32 BINInstantMessageRequest::scope() const {
  return scope_;
}
inline void BINInstantMessageRequest::set_scope(::google::protobuf::int32 value) {
  set_has_scope();
  scope_ = value;
}

// required string instantMessage = 2;
inline bool BINInstantMessageRequest::has_instantmessage() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BINInstantMessageRequest::set_has_instantmessage() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BINInstantMessageRequest::clear_has_instantmessage() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BINInstantMessageRequest::clear_instantmessage() {
  if (instantmessage_ != &::google::protobuf::internal::kEmptyString) {
    instantmessage_->clear();
  }
  clear_has_instantmessage();
}
inline const ::std::string& BINInstantMessageRequest::instantmessage() const {
  return *instantmessage_;
}
inline void BINInstantMessageRequest::set_instantmessage(const ::std::string& value) {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  instantmessage_->assign(value);
}
inline void BINInstantMessageRequest::set_instantmessage(const char* value) {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  instantmessage_->assign(value);
}
inline void BINInstantMessageRequest::set_instantmessage(const char* value, size_t size) {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  instantmessage_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINInstantMessageRequest::mutable_instantmessage() {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  return instantmessage_;
}
inline ::std::string* BINInstantMessageRequest::release_instantmessage() {
  clear_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = instantmessage_;
    instantmessage_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINInstantMessageRequest::set_allocated_instantmessage(::std::string* instantmessage) {
  if (instantmessage_ != &::google::protobuf::internal::kEmptyString) {
    delete instantmessage_;
  }
  if (instantmessage) {
    set_has_instantmessage();
    instantmessage_ = instantmessage;
  } else {
    clear_has_instantmessage();
    instantmessage_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string receiverUserName = 3;
inline bool BINInstantMessageRequest::has_receiverusername() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BINInstantMessageRequest::set_has_receiverusername() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BINInstantMessageRequest::clear_has_receiverusername() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BINInstantMessageRequest::clear_receiverusername() {
  if (receiverusername_ != &::google::protobuf::internal::kEmptyString) {
    receiverusername_->clear();
  }
  clear_has_receiverusername();
}
inline const ::std::string& BINInstantMessageRequest::receiverusername() const {
  return *receiverusername_;
}
inline void BINInstantMessageRequest::set_receiverusername(const ::std::string& value) {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  receiverusername_->assign(value);
}
inline void BINInstantMessageRequest::set_receiverusername(const char* value) {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  receiverusername_->assign(value);
}
inline void BINInstantMessageRequest::set_receiverusername(const char* value, size_t size) {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  receiverusername_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINInstantMessageRequest::mutable_receiverusername() {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  return receiverusername_;
}
inline ::std::string* BINInstantMessageRequest::release_receiverusername() {
  clear_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = receiverusername_;
    receiverusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINInstantMessageRequest::set_allocated_receiverusername(::std::string* receiverusername) {
  if (receiverusername_ != &::google::protobuf::internal::kEmptyString) {
    delete receiverusername_;
  }
  if (receiverusername) {
    set_has_receiverusername();
    receiverusername_ = receiverusername;
  } else {
    clear_has_receiverusername();
    receiverusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int64 receiverUserId = 4;
inline bool BINInstantMessageRequest::has_receiveruserid() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BINInstantMessageRequest::set_has_receiveruserid() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BINInstantMessageRequest::clear_has_receiveruserid() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BINInstantMessageRequest::clear_receiveruserid() {
  receiveruserid_ = GOOGLE_LONGLONG(0);
  clear_has_receiveruserid();
}
inline ::google::protobuf::int64 BINInstantMessageRequest::receiveruserid() const {
  return receiveruserid_;
}
inline void BINInstantMessageRequest::set_receiveruserid(::google::protobuf::int64 value) {
  set_has_receiveruserid();
  receiveruserid_ = value;
}

// -------------------------------------------------------------------

// BINInstantMessageResponse

// required bool responseCode = 1;
inline bool BINInstantMessageResponse::has_responsecode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINInstantMessageResponse::set_has_responsecode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINInstantMessageResponse::clear_has_responsecode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINInstantMessageResponse::clear_responsecode() {
  responsecode_ = false;
  clear_has_responsecode();
}
inline bool BINInstantMessageResponse::responsecode() const {
  return responsecode_;
}
inline void BINInstantMessageResponse::set_responsecode(bool value) {
  set_has_responsecode();
  responsecode_ = value;
}

// optional string message = 2;
inline bool BINInstantMessageResponse::has_message() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BINInstantMessageResponse::set_has_message() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BINInstantMessageResponse::clear_has_message() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BINInstantMessageResponse::clear_message() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    message_->clear();
  }
  clear_has_message();
}
inline const ::std::string& BINInstantMessageResponse::message() const {
  return *message_;
}
inline void BINInstantMessageResponse::set_message(const ::std::string& value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void BINInstantMessageResponse::set_message(const char* value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void BINInstantMessageResponse::set_message(const char* value, size_t size) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINInstantMessageResponse::mutable_message() {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  return message_;
}
inline ::std::string* BINInstantMessageResponse::release_message() {
  clear_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = message_;
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINInstantMessageResponse::set_allocated_message(::std::string* message) {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    delete message_;
  }
  if (message) {
    set_has_message();
    message_ = message;
  } else {
    clear_has_message();
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int32 scope = 3;
inline bool BINInstantMessageResponse::has_scope() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BINInstantMessageResponse::set_has_scope() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BINInstantMessageResponse::clear_has_scope() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BINInstantMessageResponse::clear_scope() {
  scope_ = 0;
  clear_has_scope();
}
inline ::google::protobuf::int32 BINInstantMessageResponse::scope() const {
  return scope_;
}
inline void BINInstantMessageResponse::set_scope(::google::protobuf::int32 value) {
  set_has_scope();
  scope_ = value;
}

// optional string senderUserName = 4;
inline bool BINInstantMessageResponse::has_senderusername() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BINInstantMessageResponse::set_has_senderusername() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BINInstantMessageResponse::clear_has_senderusername() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BINInstantMessageResponse::clear_senderusername() {
  if (senderusername_ != &::google::protobuf::internal::kEmptyString) {
    senderusername_->clear();
  }
  clear_has_senderusername();
}
inline const ::std::string& BINInstantMessageResponse::senderusername() const {
  return *senderusername_;
}
inline void BINInstantMessageResponse::set_senderusername(const ::std::string& value) {
  set_has_senderusername();
  if (senderusername_ == &::google::protobuf::internal::kEmptyString) {
    senderusername_ = new ::std::string;
  }
  senderusername_->assign(value);
}
inline void BINInstantMessageResponse::set_senderusername(const char* value) {
  set_has_senderusername();
  if (senderusername_ == &::google::protobuf::internal::kEmptyString) {
    senderusername_ = new ::std::string;
  }
  senderusername_->assign(value);
}
inline void BINInstantMessageResponse::set_senderusername(const char* value, size_t size) {
  set_has_senderusername();
  if (senderusername_ == &::google::protobuf::internal::kEmptyString) {
    senderusername_ = new ::std::string;
  }
  senderusername_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINInstantMessageResponse::mutable_senderusername() {
  set_has_senderusername();
  if (senderusername_ == &::google::protobuf::internal::kEmptyString) {
    senderusername_ = new ::std::string;
  }
  return senderusername_;
}
inline ::std::string* BINInstantMessageResponse::release_senderusername() {
  clear_has_senderusername();
  if (senderusername_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = senderusername_;
    senderusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINInstantMessageResponse::set_allocated_senderusername(::std::string* senderusername) {
  if (senderusername_ != &::google::protobuf::internal::kEmptyString) {
    delete senderusername_;
  }
  if (senderusername) {
    set_has_senderusername();
    senderusername_ = senderusername;
  } else {
    clear_has_senderusername();
    senderusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int64 senderUserId = 5;
inline bool BINInstantMessageResponse::has_senderuserid() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BINInstantMessageResponse::set_has_senderuserid() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BINInstantMessageResponse::clear_has_senderuserid() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BINInstantMessageResponse::clear_senderuserid() {
  senderuserid_ = GOOGLE_LONGLONG(0);
  clear_has_senderuserid();
}
inline ::google::protobuf::int64 BINInstantMessageResponse::senderuserid() const {
  return senderuserid_;
}
inline void BINInstantMessageResponse::set_senderuserid(::google::protobuf::int64 value) {
  set_has_senderuserid();
  senderuserid_ = value;
}

// optional string instantMessage = 6;
inline bool BINInstantMessageResponse::has_instantmessage() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void BINInstantMessageResponse::set_has_instantmessage() {
  _has_bits_[0] |= 0x00000020u;
}
inline void BINInstantMessageResponse::clear_has_instantmessage() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void BINInstantMessageResponse::clear_instantmessage() {
  if (instantmessage_ != &::google::protobuf::internal::kEmptyString) {
    instantmessage_->clear();
  }
  clear_has_instantmessage();
}
inline const ::std::string& BINInstantMessageResponse::instantmessage() const {
  return *instantmessage_;
}
inline void BINInstantMessageResponse::set_instantmessage(const ::std::string& value) {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  instantmessage_->assign(value);
}
inline void BINInstantMessageResponse::set_instantmessage(const char* value) {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  instantmessage_->assign(value);
}
inline void BINInstantMessageResponse::set_instantmessage(const char* value, size_t size) {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  instantmessage_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINInstantMessageResponse::mutable_instantmessage() {
  set_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    instantmessage_ = new ::std::string;
  }
  return instantmessage_;
}
inline ::std::string* BINInstantMessageResponse::release_instantmessage() {
  clear_has_instantmessage();
  if (instantmessage_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = instantmessage_;
    instantmessage_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINInstantMessageResponse::set_allocated_instantmessage(::std::string* instantmessage) {
  if (instantmessage_ != &::google::protobuf::internal::kEmptyString) {
    delete instantmessage_;
  }
  if (instantmessage) {
    set_has_instantmessage();
    instantmessage_ = instantmessage;
  } else {
    clear_has_instantmessage();
    instantmessage_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int64 sentTime = 7;
inline bool BINInstantMessageResponse::has_senttime() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void BINInstantMessageResponse::set_has_senttime() {
  _has_bits_[0] |= 0x00000040u;
}
inline void BINInstantMessageResponse::clear_has_senttime() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void BINInstantMessageResponse::clear_senttime() {
  senttime_ = GOOGLE_LONGLONG(0);
  clear_has_senttime();
}
inline ::google::protobuf::int64 BINInstantMessageResponse::senttime() const {
  return senttime_;
}
inline void BINInstantMessageResponse::set_senttime(::google::protobuf::int64 value) {
  set_has_senttime();
  senttime_ = value;
}

// optional int32 zoneId = 8;
inline bool BINInstantMessageResponse::has_zoneid() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
inline void BINInstantMessageResponse::set_has_zoneid() {
  _has_bits_[0] |= 0x00000080u;
}
inline void BINInstantMessageResponse::clear_has_zoneid() {
  _has_bits_[0] &= ~0x00000080u;
}
inline void BINInstantMessageResponse::clear_zoneid() {
  zoneid_ = 0;
  clear_has_zoneid();
}
inline ::google::protobuf::int32 BINInstantMessageResponse::zoneid() const {
  return zoneid_;
}
inline void BINInstantMessageResponse::set_zoneid(::google::protobuf::int32 value) {
  set_has_zoneid();
  zoneid_ = value;
}

// optional int32 roomIndex = 9;
inline bool BINInstantMessageResponse::has_roomindex() const {
  return (_has_bits_[0] & 0x00000100u) != 0;
}
inline void BINInstantMessageResponse::set_has_roomindex() {
  _has_bits_[0] |= 0x00000100u;
}
inline void BINInstantMessageResponse::clear_has_roomindex() {
  _has_bits_[0] &= ~0x00000100u;
}
inline void BINInstantMessageResponse::clear_roomindex() {
  roomindex_ = 0;
  clear_has_roomindex();
}
inline ::google::protobuf::int32 BINInstantMessageResponse::roomindex() const {
  return roomindex_;
}
inline void BINInstantMessageResponse::set_roomindex(::google::protobuf::int32 value) {
  set_has_roomindex();
  roomindex_ = value;
}

// optional string receiverUserName = 10;
inline bool BINInstantMessageResponse::has_receiverusername() const {
  return (_has_bits_[0] & 0x00000200u) != 0;
}
inline void BINInstantMessageResponse::set_has_receiverusername() {
  _has_bits_[0] |= 0x00000200u;
}
inline void BINInstantMessageResponse::clear_has_receiverusername() {
  _has_bits_[0] &= ~0x00000200u;
}
inline void BINInstantMessageResponse::clear_receiverusername() {
  if (receiverusername_ != &::google::protobuf::internal::kEmptyString) {
    receiverusername_->clear();
  }
  clear_has_receiverusername();
}
inline const ::std::string& BINInstantMessageResponse::receiverusername() const {
  return *receiverusername_;
}
inline void BINInstantMessageResponse::set_receiverusername(const ::std::string& value) {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  receiverusername_->assign(value);
}
inline void BINInstantMessageResponse::set_receiverusername(const char* value) {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  receiverusername_->assign(value);
}
inline void BINInstantMessageResponse::set_receiverusername(const char* value, size_t size) {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  receiverusername_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINInstantMessageResponse::mutable_receiverusername() {
  set_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    receiverusername_ = new ::std::string;
  }
  return receiverusername_;
}
inline ::std::string* BINInstantMessageResponse::release_receiverusername() {
  clear_has_receiverusername();
  if (receiverusername_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = receiverusername_;
    receiverusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINInstantMessageResponse::set_allocated_receiverusername(::std::string* receiverusername) {
  if (receiverusername_ != &::google::protobuf::internal::kEmptyString) {
    delete receiverusername_;
  }
  if (receiverusername) {
    set_has_receiverusername();
    receiverusername_ = receiverusername;
  } else {
    clear_has_receiverusername();
    receiverusername_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int64 receiverUserId = 11;
inline bool BINInstantMessageResponse::has_receiveruserid() const {
  return (_has_bits_[0] & 0x00000400u) != 0;
}
inline void BINInstantMessageResponse::set_has_receiveruserid() {
  _has_bits_[0] |= 0x00000400u;
}
inline void BINInstantMessageResponse::clear_has_receiveruserid() {
  _has_bits_[0] &= ~0x00000400u;
}
inline void BINInstantMessageResponse::clear_receiveruserid() {
  receiveruserid_ = GOOGLE_LONGLONG(0);
  clear_has_receiveruserid();
}
inline ::google::protobuf::int64 BINInstantMessageResponse::receiveruserid() const {
  return receiveruserid_;
}
inline void BINInstantMessageResponse::set_receiveruserid(::google::protobuf::int64 value) {
  set_has_receiveruserid();
  receiveruserid_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_instant_5fmessage_2eproto__INCLUDED
