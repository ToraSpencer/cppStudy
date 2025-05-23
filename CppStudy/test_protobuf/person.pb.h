// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: person.proto
// Protobuf C++ Version: 5.29.3

#ifndef person_2eproto_2epb_2eh
#define person_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5029003
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_person_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_person_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_person_2eproto;
class Person;
struct PersonDefaultTypeInternal;
extern PersonDefaultTypeInternal _Person_default_instance_;
class PersonList;
struct PersonListDefaultTypeInternal;
extern PersonListDefaultTypeInternal _PersonList_default_instance_;
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google


// ===================================================================


// -------------------------------------------------------------------

class Person final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:Person) */ {
 public:
  inline Person() : Person(nullptr) {}
  ~Person() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(Person* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(Person));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR Person(
      ::google::protobuf::internal::ConstantInitialized);

  inline Person(const Person& from) : Person(nullptr, from) {}
  inline Person(Person&& from) noexcept
      : Person(nullptr, std::move(from)) {}
  inline Person& operator=(const Person& from) {
    CopyFrom(from);
    return *this;
  }
  inline Person& operator=(Person&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Person& default_instance() {
    return *internal_default_instance();
  }
  static inline const Person* internal_default_instance() {
    return reinterpret_cast<const Person*>(
        &_Person_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(Person& a, Person& b) { a.Swap(&b); }
  inline void Swap(Person* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Person* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Person* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<Person>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Person& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const Person& from) { Person::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(Person* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "Person"; }

 protected:
  explicit Person(::google::protobuf::Arena* arena);
  Person(::google::protobuf::Arena* arena, const Person& from);
  Person(::google::protobuf::Arena* arena, Person&& from) noexcept
      : Person(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kHobbiesFieldNumber = 3,
    kNameFieldNumber = 1,
    kAgeFieldNumber = 2,
  };
  // repeated string hobbies = 3;
  int hobbies_size() const;
  private:
  int _internal_hobbies_size() const;

  public:
  void clear_hobbies() ;
  const std::string& hobbies(int index) const;
  std::string* mutable_hobbies(int index);
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_hobbies(int index, Arg_&& value, Args_... args);
  std::string* add_hobbies();
  template <typename Arg_ = const std::string&, typename... Args_>
  void add_hobbies(Arg_&& value, Args_... args);
  const ::google::protobuf::RepeatedPtrField<std::string>& hobbies() const;
  ::google::protobuf::RepeatedPtrField<std::string>* mutable_hobbies();

  private:
  const ::google::protobuf::RepeatedPtrField<std::string>& _internal_hobbies() const;
  ::google::protobuf::RepeatedPtrField<std::string>* _internal_mutable_hobbies();

  public:
  // string name = 1;
  void clear_name() ;
  const std::string& name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_name(Arg_&& arg, Args_... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* value);

  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(
      const std::string& value);
  std::string* _internal_mutable_name();

  public:
  // int32 age = 2;
  void clear_age() ;
  ::int32_t age() const;
  void set_age(::int32_t value);

  private:
  ::int32_t _internal_age() const;
  void _internal_set_age(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:Person)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      26, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const Person& from_msg);
    ::google::protobuf::RepeatedPtrField<std::string> hobbies_;
    ::google::protobuf::internal::ArenaStringPtr name_;
    ::int32_t age_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_person_2eproto;
};
// -------------------------------------------------------------------

class PersonList final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:PersonList) */ {
 public:
  inline PersonList() : PersonList(nullptr) {}
  ~PersonList() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(PersonList* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(PersonList));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR PersonList(
      ::google::protobuf::internal::ConstantInitialized);

  inline PersonList(const PersonList& from) : PersonList(nullptr, from) {}
  inline PersonList(PersonList&& from) noexcept
      : PersonList(nullptr, std::move(from)) {}
  inline PersonList& operator=(const PersonList& from) {
    CopyFrom(from);
    return *this;
  }
  inline PersonList& operator=(PersonList&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PersonList& default_instance() {
    return *internal_default_instance();
  }
  static inline const PersonList* internal_default_instance() {
    return reinterpret_cast<const PersonList*>(
        &_PersonList_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(PersonList& a, PersonList& b) { a.Swap(&b); }
  inline void Swap(PersonList* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PersonList* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PersonList* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<PersonList>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const PersonList& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const PersonList& from) { PersonList::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(PersonList* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "PersonList"; }

 protected:
  explicit PersonList(::google::protobuf::Arena* arena);
  PersonList(::google::protobuf::Arena* arena, const PersonList& from);
  PersonList(::google::protobuf::Arena* arena, PersonList&& from) noexcept
      : PersonList(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kPeopleFieldNumber = 1,
  };
  // repeated .Person people = 1;
  int people_size() const;
  private:
  int _internal_people_size() const;

  public:
  void clear_people() ;
  ::Person* mutable_people(int index);
  ::google::protobuf::RepeatedPtrField<::Person>* mutable_people();

  private:
  const ::google::protobuf::RepeatedPtrField<::Person>& _internal_people() const;
  ::google::protobuf::RepeatedPtrField<::Person>* _internal_mutable_people();
  public:
  const ::Person& people(int index) const;
  ::Person* add_people();
  const ::google::protobuf::RepeatedPtrField<::Person>& people() const;
  // @@protoc_insertion_point(class_scope:PersonList)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 1,
      0, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const PersonList& from_msg);
    ::google::protobuf::RepeatedPtrField< ::Person > people_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_person_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Person

// string name = 1;
inline void Person::clear_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.ClearToEmpty();
}
inline const std::string& Person::name() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Person.name)
  return _internal_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Person::set_name(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:Person.name)
}
inline std::string* Person::mutable_name() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:Person.name)
  return _s;
}
inline const std::string& Person::_internal_name() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.name_.Get();
}
inline void Person::_internal_set_name(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.Set(value, GetArena());
}
inline std::string* Person::_internal_mutable_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.name_.Mutable( GetArena());
}
inline std::string* Person::release_name() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:Person.name)
  return _impl_.name_.Release();
}
inline void Person::set_allocated_name(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.name_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.name_.IsDefault()) {
    _impl_.name_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:Person.name)
}

