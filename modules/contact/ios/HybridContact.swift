//
//  HybridContact.swift
//  NitroContact
//

import Foundation
import NitroModules
import Contacts

class HybridContact: HybridContactSpec {
    public var hybridContext = margelo.nitro.HybridContext()
    public var memorySize: Int {
      return getSizeOf(self)
    }
    
    public func getAll(_ keys: [String]) throws -> [ContactInterface] {
        let store = CNContactStore()
        let fetchRequest = CNContactFetchRequest(keysToFetch: keys as [CNKeyDescriptor])
        var contacts: [ContactInterface] = []
        
//        try store.enumerateContacts(with: fetchRequest) { (cnContact, _) in
//            var contact = ContactInterface()
//            
//            if keys.contains(CNContactGivenNameKey) {
//                contact.firstName = cnContact.givenName
//            }
//            if keys.contains(CNContactFamilyNameKey) {
//                contact.lastName = cnContact.familyName
//            }
//            if keys.contains(CNContactPhoneNumbersKey) {
//                contact.phoneNumbers = cnContact.phoneNumbers.map {
//                    PhoneNumber(label: $0.label ?? "", value: $0.value.stringValue)
//                }
//            }
//            if keys.contains(CNContactEmailAddressesKey) {
//                contact.emailAddresses = cnContact.emailAddresses.map {
//                    EmailAddress(label: $0.label ?? "", value: $0.value as String)
//                }
//            }
//            if keys.contains(CNContactThumbnailImageDataKey) {
//                contact.thumbnail = cnContact.thumbnailImageData?.base64EncodedString()
//            }
//            
//            contacts.append(contact)
//        }
        
        return contacts
    }
}
