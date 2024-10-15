///
/// JContactData.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

#include <fbjni/fbjni.h>
#include "ContactData.hpp"

#include "JStringHolder.hpp"
#include "StringHolder.hpp"
#include <optional>
#include <string>
#include <vector>

namespace margelo::nitro::contacts {

  using namespace facebook;

  /**
   * The C++ JNI bridge between the C++ struct "ContactData" and the the Kotlin data class "ContactData".
   */
  struct JContactData final: public jni::JavaClass<JContactData> {
  public:
    static auto constexpr kJavaDescriptor = "Lcom/margelo/nitro/contacts/ContactData;";

  public:
    /**
     * Convert this Java/Kotlin-based struct to the C++ struct ContactData by copying all values to C++.
     */
    [[maybe_unused]]
    ContactData toCpp() const {
      static const auto clazz = javaClassStatic();
      static const auto fieldFirstName = clazz->getField<jni::JString>("firstName");
      jni::local_ref<jni::JString> firstName = this->getFieldValue(fieldFirstName);
      static const auto fieldLastName = clazz->getField<jni::JString>("lastName");
      jni::local_ref<jni::JString> lastName = this->getFieldValue(fieldLastName);
      static const auto fieldMiddleName = clazz->getField<jni::JString>("middleName");
      jni::local_ref<jni::JString> middleName = this->getFieldValue(fieldMiddleName);
      static const auto fieldPhoneNumbers = clazz->getField<jni::JArrayClass<JStringHolder>>("phoneNumbers");
      jni::local_ref<jni::JArrayClass<JStringHolder>> phoneNumbers = this->getFieldValue(fieldPhoneNumbers);
      static const auto fieldEmailAddresses = clazz->getField<jni::JArrayClass<JStringHolder>>("emailAddresses");
      jni::local_ref<jni::JArrayClass<JStringHolder>> emailAddresses = this->getFieldValue(fieldEmailAddresses);
      static const auto fieldImageData = clazz->getField<jni::JString>("imageData");
      jni::local_ref<jni::JString> imageData = this->getFieldValue(fieldImageData);
      static const auto fieldThumbnailImageData = clazz->getField<jni::JString>("thumbnailImageData");
      jni::local_ref<jni::JString> thumbnailImageData = this->getFieldValue(fieldThumbnailImageData);
      return ContactData(
        firstName != nullptr ? std::make_optional(firstName->toStdString()) : std::nullopt,
        lastName != nullptr ? std::make_optional(lastName->toStdString()) : std::nullopt,
        middleName != nullptr ? std::make_optional(middleName->toStdString()) : std::nullopt,
        phoneNumbers != nullptr ? std::make_optional([&]() {
          size_t size = phoneNumbers->size();
          std::vector<StringHolder> vector;
          vector.reserve(size);
          for (size_t i = 0; i < size; i++) {
            auto element = phoneNumbers->getElement(i);
            vector.push_back(element->toCpp());
          }
          return vector;
        }()) : std::nullopt,
        emailAddresses != nullptr ? std::make_optional([&]() {
          size_t size = emailAddresses->size();
          std::vector<StringHolder> vector;
          vector.reserve(size);
          for (size_t i = 0; i < size; i++) {
            auto element = emailAddresses->getElement(i);
            vector.push_back(element->toCpp());
          }
          return vector;
        }()) : std::nullopt,
        imageData != nullptr ? std::make_optional(imageData->toStdString()) : std::nullopt,
        thumbnailImageData != nullptr ? std::make_optional(thumbnailImageData->toStdString()) : std::nullopt
      );
    }

  public:
    /**
     * Create a Java/Kotlin-based struct by copying all values from the given C++ struct to Java.
     */
    [[maybe_unused]]
    static jni::local_ref<JContactData::javaobject> fromCpp(const ContactData& value) {
      return newInstance(
        value.firstName.has_value() ? jni::make_jstring(value.firstName.value()) : nullptr,
        value.lastName.has_value() ? jni::make_jstring(value.lastName.value()) : nullptr,
        value.middleName.has_value() ? jni::make_jstring(value.middleName.value()) : nullptr,
        value.phoneNumbers.has_value() ? [&]() {
          size_t size = value.phoneNumbers.value().size();
          jni::local_ref<jni::JArrayClass<JStringHolder>> array = jni::JArrayClass<JStringHolder>::newArray(size);
          for (size_t i = 0; i < size; i++) {
            const auto& element = value.phoneNumbers.value()[i];
            array->setElement(i, *JStringHolder::fromCpp(element));
          }
          return array;
        }() : nullptr,
        value.emailAddresses.has_value() ? [&]() {
          size_t size = value.emailAddresses.value().size();
          jni::local_ref<jni::JArrayClass<JStringHolder>> array = jni::JArrayClass<JStringHolder>::newArray(size);
          for (size_t i = 0; i < size; i++) {
            const auto& element = value.emailAddresses.value()[i];
            array->setElement(i, *JStringHolder::fromCpp(element));
          }
          return array;
        }() : nullptr,
        value.imageData.has_value() ? jni::make_jstring(value.imageData.value()) : nullptr,
        value.thumbnailImageData.has_value() ? jni::make_jstring(value.thumbnailImageData.value()) : nullptr
      );
    }
  };

} // namespace margelo::nitro::contacts