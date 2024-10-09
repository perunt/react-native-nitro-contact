///
/// HybridContactSpecCxx.swift
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

import Foundation
import NitroModules

/**
 * A class implementation that bridges HybridContactSpec over to C++.
 * In C++, we cannot use Swift protocols - so we need to wrap it in a class to make it strongly defined.
 *
 * Also, some Swift types need to be bridged with special handling:
 * - Enums need to be wrapped in Structs, otherwise they cannot be accessed bi-directionally (Swift bug: https://github.com/swiftlang/swift/issues/75330)
 * - Other HybridObjects need to be wrapped/unwrapped from the Swift TCxx wrapper
 * - Throwing methods need to be wrapped with a Result<T, Error> type, as exceptions cannot be propagated to C++
 */
public class HybridContactSpecCxx {
  /**
   * The Swift <> C++ bridge's namespace (`margelo::nitro::contacts::bridge::swift`)
   * from `NitroContact-Swift-Cxx-Bridge.hpp`.
   * This contains specialized C++ templates, and C++ helper functions that can be accessed from Swift.
   */
  public typealias bridge = margelo.nitro.contacts.bridge.swift

  /**
   * Holds an instance of the `HybridContactSpec` Swift protocol.
   */
  private var implementation: HybridContactSpec

  /**
   * Get the actual `HybridContactSpec` instance this class wraps.
   */
  @inline(__always)
  public func getHybridContactSpec() -> HybridContactSpec {
    return implementation
  }

  /**
   * Create a new `HybridContactSpecCxx` that wraps the given `HybridContactSpec`.
   * All properties and methods bridge to C++ types.
   */
  public init(_ implementation: HybridContactSpec) {
    self.implementation = implementation
    /* no base class */
  }

  /**
   * Contains a (weak) reference to the C++ HybridObject to cache it.
   */
  public var hybridContext: margelo.nitro.HybridContext {
    @inline(__always)
    get {
      return self.implementation.hybridContext
    }
    @inline(__always)
    set {
      self.implementation.hybridContext = newValue
    }
  }

  /**
   * Get the memory size of the Swift class (plus size of any other allocations)
   * so the JS VM can properly track it and garbage-collect the JS object if needed.
   */
  @inline(__always)
  public var memorySize: Int {
    return self.implementation.memorySize
  }

  // Properties
  

  // Methods
  @inline(__always)
  public func getAll(keys: bridge.std__vector_std__string_) -> bridge.PromiseHolder_std__vector_ContactData__ {
    do {
      let result = try self.implementation.getAll(keys: keys.map({ val in String(val) }))
      return { () -> bridge.PromiseHolder_std__vector_ContactData__ in
        let promiseHolder = bridge.create_PromiseHolder_std__vector_ContactData__()
        result
          .then({ __result in promiseHolder.resolve({ () -> bridge.std__vector_ContactData_ in
        var vector = bridge.create_std__vector_ContactData_(__result.count)
        for item in __result {
          vector.push_back(item)
        }
        return vector
      }()) })
          .catch({ __error in promiseHolder.reject(std.string(String(describing: __error))) })
        return promiseHolder
      }()
    } catch {
      let message = "\(error.localizedDescription)"
      fatalError("Swift errors can currently not be propagated to C++! See https://github.com/swiftlang/swift/issues/75290 (Error: \(message))")
    }
  }
}