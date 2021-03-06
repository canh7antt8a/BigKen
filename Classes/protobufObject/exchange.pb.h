// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: exchange.proto

#ifndef PROTOBUF_exchange_2eproto__INCLUDED
#define PROTOBUF_exchange_2eproto__INCLUDED

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
void  protobuf_AddDesc_exchange_2eproto();
void protobuf_AssignDesc_exchange_2eproto();
void protobuf_ShutdownFile_exchange_2eproto();

class BINAssetConfigRequest;
class BINAsset;
class BINAssetConfigResponse;
class BINExchangeAssetRequest;
class BINExchangeAssetResponse;

// ===================================================================

class BINAssetConfigRequest : public ::google::protobuf::Message {
 public:
  BINAssetConfigRequest();
  virtual ~BINAssetConfigRequest();

  BINAssetConfigRequest(const BINAssetConfigRequest& from);

  inline BINAssetConfigRequest& operator=(const BINAssetConfigRequest& from) {
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
  static const BINAssetConfigRequest& default_instance();

  void Swap(BINAssetConfigRequest* other);

  // implements Message ----------------------------------------------

  BINAssetConfigRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINAssetConfigRequest& from);
  void MergeFrom(const BINAssetConfigRequest& from);
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

  // required int32 type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:BINAssetConfigRequest)
 private:
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 type_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static BINAssetConfigRequest* default_instance_;
};
// -------------------------------------------------------------------

class BINAsset : public ::google::protobuf::Message {
 public:
  BINAsset();
  virtual ~BINAsset();

  BINAsset(const BINAsset& from);

  inline BINAsset& operator=(const BINAsset& from) {
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
  static const BINAsset& default_instance();

  void Swap(BINAsset* other);

  // implements Message ----------------------------------------------

  BINAsset* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINAsset& from);
  void MergeFrom(const BINAsset& from);
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

  // required int32 assetId = 1;
  inline bool has_assetid() const;
  inline void clear_assetid();
  static const int kAssetIdFieldNumber = 1;
  inline ::google::protobuf::int32 assetid() const;
  inline void set_assetid(::google::protobuf::int32 value);

  // required int32 type = 2;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 2;
  inline ::google::protobuf::int32 type() const;
  inline void set_type(::google::protobuf::int32 value);

  // required string provider = 3;
  inline bool has_provider() const;
  inline void clear_provider();
  static const int kProviderFieldNumber = 3;
  inline const ::std::string& provider() const;
  inline void set_provider(const ::std::string& value);
  inline void set_provider(const char* value);
  inline void set_provider(const char* value, size_t size);
  inline ::std::string* mutable_provider();
  inline ::std::string* release_provider();
  inline void set_allocated_provider(::std::string* provider);

  // optional int64 parValue = 4;
  inline bool has_parvalue() const;
  inline void clear_parvalue();
  static const int kParValueFieldNumber = 4;
  inline ::google::protobuf::int64 parvalue() const;
  inline void set_parvalue(::google::protobuf::int64 value);

  // required int64 cashValue = 5;
  inline bool has_cashvalue() const;
  inline void clear_cashvalue();
  static const int kCashValueFieldNumber = 5;
  inline ::google::protobuf::int64 cashvalue() const;
  inline void set_cashvalue(::google::protobuf::int64 value);

  // required int32 trustedIndex = 6;
  inline bool has_trustedindex() const;
  inline void clear_trustedindex();
  static const int kTrustedIndexFieldNumber = 6;
  inline ::google::protobuf::int32 trustedindex() const;
  inline void set_trustedindex(::google::protobuf::int32 value);

  // required bool active = 7;
  inline bool has_active() const;
  inline void clear_active();
  static const int kActiveFieldNumber = 7;
  inline bool active() const;
  inline void set_active(bool value);

  // @@protoc_insertion_point(class_scope:BINAsset)
 private:
  inline void set_has_assetid();
  inline void clear_has_assetid();
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_provider();
  inline void clear_has_provider();
  inline void set_has_parvalue();
  inline void clear_has_parvalue();
  inline void set_has_cashvalue();
  inline void clear_has_cashvalue();
  inline void set_has_trustedindex();
  inline void clear_has_trustedindex();
  inline void set_has_active();
  inline void clear_has_active();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 assetid_;
  ::google::protobuf::int32 type_;
  ::std::string* provider_;
  ::google::protobuf::int64 parvalue_;
  ::google::protobuf::int64 cashvalue_;
  ::google::protobuf::int32 trustedindex_;
  bool active_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(7 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static BINAsset* default_instance_;
};
// -------------------------------------------------------------------

class BINAssetConfigResponse : public ::google::protobuf::Message {
 public:
  BINAssetConfigResponse();
  virtual ~BINAssetConfigResponse();

