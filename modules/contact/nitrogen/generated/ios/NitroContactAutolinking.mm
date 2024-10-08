///
/// NitroContactAutolinking.mm
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

#import <Foundation/Foundation.h>
#import <NitroModules/HybridObjectRegistry.hpp>
#import "NitroContact-Swift-Cxx-Umbrella.hpp"
#import <type_traits>

#include "HybridContactSpecSwift.hpp"

@interface NitroContactAutolinking : NSObject
@end

@implementation NitroContactAutolinking

+ (void) load {
  using namespace margelo::nitro;
  using namespace margelo::nitro::contacts;

  HybridObjectRegistry::registerHybridObjectConstructor(
    "Contact",
    []() -> std::shared_ptr<HybridObject> {
      auto swiftPart = NitroContact::NitroContactAutolinking::createContact();
      return std::make_shared<HybridContactSpecSwift>(swiftPart);
    }
  );
}

@end
