///
/// HybridContactTestSpec.hpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#pragma once

#if __has_include(<NitroModules/HybridObject.hpp>)
#include <NitroModules/HybridObject.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif

// Forward declaration of `ContactData` to properly resolve imports.
namespace margelo::nitro::contacts { struct ContactData; }

#include <vector>
#include "ContactData.hpp"
#include <string>

namespace margelo::nitro::contacts {

  using namespace margelo::nitro;

  /**
   * An abstract base class for `ContactTest`
   * Inherit this class to create instances of `HybridContactTestSpec` in C++.
   * You must explicitly call `HybridObject`'s constructor yourself, because it is virtual.
   * @example
   * ```cpp
   * class HybridContactTest: public HybridContactTestSpec {
   * public:
   *   HybridContactTest(...): HybridObject(TAG) { ... }
   *   // ...
   * };
   * ```
   */
  class HybridContactTestSpec: public virtual HybridObject {
    public:
      // Constructor
      explicit HybridContactTestSpec(): HybridObject(TAG) { }

      // Destructor
      virtual ~HybridContactTestSpec() { }

    public:
      // Properties
      

    public:
      // Methods
      virtual std::vector<ContactData> getAll(const std::vector<std::string>& keys) = 0;

    protected:
      // Hybrid Setup
      void loadHybridMethods() override;

    protected:
      // Tag for logging
      static constexpr auto TAG = "ContactTest";
  };

} // namespace margelo::nitro::contacts
