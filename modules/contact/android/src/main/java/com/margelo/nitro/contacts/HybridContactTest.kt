package com.margelo.nitro.contacts

import android.Manifest
import android.annotation.SuppressLint
import android.content.pm.PackageManager
import android.provider.ContactsContract
import android.util.Log
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.facebook.react.bridge.ReactApplicationContext
import com.margelo.nitro.NitroModules

class HybridContactTest : HybridContactTestSpec() {
    override val memorySize: Long
        get() = estimateMemorySize()

    private val context: ReactApplicationContext? = NitroModules.applicationContext

    fun requestContactPermission(): Boolean {
        val currentActivity = context?.currentActivity
        if (currentActivity != null) {
            ActivityCompat.requestPermissions(
                currentActivity,
                arrayOf(REQUIRED_PERMISSION),
                PERMISSION_REQUEST_CODE
            )
            return true
        }
        return false
    }

    private fun hasPhoneContactsPermission(): Boolean {
        if (context == null) {
            return false
        }

        val permissionStatus = ContextCompat.checkSelfPermission(
            context,
            Manifest.permission.READ_CONTACTS
        )

        return permissionStatus == PackageManager.PERMISSION_GRANTED
    }

    @SuppressLint("Range")
    override fun getAll(keys: Array<String>): Array<ContactData> {
        val startTime = System.currentTimeMillis()

        if (!hasPhoneContactsPermission()) {
            requestContactPermission()
            return emptyArray()
        }

        val contacts = mutableListOf<ContactData>()
        context?.contentResolver?.let { resolver ->
            val projection = arrayOf(
                ContactsContract.Data.MIMETYPE,
                ContactsContract.Data.CONTACT_ID,
                ContactsContract.Data.DISPLAY_NAME,
                ContactsContract.Contacts.PHOTO_URI,
                ContactsContract.Contacts.PHOTO_THUMBNAIL_URI,
                ContactsContract.Data.DATA1,
                ContactsContract.Data.DATA2,
                ContactsContract.Data.DATA3
            )

            val selection = StringBuilder()
            val selectionArgs = mutableListOf<String>()

            if (keys.isNotEmpty()) {
                selection.append("${ContactsContract.Data.MIMETYPE} IN (")
                keys.forEachIndexed { index, key ->
                    when (key) {
                        "firstName", "lastName", "middleName" -> {
                            if (index > 0) selection.append(",")
                            selection.append("?")
                            selectionArgs.add(ContactsContract.CommonDataKinds.StructuredName.CONTENT_ITEM_TYPE)
                        }
                        "phoneNumbers" -> {
                            if (index > 0) selection.append(",")
                            selection.append("?")
                            selectionArgs.add(ContactsContract.CommonDataKinds.Phone.CONTENT_ITEM_TYPE)
                        }
                        "emailAddresses" -> {
                            if (index > 0) selection.append(",")
                            selection.append("?")
                            selectionArgs.add(ContactsContract.CommonDataKinds.Email.CONTENT_ITEM_TYPE)
                        }
                    }
                }
                selection.append(")")
            }

            val sortOrder = "${ContactsContract.Data.CONTACT_ID} ASC"

            val cursor = resolver.query(
                ContactsContract.Data.CONTENT_URI,
                projection,
                if (selection.isNotEmpty()) selection.toString() else null,
                if (selectionArgs.isNotEmpty()) selectionArgs.toTypedArray() else null,
                sortOrder
            )

            cursor?.use {
                val mimeTypeIndex = it.getColumnIndex(ContactsContract.Data.MIMETYPE)
                val contactIdIndex = it.getColumnIndex(ContactsContract.Data.CONTACT_ID)
                val displayNameIndex = it.getColumnIndex(ContactsContract.Data.DISPLAY_NAME)
                val photoUriIndex = it.getColumnIndex(ContactsContract.Contacts.PHOTO_URI)
                val thumbnailUriIndex = it.getColumnIndex(ContactsContract.Contacts.PHOTO_THUMBNAIL_URI)
                val data1Index = it.getColumnIndex(ContactsContract.Data.DATA1)
                val data2Index = it.getColumnIndex(ContactsContract.Data.DATA2)
                val data3Index = it.getColumnIndex(ContactsContract.Data.DATA3)

                var currentContact: ContactData? = null
                var currentContactId: String? = null
                val currentPhoneNumbers = mutableListOf<String>()
                val currentEmailAddresses = mutableListOf<String>()

                while (it.moveToNext()) {
                    val contactId = it.getString(contactIdIndex)
                    if (contactId != currentContactId) {
                        currentContact?.let { contact -> contacts.add(contact) }
                        val displayName = it.getString(displayNameIndex) ?: ""
                        val nameParts = displayName.split(" ")
                        currentPhoneNumbers.clear()
                        currentEmailAddresses.clear()
                        currentContact = ContactData(
                            firstName = nameParts.firstOrNull() ?: "",
                            lastName = nameParts.lastOrNull()?.takeIf { it != nameParts.firstOrNull() } ?: "",
                            middleName = if (nameParts.size > 2) nameParts.subList(1, nameParts.size - 1).joinToString(" ") else null,
                            phoneNumbers = emptyArray(),  // Will be set later
                            emailAddresses = emptyArray(),  // Will be set later
                            imageData = it.getString(photoUriIndex) ?: "",
                            thumbnailImageData = it.getString(thumbnailUriIndex) ?: ""
                        )
                        currentContactId = contactId
                    }

                    when (it.getString(mimeTypeIndex)) {
                        ContactsContract.CommonDataKinds.Phone.CONTENT_ITEM_TYPE -> {
                            it.getString(data1Index)?.let { phone -> currentPhoneNumbers.add(phone) }
                        }
                        ContactsContract.CommonDataKinds.Email.CONTENT_ITEM_TYPE -> {
                            it.getString(data1Index)?.let { email -> currentEmailAddresses.add(email) }
                        }
                    }
                    currentContact = currentContact?.copy(
                        phoneNumbers = currentPhoneNumbers.toTypedArray(),
                        emailAddresses = currentEmailAddresses.toTypedArray()
                    )
                }
                currentContact?.let { contact -> contacts.add(contact) }
            }
        }

        val endTime = System.currentTimeMillis()
        val executionTime = endTime - startTime
        Log.d("HybridContactTest", "getAll execution time: $executionTime ms")

        return contacts.toTypedArray()
    }

    private fun estimateMemorySize(): Long {
        // This is a rough estimate. You might want to implement a more accurate calculation based on actual data.
        return 1024 * 1024 // 1MB as a placeholder
    }

    companion object {
        const val PERMISSION_REQUEST_CODE = 1
        const val REQUIRED_PERMISSION = Manifest.permission.READ_CONTACTS

        fun onRequestPermissionsResult(
            requestCode: Int,
            permissions: Array<out String>,
            grantResults: IntArray,
            onGranted: () -> Unit,
            onDenied: () -> Unit
        ) {
            if (requestCode == PERMISSION_REQUEST_CODE) {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    onGranted()
                } else {
                    onDenied()
                }
            }
        }
    }
}