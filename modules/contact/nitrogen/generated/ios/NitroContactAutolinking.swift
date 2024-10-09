///
/// NitroContactAutolinking.swift
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

public final class NitroContactAutolinking {
  /**
   * Creates an instance of a Swift class that implements `HybridContactSpec`,
   * and wraps it in a Swift class that can directly interop with C++ (`HybridContactSpecCxx`)
   *
   * This is generated by Nitrogen and will initialize the class specified
   * in the `"autolinking"` property of `nitro.json` (in this case, `HybridContact`).
   */
  public static func createContact() -> HybridContactSpecCxx {
    let hybridObject = HybridContact()
    return hybridObject.createCxxBridge()
  }
}
