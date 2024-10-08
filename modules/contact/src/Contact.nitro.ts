import type { HybridObject } from 'react-native-nitro-modules'

interface ContactData {
  firstName?: string
  lastName?: string
  middleName?: string
  phoneNumbers?: string[]
  emailAddresses?: string[]
  imageData?: string
  thumbnailImageData?: string
}

export interface Contact
  extends HybridObject<{ ios: 'swift'; android: 'kotlin' }> {
  getAll(keys: string[]): Promise<ContactData[]>
}