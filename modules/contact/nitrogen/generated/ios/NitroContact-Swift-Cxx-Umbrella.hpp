///
/// NitroContact-Swift-Cxx-Umbrella.hpp
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
// Forward declaration of `HybridContactSpec` to properly resolve imports.
namespace margelo::nitro::contacts { class HybridContactSpec; }
// Forward declaration of `StringHolder` to properly resolve imports.
namespace margelo::nitro::contacts { struct StringHolder; }

// Include C++ defined types
#include "ContactData.hpp"
#include "ContactFields.hpp"
#include "HybridContactSpec.hpp"
#include "StringHolder.hpp"
#include <future>
#include <memory>
#include <optional>
#include <string>
#include <vector>

// C++ helpers for Swift
#include "NitroContact-Swift-Cxx-Bridge.hpp"

// Common C++ types used in Swift
#include <NitroModules/ArrayBufferHolder.hpp>
#include <NitroModules/AnyMapHolder.hpp>
#include <NitroModules/HybridContext.hpp>
#include <NitroModules/PromiseHolder.hpp>

// Forward declarations of Swift defined types
// Forward declaration of `HybridContactSpecCxx` to properly resolve imports.
namespace NitroContact { class HybridContactSpecCxx; }

// Include Swift defined types
#if __has_include("NitroContact-Swift.h")
// This header is generated by Xcode/Swift on every app build.
// If it cannot be found, make sure the Swift module's name (= podspec name) is actually "NitroContact".
#include "NitroContact-Swift.h"
#else
#error NitroContact's autogenerated Swift header cannot be found! Make sure the Swift module's name (= podspec name) is actually "NitroContact", and try building the app first.
#endif
