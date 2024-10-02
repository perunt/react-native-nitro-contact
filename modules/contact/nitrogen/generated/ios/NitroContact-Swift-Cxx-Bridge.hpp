///
/// NitroContact-Swift-Cxx-Bridge.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

// Forward declarations of C++ defined types
// Forward declaration of `ContactData` to properly resolve imports.
namespace margelo::nitro::margeloContact { struct ContactData; }

// Include C++ defined types
#if __has_include("ContactData.hpp")
 #include "ContactData.hpp"
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
namespace margelo::nitro::margeloContact::bridge::swift {

  /**
   * Specialized version of `std::optional<std::string>`.
   */
  using std__optional_std__string_ = std::optional<std::string>;
  inline std::optional<std::string> create_std__optional_std__string_(const std::string& value) {
    return std::optional<std::string>(value);
  }
  
  /**
   * Specialized version of `std::vector<std::string>`.
   */
  using std__vector_std__string_ = std::vector<std::string>;
  inline std::vector<std::string> create_std__vector_std__string_(size_t size) {
    std::vector<std::string> vector;
    vector.reserve(size);
    return vector;
  }
  
  /**
   * Specialized version of `std::optional<std::vector<std::string>>`.
   */
  using std__optional_std__vector_std__string__ = std::optional<std::vector<std::string>>;
  inline std::optional<std::vector<std::string>> create_std__optional_std__vector_std__string__(const std::vector<std::string>& value) {
    return std::optional<std::vector<std::string>>(value);
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

} // namespace margelo::nitro::margeloContact::bridge::swift
