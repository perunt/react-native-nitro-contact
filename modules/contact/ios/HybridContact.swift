//
//  HybridTestObjectSwift.swift
//  NitroImage
//

import Foundation
import NitroModules
import Contacts
import ContactsUI

import Contacts
import Foundation

class HybridContact: HybridContactSpec {
    public var hybridContext = margelo.nitro.HybridContext()
    
    public var memorySize: Int {
        return getSizeOf(self)
    }
    
    // func getAll() -> [[String: Any]] {
    func getAll() {
        let contactStore = CNContactStore()
        var contacts: [[String: Any]] = []
        
        let keys = [CNContactGivenNameKey, CNContactFamilyNameKey, CNContactPhoneNumbersKey, CNContactEmailAddressesKey]
        let request = CNContactFetchRequest(keysToFetch: keys as [CNKeyDescriptor])
        
        do {
            try contactStore.enumerateContacts(with: request) { (contact, stopPointer) in
                var contactDict: [String: Any] = [:]
                
                contactDict["firstName"] = contact.givenName
                contactDict["lastName"] = contact.familyName
                
                let phoneNumbers = contact.phoneNumbers.map { $0.value.stringValue }
                contactDict["phoneNumbers"] = phoneNumbers
                
                let emailAddresses = contact.emailAddresses.map { $0.value as String }
                contactDict["emailAddresses"] = emailAddresses
                
                contacts.append(contactDict)
            }
        } catch {
            print("Error fetching contacts: \(error)")
        }
        print("Contacts: \(contacts)")
        // return contacts
    }
}
