package com.margelo.nitro.contacts

import android.Manifest
import android.content.pm.PackageManager
import android.provider.ContactsContract
import android.util.Log
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.facebook.react.bridge.ReactApplicationContext
import com.margelo.nitro.NitroModules
import com.margelo.nitro.core.Promise

class HybridContact : HybridContactSpec() {
    override val memorySize: Long
        get() = 0


    override fun getAll(): Boolean {
        Log.d("Module", "Hello nitro")
        return true
    }
}