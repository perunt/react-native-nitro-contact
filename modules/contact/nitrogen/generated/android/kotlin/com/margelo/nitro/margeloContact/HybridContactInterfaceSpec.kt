///
/// HybridContactInterfaceSpec.kt
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

package com.margelo.nitro.margeloContact

import android.util.Log
import androidx.annotation.Keep
import com.facebook.jni.HybridData
import com.facebook.proguard.annotations.DoNotStrip
import com.margelo.nitro.core.*

/**
 * A Kotlin class representing the ContactInterface HybridObject.
 * Implement this abstract class to create Kotlin-based instances of ContactInterface.
 */
@DoNotStrip
@Keep
@Suppress("RedundantSuppression", "KotlinJniMissingFunction", "PropertyName", "RedundantUnitReturnType", "unused")
abstract class HybridContactInterfaceSpec: HybridObject() {
  protected val TAG = "HybridContactInterfaceSpec"

  @DoNotStrip
  val mHybridData: HybridData = initHybrid()

  init {
    // Pass this `HybridData` through to it's base class,
    // to represent inheritance to JHybridObject on C++ side
    super.updateNative(mHybridData)
  }

  // Properties
  

  // Methods
  @DoNotStrip
  @Keep
  abstract fun add(a: Double, b: Double): Double
  
  @DoNotStrip
  @Keep
  abstract fun getAll(keys: Array<String>): Promise<Array<Contact>>

  private external fun initHybrid(): HybridData

  companion object {
    private const val TAG = "HybridContactInterfaceSpec"
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