// int32 age = 2;
inline void Person::clear_age() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.age_ = 0;
}
inline ::int32_t Person::age() const {
  // @@protoc_insertion_point(field_get:Person.age)
  return _internal_age();
}
inline void Person::set_age(::int32_t value) {
  _internal_set_age(value);
  // @@protoc_insertion_point(field_set:Person.age)
}
inline ::int32_t Person::_internal_age() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.age_;
}
inline void Person::_internal_set_age(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.age_ = value;
}

// repeated string hobbies = 3;
inline int Person::_internal_hobbies_size() const {
  return _internal_hobbies().size();
}
inline int Person::hobbies_size() const {
  return _internal_hobbies_size();
}
inline void Person::clear_hobbies() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.hobbies_.Clear();
}
inline std::string* Person::add_hobbies() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  std::string* _s = _internal_mutable_hobbies()->Add();
  // @@protoc_insertion_point(field_add_mutable:Person.hobbies)
  return _s;
}
inline const std::string& Person::hobbies(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Person.hobbies)
  return _internal_hobbies().Get(index);
}
inline std::string* Person::mutable_hobbies(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:Person.hobbies)
  return _internal_mutable_hobbies()->Mutable(index);
}
template <typename Arg_, typename... Args_>
inline void Person::set_hobbies(int index, Arg_&& value, Args_... args) {
  ::google::protobuf::internal::AssignToString(
      *_internal_mutable_hobbies()->Mutable(index),
      std::forward<Arg_>(value), args... );
  // @@protoc_insertion_point(field_set:Person.hobbies)
}
template <typename Arg_, typename... Args_>
inline void Person::add_hobbies(Arg_&& value, Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::google::protobuf::internal::AddToRepeatedPtrField(*_internal_mutable_hobbies(),
                               std::forward<Arg_>(value),
                               args... );
  // @@protoc_insertion_point(field_add:Person.hobbies)
}
inline const ::google::protobuf::RepeatedPtrField<std::string>&
Person::hobbies() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:Person.hobbies)
  return _internal_hobbies();
}
inline ::google::protobuf::RepeatedPtrField<std::string>*
Person::mutable_hobbies() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:Person.hobbies)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _internal_mutable_hobbies();
}
inline const ::google::protobuf::RepeatedPtrField<std::string>&
Person::_internal_hobbies() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.hobbies_;
}
inline ::google::protobuf::RepeatedPtrField<std::string>*
Person::_internal_mutable_hobbies() {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return &_impl_.hobbies_;
}

// -------------------------------------------------------------------

// PersonList

// repeated .Person people = 1;
inline int PersonList::_internal_people_size() const {
  return _internal_people().size();
}
inline int PersonList::people_size() const {
  return _internal_people_size();
}
inline void PersonList::clear_people() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.people_.Clear();
}
inline ::Person* PersonList::mutable_people(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:PersonList.people)
  return _internal_mutable_people()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::Person>* PersonList::mutable_people()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:PersonList.people)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _internal_mutable_people();
}
inline const ::Person& PersonList::people(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:PersonList.people)
  return _internal_people().Get(index);
}
inline ::Person* PersonList::add_people() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::Person* _add = _internal_mutable_people()->Add();
  // @@protoc_insertion_point(field_add:PersonList.people)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::Person>& PersonList::people() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:PersonList.people)
  return _internal_people();
}
inline const ::google::protobuf::RepeatedPtrField<::Person>&
PersonList::_internal_people() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.people_;
}
inline ::google::protobuf::RepeatedPtrField<::Person>*
PersonList::_internal_mutable_people() {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return &_impl_.people_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // person_2eproto_2epb_2eh
