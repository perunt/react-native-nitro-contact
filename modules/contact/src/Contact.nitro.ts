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
export enum ContactFields {
  FIRST_NAME = 0,
  LAST_NAME = 1,
  MIDDLE_NAME = 2,
  PHONE_NUMBERS = 3,
  EMAIL_ADDRESSES = 4,
  IMAGE_DATA = 5,
  THUMBNAIL_IMAGE_DATA = 6,
  GIVEN_NAME_KEY = 7,
}
export interface Contact
  extends HybridObject<{ ios: 'swift'; android: 'kotlin' }> {
  getAll(keys: ContactFields[]): Promise<ContactData[]>
}
