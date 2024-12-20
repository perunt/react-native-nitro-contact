///
/// NitroContact-Swift-Cxx-Bridge.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

// Forward declarations of C++ defined types
// Forward declaration of `ContactData` to properly resolve imports.
namespace margelo::nitro::contacts { struct ContactData; }
// Forward declaration of `ContactFields` to properly resolve imports.
namespace margelo::nitro::contacts { enum class ContactFields; }
// Forward declaration of `StringHolder` to properly resolve imports.
namespace margelo::nitro::contacts { struct StringHolder; }

// Include C++ defined types
#if __has_include("ContactData.hpp")
 #include "ContactData.hpp"
#endif
#if __has_include("ContactFields.hpp")
 #include "ContactFields.hpp"
#endif
#if __has_include("StringHolder.hpp")
 #include "StringHolder.hpp"
#endif
#if __has_include(<NitroModules/PromiseHolder.hpp>)
 #include <NitroModules/PromiseHolder.hpp>
#endif
#if __has_include(<future>)
 #include <future>
#endif
#if __has_include(<optional>)
 #include <optional>
#endif
#if __has_include(<string>)
 #include <string>
#endif
#if __has_include(<vector>)
 #include <vector>
#endif

/**
 * Contains specialized versions of C++ templated types so they can be accessed from Swift,
 * as well as helper functions to interact with those C++ types from Swift.
 */
namespace margelo::nitro::contacts::bridge::swift {

  /**
   * Specialized version of `std::optional<std::string>`.
   */
  using std__optional_std__string_ = std::optional<std::string>;
  inline std::optional<std::string> create_std__optional_std__string_(const std::string& value) {
    return std::optional<std::string>(value);
  }
  
  /**
   * Specialized version of `std::vector<StringHolder>`.
   */
  using std__vector_StringHolder_ = std::vector<StringHolder>;
  inline std::vector<StringHolder> create_std__vector_StringHolder_(size_t size) {
    std::vector<StringHolder> vector;
    vector.reserve(size);
    return vector;
  }
  
  /**
   * Specialized version of `std::optional<std::vector<StringHolder>>`.
   */
  using std__optional_std__vector_StringHolder__ = std::optional<std::vector<StringHolder>>;
  inline std::optional<std::vector<StringHolder>> create_std__optional_std__vector_StringHolder__(const std::vector<StringHolder>& value) {
    return std::optional<std::vector<StringHolder>>(value);
  }
  
  /**
   * Specialized version of `std::vector<ContactData>`.
   */
  using std__vector_ContactData_ = std::vector<ContactData>;
  inline std::vector<ContactData> create_std__vector_ContactData_(size_t size) {
    std::vector<ContactData> vector;
    vector.reserve(size);
    return vector;
  }
  
  /**
   * Specialized version of `PromiseHolder<std::vector<ContactData>>`.
   */
  using PromiseHolder_std__vector_ContactData__ = PromiseHolder<std::vector<ContactData>>;
  inline PromiseHolder<std::vector<ContactData>> create_PromiseHolder_std__vector_ContactData__() {
    return PromiseHolder<std::vector<ContactData>>();
  }
  
  /**
   * Specialized version of `std::vector<ContactFields>`.
   */
  using std__vector_ContactFields_ = std::vector<ContactFields>;
  inline std::vector<ContactFields> create_std__vector_ContactFields_(size_t size) {
    std::vector<ContactFields> vector;
    vector.reserve(size);
    return vector;
  }

} // namespace margelo::nitro::contacts::bridge::swift