  BINAssetConfigResponse(const BINAssetConfigResponse& from);

  inline BINAssetConfigResponse& operator=(const BINAssetConfigResponse& from) {
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
  static const BINAssetConfigResponse& default_instance();

  void Swap(BINAssetConfigResponse* other);

  // implements Message ----------------------------------------------

  BINAssetConfigResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINAssetConfigResponse& from);
  void MergeFrom(const BINAssetConfigResponse& from);
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

  // repeated .BINAsset assets = 3;
  inline int assets_size() const;
  inline void clear_assets();
  static const int kAssetsFieldNumber = 3;
  inline const ::BINAsset& assets(int index) const;
  inline ::BINAsset* mutable_assets(int index);
  inline ::BINAsset* add_assets();
  inline const ::google::protobuf::RepeatedPtrField< ::BINAsset >&
      assets() const;
  inline ::google::protobuf::RepeatedPtrField< ::BINAsset >*
      mutable_assets();

  // @@protoc_insertion_point(class_scope:BINAssetConfigResponse)
 private:
  inline void set_has_responsecode();
  inline void clear_has_responsecode();
  inline void set_has_message();
  inline void clear_has_message();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* message_;
  ::google::protobuf::RepeatedPtrField< ::BINAsset > assets_;
  bool responsecode_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static BINAssetConfigResponse* default_instance_;
};
// -------------------------------------------------------------------

class BINExchangeAssetRequest : public ::google::protobuf::Message {
 public:
  BINExchangeAssetRequest();
  virtual ~BINExchangeAssetRequest();

  BINExchangeAssetRequest(const BINExchangeAssetRequest& from);

  inline BINExchangeAssetRequest& operator=(const BINExchangeAssetRequest& from) {
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
  static const BINExchangeAssetRequest& default_instance();

  void Swap(BINExchangeAssetRequest* other);

  // implements Message ----------------------------------------------

  BINExchangeAssetRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINExchangeAssetRequest& from);
  void MergeFrom(const BINExchangeAssetRequest& from);
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

  // required int32 assetId = 1;
  inline bool has_assetid() const;
  inline void clear_assetid();
  static const int kAssetIdFieldNumber = 1;
  inline ::google::protobuf::int32 assetid() const;
  inline void set_assetid(::google::protobuf::int32 value);

  // required int32 amount = 2;
  inline bool has_amount() const;
  inline void clear_amount();
  static const int kAmountFieldNumber = 2;
  inline ::google::protobuf::int32 amount() const;
  inline void set_amount(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:BINExchangeAssetRequest)
 private:
  inline void set_has_assetid();
  inline void clear_has_assetid();
  inline void set_has_amount();
  inline void clear_has_amount();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 assetid_;
  ::google::protobuf::int32 amount_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static BINExchangeAssetRequest* default_instance_;
};
// -------------------------------------------------------------------

class BINExchangeAssetResponse : public ::google::protobuf::Message {
 public:
  BINExchangeAssetResponse();
  virtual ~BINExchangeAssetResponse();

  BINExchangeAssetResponse(const BINExchangeAssetResponse& from);

  inline BINExchangeAssetResponse& operator=(const BINExchangeAssetResponse& from) {
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
  static const BINExchangeAssetResponse& default_instance();

  void Swap(BINExchangeAssetResponse* other);

  // implements Message ----------------------------------------------

  BINExchangeAssetResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BINExchangeAssetResponse& from);
  void MergeFrom(const BINExchangeAssetResponse& from);
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

  // @@protoc_insertion_point(class_scope:BINExchangeAssetResponse)
 private:
  inline void set_has_responsecode();
  inline void clear_has_responsecode();
  inline void set_has_message();
  inline void clear_has_message();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* message_;
  bool responsecode_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_exchange_2eproto();
  friend void protobuf_AssignDesc_exchange_2eproto();
  friend void protobuf_ShutdownFile_exchange_2eproto();

