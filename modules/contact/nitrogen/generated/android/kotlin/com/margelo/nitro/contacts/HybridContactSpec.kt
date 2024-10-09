///
/// HybridContactSpec.kt
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

package com.margelo.nitro.contacts

import android.util.Log
import androidx.annotation.Keep
import com.facebook.jni.HybridData
import com.facebook.proguard.annotations.DoNotStrip
import com.margelo.nitro.core.*

/**
 * A Kotlin class representing the Contact HybridObject.
 * Implement this abstract class to create Kotlin-based instances of Contact.
 */
@DoNotStrip
@Keep
@Suppress("RedundantSuppression", "KotlinJniMissingFunction", "PropertyName", "RedundantUnitReturnType", "unused")
abstract class HybridContactSpec: HybridObject() {
  @DoNotStrip
  private var mHybridData: HybridData = initHybrid()

  init {
    // Pass this `HybridData` through to it's base class,
    // to represent inheritance to JHybridObject on C++ side
    super.updateNative(mHybridData)
  }

  /**
   * Call from a child class to initialize HybridData with a child.
   */
  override fun updateNative(hybridData: HybridData) {
    mHybridData = hybridData
  }

  // Properties
  

  // Methods
  @DoNotStrip
  @Keep
  abstract fun getAll(keys: Array<String>): Promise<Array<ContactData>>

  private external fun initHybrid(): HybridData

  companion object {
    private const val TAG = "HybridContactSpec"
    init {
      try {
        Log.i(TAG, "Loading NitroContact C++ library...")
        System.loadLibrary("NitroContact")
        Log.i(TAG, "Successfully loaded NitroContact C++ library!")
      } catch (e: Error) {
        Log.e(TAG, "Failed to load NitroContact C++ library! Is it properly installed and linked? " +
                    "Is the name correct? (see `CMakeLists.txt`, at `add_library(...)`)", e)
        throw e
      }
    }
  }
}
