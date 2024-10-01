///
/// PhoneNumber.swift
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

import NitroModules

/**
 * Represents an instance of `PhoneNumber`, backed by a C++ struct.
 */
public typealias PhoneNumber = margelo.nitro.margeloContact.PhoneNumber

public extension PhoneNumber {
  private typealias bridge = margelo.nitro.margeloContact.bridge.swift

  /**
   * Create a new instance of `PhoneNumber`.
   */
  init(label: String?, value: String) {
    self.init({ () -> bridge.std__optional_std__string_ in
      if let actualValue = label {
        return bridge.create_std__optional_std__string_(std.string(actualValue))
      } else {
        return .init()
      }
    }(), std.string(value))
  }

  var label: String? {
    @inline(__always)
    get {
      return { () -> String? in
        if let actualValue = self.__label.value {
          return String(actualValue)
        } else {
          return nil
        }
      }()
    }
    @inline(__always)
    set {
      self.__label = { () -> bridge.std__optional_std__string_ in
        if let actualValue = newValue {
          return bridge.create_std__optional_std__string_(std.string(actualValue))
        } else {
          return .init()
        }
      }()
    }
  }
  
  var value: String {
    @inline(__always)
    get {
      return String(self.__value)
    }
    @inline(__always)
    set {
      self.__value = std.string(newValue)
    }
  }
}