  void InitAsDefaultInstance();
  static BINExchangeAssetResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// BINAssetConfigRequest

// required int32 type = 1;
inline bool BINAssetConfigRequest::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINAssetConfigRequest::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINAssetConfigRequest::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINAssetConfigRequest::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 BINAssetConfigRequest::type() const {
  return type_;
}
inline void BINAssetConfigRequest::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
}

// -------------------------------------------------------------------

// BINAsset

// required int32 assetId = 1;
inline bool BINAsset::has_assetid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINAsset::set_has_assetid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINAsset::clear_has_assetid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINAsset::clear_assetid() {
  assetid_ = 0;
  clear_has_assetid();
}
inline ::google::protobuf::int32 BINAsset::assetid() const {
  return assetid_;
}
inline void BINAsset::set_assetid(::google::protobuf::int32 value) {
  set_has_assetid();
  assetid_ = value;
}

// required int32 type = 2;
inline bool BINAsset::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BINAsset::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BINAsset::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BINAsset::clear_type() {
  type_ = 0;
  clear_has_type();
}
inline ::google::protobuf::int32 BINAsset::type() const {
  return type_;
}
inline void BINAsset::set_type(::google::protobuf::int32 value) {
  set_has_type();
  type_ = value;
}

// required string provider = 3;
inline bool BINAsset::has_provider() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void BINAsset::set_has_provider() {
  _has_bits_[0] |= 0x00000004u;
}
inline void BINAsset::clear_has_provider() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void BINAsset::clear_provider() {
  if (provider_ != &::google::protobuf::internal::kEmptyString) {
    provider_->clear();
  }
  clear_has_provider();
}
inline const ::std::string& BINAsset::provider() const {
  return *provider_;
}
inline void BINAsset::set_provider(const ::std::string& value) {
  set_has_provider();
  if (provider_ == &::google::protobuf::internal::kEmptyString) {
    provider_ = new ::std::string;
  }
  provider_->assign(value);
}
inline void BINAsset::set_provider(const char* value) {
  set_has_provider();
  if (provider_ == &::google::protobuf::internal::kEmptyString) {
    provider_ = new ::std::string;
  }
  provider_->assign(value);
}
inline void BINAsset::set_provider(const char* value, size_t size) {
  set_has_provider();
  if (provider_ == &::google::protobuf::internal::kEmptyString) {
    provider_ = new ::std::string;
  }
  provider_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINAsset::mutable_provider() {
  set_has_provider();
  if (provider_ == &::google::protobuf::internal::kEmptyString) {
    provider_ = new ::std::string;
  }
  return provider_;
}
inline ::std::string* BINAsset::release_provider() {
  clear_has_provider();
  if (provider_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = provider_;
    provider_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINAsset::set_allocated_provider(::std::string* provider) {
  if (provider_ != &::google::protobuf::internal::kEmptyString) {
    delete provider_;
  }
  if (provider) {
    set_has_provider();
    provider_ = provider;
  } else {
    clear_has_provider();
    provider_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional int64 parValue = 4;
inline bool BINAsset::has_parvalue() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void BINAsset::set_has_parvalue() {
  _has_bits_[0] |= 0x00000008u;
}
inline void BINAsset::clear_has_parvalue() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void BINAsset::clear_parvalue() {
  parvalue_ = GOOGLE_LONGLONG(0);
  clear_has_parvalue();
}
inline ::google::protobuf::int64 BINAsset::parvalue() const {
  return parvalue_;
}
inline void BINAsset::set_parvalue(::google::protobuf::int64 value) {
  set_has_parvalue();
  parvalue_ = value;
}

// required int64 cashValue = 5;
inline bool BINAsset::has_cashvalue() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void BINAsset::set_has_cashvalue() {
  _has_bits_[0] |= 0x00000010u;
}
inline void BINAsset::clear_has_cashvalue() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void BINAsset::clear_cashvalue() {
  cashvalue_ = GOOGLE_LONGLONG(0);
  clear_has_cashvalue();
}
inline ::google::protobuf::int64 BINAsset::cashvalue() const {
  return cashvalue_;
}
inline void BINAsset::set_cashvalue(::google::protobuf::int64 value) {
  set_has_cashvalue();
  cashvalue_ = value;
}

// required int32 trustedIndex = 6;
inline bool BINAsset::has_trustedindex() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void BINAsset::set_has_trustedindex() {
  _has_bits_[0] |= 0x00000020u;
}
inline void BINAsset::clear_has_trustedindex() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void BINAsset::clear_trustedindex() {
  trustedindex_ = 0;
  clear_has_trustedindex();
}
inline ::google::protobuf::int32 BINAsset::trustedindex() const {
  return trustedindex_;
}
inline void BINAsset::set_trustedindex(::google::protobuf::int32 value) {
  set_has_trustedindex();
  trustedindex_ = value;
}

// required bool active = 7;
inline bool BINAsset::has_active() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void BINAsset::set_has_active() {
  _has_bits_[0] |= 0x00000040u;
}
inline void BINAsset::clear_has_active() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void BINAsset::clear_active() {
  active_ = false;
  clear_has_active();
}
inline bool BINAsset::active() const {
  return active_;
}
inline void BINAsset::set_active(bool value) {
  set_has_active();
  active_ = value;
}

// -------------------------------------------------------------------

// BINAssetConfigResponse

// required bool responseCode = 1;
inline bool BINAssetConfigResponse::has_responsecode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINAssetConfigResponse::set_has_responsecode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINAssetConfigResponse::clear_has_responsecode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINAssetConfigResponse::clear_responsecode() {
  responsecode_ = false;
  clear_has_responsecode();
}
inline bool BINAssetConfigResponse::responsecode() const {
  return responsecode_;
}
inline void BINAssetConfigResponse::set_responsecode(bool value) {
  set_has_responsecode();
  responsecode_ = value;
}

// optional string message = 2;
inline bool BINAssetConfigResponse::has_message() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BINAssetConfigResponse::set_has_message() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BINAssetConfigResponse::clear_has_message() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BINAssetConfigResponse::clear_message() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    message_->clear();
  }
  clear_has_message();
}
inline const ::std::string& BINAssetConfigResponse::message() const {
  return *message_;
}
inline void BINAssetConfigResponse::set_message(const ::std::string& value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void BINAssetConfigResponse::set_message(const char* value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void BINAssetConfigResponse::set_message(const char* value, size_t size) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINAssetConfigResponse::mutable_message() {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  return message_;
}
inline ::std::string* BINAssetConfigResponse::release_message() {
  clear_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = message_;
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINAssetConfigResponse::set_allocated_message(::std::string* message) {
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

// repeated .BINAsset assets = 3;
inline int BINAssetConfigResponse::assets_size() const {
  return assets_.size();
}
inline void BINAssetConfigResponse::clear_assets() {
  assets_.Clear();
}
inline const ::BINAsset& BINAssetConfigResponse::assets(int index) const {
  return assets_.Get(index);
}
inline ::BINAsset* BINAssetConfigResponse::mutable_assets(int index) {
  return assets_.Mutable(index);
}
inline ::BINAsset* BINAssetConfigResponse::add_assets() {
  return assets_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::BINAsset >&
BINAssetConfigResponse::assets() const {
  return assets_;
}
inline ::google::protobuf::RepeatedPtrField< ::BINAsset >*
BINAssetConfigResponse::mutable_assets() {
  return &assets_;
}

// -------------------------------------------------------------------

// BINExchangeAssetRequest

// required int32 assetId = 1;
inline bool BINExchangeAssetRequest::has_assetid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINExchangeAssetRequest::set_has_assetid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINExchangeAssetRequest::clear_has_assetid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINExchangeAssetRequest::clear_assetid() {
  assetid_ = 0;
  clear_has_assetid();
}
inline ::google::protobuf::int32 BINExchangeAssetRequest::assetid() const {
  return assetid_;
}
inline void BINExchangeAssetRequest::set_assetid(::google::protobuf::int32 value) {
  set_has_assetid();
  assetid_ = value;
}

// required int32 amount = 2;
inline bool BINExchangeAssetRequest::has_amount() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BINExchangeAssetRequest::set_has_amount() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BINExchangeAssetRequest::clear_has_amount() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BINExchangeAssetRequest::clear_amount() {
  amount_ = 0;
  clear_has_amount();
}
inline ::google::protobuf::int32 BINExchangeAssetRequest::amount() const {
  return amount_;
}
inline void BINExchangeAssetRequest::set_amount(::google::protobuf::int32 value) {
  set_has_amount();
  amount_ = value;
}

// -------------------------------------------------------------------

// BINExchangeAssetResponse

// required bool responseCode = 1;
inline bool BINExchangeAssetResponse::has_responsecode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BINExchangeAssetResponse::set_has_responsecode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BINExchangeAssetResponse::clear_has_responsecode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BINExchangeAssetResponse::clear_responsecode() {
  responsecode_ = false;
  clear_has_responsecode();
}
inline bool BINExchangeAssetResponse::responsecode() const {
  return responsecode_;
}
inline void BINExchangeAssetResponse::set_responsecode(bool value) {
  set_has_responsecode();
  responsecode_ = value;
}

// optional string message = 2;
inline bool BINExchangeAssetResponse::has_message() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void BINExchangeAssetResponse::set_has_message() {
  _has_bits_[0] |= 0x00000002u;
}
inline void BINExchangeAssetResponse::clear_has_message() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void BINExchangeAssetResponse::clear_message() {
  if (message_ != &::google::protobuf::internal::kEmptyString) {
    message_->clear();
  }
  clear_has_message();
}
inline const ::std::string& BINExchangeAssetResponse::message() const {
  return *message_;
}
inline void BINExchangeAssetResponse::set_message(const ::std::string& value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void BINExchangeAssetResponse::set_message(const char* value) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(value);
}
inline void BINExchangeAssetResponse::set_message(const char* value, size_t size) {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  message_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BINExchangeAssetResponse::mutable_message() {
  set_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    message_ = new ::std::string;
  }
  return message_;
}
inline ::std::string* BINExchangeAssetResponse::release_message() {
  clear_has_message();
  if (message_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = message_;
    message_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void BINExchangeAssetResponse::set_allocated_message(::std::string* message) {
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


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_exchange_2eproto__INCLUDED
