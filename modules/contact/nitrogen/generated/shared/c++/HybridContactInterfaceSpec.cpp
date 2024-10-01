///
/// HybridContactInterfaceSpec.cpp
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#include "HybridContactInterfaceSpec.hpp"

namespace margelo::nitro::margeloContact {

  void HybridContactInterfaceSpec::loadHybridMethods() {
    // load base methods/properties
    HybridObject::loadHybridMethods();
    // load custom methods/properties
    registerHybrids(this, [](Prototype& prototype) {
      prototype.registerHybridMethod("add", &HybridContactInterfaceSpec::add);
      prototype.registerHybridMethod("getAll", &HybridContactInterfaceSpec::getAll);
    });
  }

} // namespace margelo::nitro::margeloContact
