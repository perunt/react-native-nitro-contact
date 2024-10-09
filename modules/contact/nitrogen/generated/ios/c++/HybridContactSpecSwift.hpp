///
/// HybridContactSpecSwift.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

#include "HybridContactSpec.hpp"

// Forward declaration of `HybridContactSpecCxx` to properly resolve imports.
namespace NitroContact { class HybridContactSpecCxx; }

// Forward declaration of `ContactData` to properly resolve imports.
namespace margelo::nitro::contacts { struct ContactData; }

#include <future>
#include <vector>
#include "ContactData.hpp"
#include <NitroModules/PromiseHolder.hpp>
#include <optional>
#include <string>

#if __has_include(<NitroModules/HybridContext.hpp>)
#include <NitroModules/HybridContext.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif

#include "NitroContact-Swift-Cxx-Umbrella.hpp"

namespace margelo::nitro::contacts {

  /**
   * The C++ part of HybridContactSpecCxx.swift.
   *
   * HybridContactSpecSwift (C++) accesses HybridContactSpecCxx (Swift), and might
   * contain some additional bridging code for C++ <> Swift interop.
   *
   * Since this obviously introduces an overhead, I hope at some point in
   * the future, HybridContactSpecCxx can directly inherit from the C++ class HybridContactSpec
   * to simplify the whole structure and memory management.
   */
  class HybridContactSpecSwift: public virtual HybridContactSpec {
  public:
    // Constructor from a Swift instance
    explicit HybridContactSpecSwift(const NitroContact::HybridContactSpecCxx& swiftPart):
      HybridObject(HybridContactSpec::TAG),
      _swiftPart(swiftPart) { }

  public:
    // Get the Swift part
    inline NitroContact::HybridContactSpecCxx getSwiftPart() noexcept { return _swiftPart; }

  public:
    // Get memory pressure
    inline size_t getExternalMemorySize() noexcept override {
      return _swiftPart.getMemorySize();
    }

  public:
    // Properties
    

  public:
    // Methods
    inline std::future<std::vector<ContactData>> getAll(const std::vector<std::string>& keys) override {
      auto __result = _swiftPart.getAll(keys);
      return __result.getFuture();
    }

  private:
    NitroContact::HybridContactSpecCxx _swiftPart;
  };

} // namespace margelo::nitro::contacts
