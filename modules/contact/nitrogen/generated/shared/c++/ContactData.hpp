///
/// ContactData.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

#if __has_include(<NitroModules/JSIConverter.hpp>)
#include <NitroModules/JSIConverter.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif
#if __has_include(<NitroModules/NitroDefines.hpp>)
#include <NitroModules/NitroDefines.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif



#include <optional>
#include <string>
#include <vector>

namespace margelo::nitro::margeloContact {

  /**
   * A struct which can be represented as a JavaScript object (ContactData).
   */
  struct ContactData {
  public:
    std::optional<std::string> firstName     SWIFT_PRIVATE;
    std::optional<std::string> lastName     SWIFT_PRIVATE;
    std::optional<std::string> middleName     SWIFT_PRIVATE;
    std::optional<std::vector<std::string>> phoneNumbers     SWIFT_PRIVATE;
    std::optional<std::vector<std::string>> emailAddresses     SWIFT_PRIVATE;
    std::optional<std::string> imageData     SWIFT_PRIVATE;
    std::optional<std::string> thumbnailImageData     SWIFT_PRIVATE;

  public:
    explicit ContactData(std::optional<std::string> firstName, std::optional<std::string> lastName, std::optional<std::string> middleName, std::optional<std::vector<std::string>> phoneNumbers, std::optional<std::vector<std::string>> emailAddresses, std::optional<std::string> imageData, std::optional<std::string> thumbnailImageData): firstName(firstName), lastName(lastName), middleName(middleName), phoneNumbers(phoneNumbers), emailAddresses(emailAddresses), imageData(imageData), thumbnailImageData(thumbnailImageData) {}
  };

} // namespace margelo::nitro::margeloContact

namespace margelo::nitro {

  using namespace margelo::nitro::margeloContact;

  // C++ ContactData <> JS ContactData (object)
  template <>
  struct JSIConverter<ContactData> {
    static inline ContactData fromJSI(jsi::Runtime& runtime, const jsi::Value& arg) {
      jsi::Object obj = arg.asObject(runtime);
      return ContactData(
        JSIConverter<std::optional<std::string>>::fromJSI(runtime, obj.getProperty(runtime, "firstName")),
        JSIConverter<std::optional<std::string>>::fromJSI(runtime, obj.getProperty(runtime, "lastName")),
        JSIConverter<std::optional<std::string>>::fromJSI(runtime, obj.getProperty(runtime, "middleName")),
        JSIConverter<std::optional<std::vector<std::string>>>::fromJSI(runtime, obj.getProperty(runtime, "phoneNumbers")),
        JSIConverter<std::optional<std::vector<std::string>>>::fromJSI(runtime, obj.getProperty(runtime, "emailAddresses")),
        JSIConverter<std::optional<std::string>>::fromJSI(runtime, obj.getProperty(runtime, "imageData")),
        JSIConverter<std::optional<std::string>>::fromJSI(runtime, obj.getProperty(runtime, "thumbnailImageData"))
      );
    }
    static inline jsi::Value toJSI(jsi::Runtime& runtime, const ContactData& arg) {
      jsi::Object obj(runtime);
      obj.setProperty(runtime, "firstName", JSIConverter<std::optional<std::string>>::toJSI(runtime, arg.firstName));
      obj.setProperty(runtime, "lastName", JSIConverter<std::optional<std::string>>::toJSI(runtime, arg.lastName));
      obj.setProperty(runtime, "middleName", JSIConverter<std::optional<std::string>>::toJSI(runtime, arg.middleName));
      obj.setProperty(runtime, "phoneNumbers", JSIConverter<std::optional<std::vector<std::string>>>::toJSI(runtime, arg.phoneNumbers));
      obj.setProperty(runtime, "emailAddresses", JSIConverter<std::optional<std::vector<std::string>>>::toJSI(runtime, arg.emailAddresses));
      obj.setProperty(runtime, "imageData", JSIConverter<std::optional<std::string>>::toJSI(runtime, arg.imageData));
      obj.setProperty(runtime, "thumbnailImageData", JSIConverter<std::optional<std::string>>::toJSI(runtime, arg.thumbnailImageData));
      return obj;
    }
    static inline bool canConvert(jsi::Runtime& runtime, const jsi::Value& value) {
      if (!value.isObject()) {
        return false;
      }
      jsi::Object obj = value.getObject(runtime);
      if (!JSIConverter<std::optional<std::string>>::canConvert(runtime, obj.getProperty(runtime, "firstName"))) return false;
      if (!JSIConverter<std::optional<std::string>>::canConvert(runtime, obj.getProperty(runtime, "lastName"))) return false;
      if (!JSIConverter<std::optional<std::string>>::canConvert(runtime, obj.getProperty(runtime, "middleName"))) return false;
      if (!JSIConverter<std::optional<std::vector<std::string>>>::canConvert(runtime, obj.getProperty(runtime, "phoneNumbers"))) return false;
      if (!JSIConverter<std::optional<std::vector<std::string>>>::canConvert(runtime, obj.getProperty(runtime, "emailAddresses"))) return false;
      if (!JSIConverter<std::optional<std::string>>::canConvert(runtime, obj.getProperty(runtime, "imageData"))) return false;
      if (!JSIConverter<std::optional<std::string>>::canConvert(runtime, obj.getProperty(runtime, "thumbnailImageData"))) return false;
      return true;
    }
  };

} // namespace margelo::nitro
