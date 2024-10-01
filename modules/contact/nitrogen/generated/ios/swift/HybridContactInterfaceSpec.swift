///
/// HybridContactInterfaceSpec.swift
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

import Foundation
import NitroModules

/**
 * A Swift protocol representing the ContactInterface HybridObject.
 * Implement this protocol to create Swift-based instances of ContactInterface.
 *
 * When implementing this protocol, make sure to initialize `hybridContext` - example:
 * ```
 * public class HybridContactInterface : HybridContactInterfaceSpec {
 *   // Initialize HybridContext
 *   var hybridContext = margelo.nitro.HybridContext()
 *
 *   // Return size of the instance to inform JS GC about memory pressure
 *   var memorySize: Int {
 *     return getSizeOf(self)
 *   }
 *
 *   // ...
 * }
 * ```
 */
public protocol HybridContactInterfaceSpec: HybridObjectSpec {
  // Properties
  

  // Methods
  func add(a: Double, b: Double) throws -> Double
  func getAll(keys: [String]) throws -> Promise<[Contact]>
}

public extension HybridContactInterfaceSpec {
  /**
   * Create a new instance of HybridContactInterfaceSpecCxx for the given HybridContactInterfaceSpec.
   *
   * Instances of HybridContactInterfaceSpecCxx can be accessed from C++, and contain
   * additional required bridging code for C++ <> Swift interop.
   */
  func createCxxBridge() -> HybridContactInterfaceSpecCxx {
    return HybridContactInterfaceSpecCxx(self)
  }
}
