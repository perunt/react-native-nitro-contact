
import type { HybridObject } from 'react-native-nitro-modules'

interface Contact {
  firstName?: string;
  lastName?: string;
  phoneNumbers?: PhoneNumber[];
  emailAddresses?: EmailAddress[];
  thumbnail?: string | null;
}

interface PhoneNumber {
  label: string | null;
  value: string;
}

interface EmailAddress {
  label: string | null;
  value: string;
}

export interface ContactInterface
  extends HybridObject<{ ios: 'swift'; android: 'kotlin' }> {
  add(a: number, b: number): number
  getAll(keys: string[]): Promise<Contact[]>;
}