package com.margelo.nitro.contacts;

class HybridContactTest : HybridContactTestSpec() {
    override val memorySize: Long
        get() = 0 // Placeholder value, adjust as needed


    override fun getAll(): Unit {
        println("from inside")
    }
}
