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

#include "HybridContactTestSpecSwift.hpp"

@interface NitroContactAutolinking : NSObject
@end

@implementation NitroContactAutolinking

+ (void) load {
  using namespace margelo::nitro;
  using namespace margelo::nitro::contacts;

  HybridObjectRegistry::registerHybridObjectConstructor(
    "ContactTest",
    []() -> std::shared_ptr<HybridObject> {
      auto swiftPart = NitroContact::NitroContactAutolinking::createContactTest();
      return std::make_shared<HybridContactTestSpecSwift>(swiftPart);
    }
  );
}

@end