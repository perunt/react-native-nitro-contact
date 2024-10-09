import NitroModules
import Contacts
import Foundation

class HybridContact: HybridContactSpec {
    public var hybridContext = margelo.nitro.HybridContext()
    public var memorySize: Int {
        return getSizeOf(self)
    }
    
    private let contactStore = CNContactStore()
    private let imageDirectory: URL
    
    init() {
        imageDirectory = FileManager.default.temporaryDirectory.appendingPathComponent("ContactImages")
        try? FileManager.default.createDirectory(at: imageDirectory, withIntermediateDirectories: true)
    }
    
    func getAll(keys: [String]) throws -> Promise<[ContactData]> {
        return Promise.async {
            let startTime = CFAbsoluteTimeGetCurrent()
            let keysSet = Set(keys)
            
            let fieldToKeyDescriptor: [String: CNKeyDescriptor] = [
                "firstName": CNContactGivenNameKey as CNKeyDescriptor,
                "lastName": CNContactFamilyNameKey as CNKeyDescriptor,
                "phoneNumbers": CNContactPhoneNumbersKey as CNKeyDescriptor,
                "emailAddresses": CNContactEmailAddressesKey as CNKeyDescriptor,
                "middleName": CNContactMiddleNameKey as CNKeyDescriptor,
                "imageData": CNContactImageDataKey as CNKeyDescriptor,
                "thumbnailImageData": CNContactThumbnailImageDataKey as CNKeyDescriptor,
                "givenNameKey": CNContactGivenNameKey as CNKeyDescriptor
            ]
            
            let keysToFetch = keys.compactMap { fieldToKeyDescriptor[$0] }
            guard !keysToFetch.isEmpty else { return [] }
            
            let request = CNContactFetchRequest(keysToFetch: keysToFetch)
            var contacts: [ContactData] = []
            
            try self.contactStore.enumerateContacts(with: request) { (contact, _) in
                autoreleasepool {
                    let contactData = self.processContact(contact, keysSet: keysSet)
                    contacts.append(contactData)
                }
            }
            
            let end = CFAbsoluteTimeGetCurrent()
            let duration = (end - startTime) * 1000
            print("Duration: \(duration)ms")
            return contacts
        }
    }
    
    private func processContact(_ contact: CNContact, keysSet: Set<String>) -> ContactData {
        var contactData = ContactData()
        
        if keysSet.contains("firstName") {
            contactData.firstName = contact.givenName
        }
        if keysSet.contains("lastName") {
            contactData.lastName = contact.familyName
        }
        if keysSet.contains("middleName") {
            contactData.middleName = contact.middleName
        }
        if keysSet.contains("phoneNumbers") {
            contactData.phoneNumbers = contact.phoneNumbers.map { $0.value.stringValue }
        }
        if keysSet.contains("emailAddresses") {
            contactData.emailAddresses = contact.emailAddresses.map { String($0.value) }
        }
        if keysSet.contains("imageData") {
            contactData.imageData = getImagePath(for: contact, isThumbnail: false)
        }
        if keysSet.contains("thumbnailImageData") {
            contactData.thumbnailImageData = getImagePath(for: contact, isThumbnail: true)
        }
        
        return contactData
    }
    
    private func getImagePath(for contact: CNContact, isThumbnail: Bool) -> String? {
        let imageData = isThumbnail ? contact.thumbnailImageData : contact.imageData
        guard let data = imageData else { return nil }
        
        let fileName = "\(contact.identifier)_\(isThumbnail ? "thumb" : "full").jpg"
        let fileURL = imageDirectory.appendingPathComponent(fileName)
        
        if !FileManager.default.fileExists(atPath: fileURL.path) {
            try? data.write(to: fileURL)
        }
        
        return fileURL.path
    }
}
