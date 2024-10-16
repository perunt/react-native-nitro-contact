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
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext

class HybridContact : HybridContactSpec() {
    private var estimatedMemorySize: Long = 0
    override val memorySize: Long
        get() = estimatedMemorySize

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

    override fun getAll(keys: Array<ContactFields>): Promise<Array<ContactData>> {
        return Promise.async {
            if (!hasPhoneContactsPermission()) {
                requestContactPermission()
                return@async emptyArray<ContactData>()
            }

            val contacts = mutableListOf<ContactData>()
            var totalMemorySize: Long = 0

            context?.contentResolver?.let { resolver ->
                val projection = arrayOf(
                    ContactsContract.Data.MIMETYPE,
                    ContactsContract.Data.CONTACT_ID,
                    ContactsContract.Data.DISPLAY_NAME,
                    ContactsContract.Contacts.PHOTO_URI,
                    ContactsContract.Contacts.PHOTO_THUMBNAIL_URI,
                    ContactsContract.Data.DATA1,
                    ContactsContract.CommonDataKinds.StructuredName.GIVEN_NAME,
                    ContactsContract.CommonDataKinds.StructuredName.FAMILY_NAME,
                    ContactsContract.CommonDataKinds.StructuredName.MIDDLE_NAME
                )

                val selection = StringBuilder()
                val selectionArgs = mutableListOf<String>()

                selectionArgs.addAll(listOf(
                    ContactsContract.CommonDataKinds.StructuredName.CONTENT_ITEM_TYPE,
                    ContactsContract.CommonDataKinds.Phone.CONTENT_ITEM_TYPE,
                    ContactsContract.CommonDataKinds.Email.CONTENT_ITEM_TYPE
                ))

                selection.append("${ContactsContract.Data.MIMETYPE} IN (?, ?, ?)")

                val sortOrder = "${ContactsContract.Data.CONTACT_ID} ASC"

                val cursor = resolver.query(
                    ContactsContract.Data.CONTENT_URI,
                    projection,
                    selection.toString(),
                    selectionArgs.toTypedArray(),
                    sortOrder
                )

                cursor?.use {
                    val mimeTypeIndex = it.getColumnIndex(ContactsContract.Data.MIMETYPE)
                    val contactIdIndex = it.getColumnIndex(ContactsContract.Data.CONTACT_ID)
                    val photoUriIndex = it.getColumnIndex(ContactsContract.Contacts.PHOTO_URI)
                    val thumbnailUriIndex = it.getColumnIndex(ContactsContract.Contacts.PHOTO_THUMBNAIL_URI)
                    val data1Index = it.getColumnIndex(ContactsContract.Data.DATA1)
                    val givenNameIndex = it.getColumnIndex(ContactsContract.CommonDataKinds.StructuredName.GIVEN_NAME)
                    val familyNameIndex = it.getColumnIndex(ContactsContract.CommonDataKinds.StructuredName.FAMILY_NAME)
                    val middleNameIndex = it.getColumnIndex(ContactsContract.CommonDataKinds.StructuredName.MIDDLE_NAME)

                    var currentContact: ContactData? = null
                    var currentContactId: String? = null
                    val currentPhoneNumbers = mutableListOf<StringHolder>()
                    val currentEmailAddresses = mutableListOf<StringHolder>()

                    while (it.moveToNext()) {
                        val contactId = it.getString(contactIdIndex)
                        val mimeType = it.getString(mimeTypeIndex)

                        if (contactId != currentContactId) {
                            currentContact?.let { contact ->
                                contacts.add(contact.copy(
                                    phoneNumbers = currentPhoneNumbers.toTypedArray(),
                                    emailAddresses = currentEmailAddresses.toTypedArray()
                                ))
                                totalMemorySize += calculateContactMemory(contact, currentPhoneNumbers, currentEmailAddresses)
                            }
                            currentPhoneNumbers.clear()
                            currentEmailAddresses.clear()
                            currentContact = ContactData(
                                firstName = "",
                                lastName = "",
                                middleName = null,
                                phoneNumbers = emptyArray(),
                                emailAddresses = emptyArray(),
                                imageData = it.getString(photoUriIndex) ?: "",
                                thumbnailImageData = it.getString(thumbnailUriIndex) ?: ""
                            )
                            currentContactId = contactId
                        }

                        when (mimeType) {
                            ContactsContract.CommonDataKinds.StructuredName.CONTENT_ITEM_TYPE -> {
                                currentContact = currentContact?.copy(
                                    firstName = it.getString(givenNameIndex) ?: "",
                                    lastName = it.getString(familyNameIndex) ?: "",
                                    middleName = it.getString(middleNameIndex)
                                )
                            }
                            ContactsContract.CommonDataKinds.Phone.CONTENT_ITEM_TYPE -> {
                                it.getString(data1Index)?.let { phone ->
                                    currentPhoneNumbers.add(StringHolder(phone))
                                }
                            }
                            ContactsContract.CommonDataKinds.Email.CONTENT_ITEM_TYPE -> {
                                it.getString(data1Index)?.let { email ->
                                    currentEmailAddresses.add(StringHolder(email))
                                }
                            }
                        }
                    }
                    currentContact?.let { contact ->
                        contacts.add(contact.copy(
                            phoneNumbers = currentPhoneNumbers.toTypedArray(),
                            emailAddresses = currentEmailAddresses.toTypedArray()
                        ))
                        totalMemorySize += calculateContactMemory(contact, currentPhoneNumbers, currentEmailAddresses)
                    }
                }
            }

            estimatedMemorySize = totalMemorySize
            contacts.toTypedArray()
        }
    }

    private fun calculateContactMemory(contact: ContactData, phoneNumbers: List<StringHolder>, emailAddresses: List<StringHolder>): Long {
        var memory: Long = 0

        // Base size for ContactData object
        memory += 48 // Approximate size of object header and references

        // Memory for strings
        memory += (contact.firstName?.length ?: 0) * 2L
        memory += (contact.lastName?.length ?: 0) * 2L
        memory += (contact.middleName?.length ?: 0) * 2L
        memory += (contact.imageData?.length ?: 0) * 2L
        memory += (contact.thumbnailImageData?.length ?: 0) * 2L

        // Memory for phone numbers
        memory += phoneNumbers.sumOf { (it.value.length) * 2L + 24 } // 24 for StringHolder object

        // Memory for email addresses
        memory += emailAddresses.sumOf { (it.value.length) * 2L + 24 } // 24 for StringHolder object

        // Memory for arrays
        memory += 16 + phoneNumbers.size * 4L // Array object overhead + references
        memory += 16 + emailAddresses.size * 4L // Array object overhead + references

        return memory
    }

    fun getContactCount(): Int {
        if (context == null) {
            return 0
        }
        val cursor = context.contentResolver.query(
            ContactsContract.Contacts.CONTENT_URI,
            null,
            null,
            null,
            null
        )
        val count = cursor?.count ?: 0
        cursor?.close()
        return count
    }

    companion object {
        const val PERMISSION_REQUEST_CODE = 1
        const val REQUIRED_PERMISSION = Manifest.permission.READ_CONTACTS
    }
}