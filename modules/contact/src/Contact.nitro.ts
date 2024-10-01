import type { HybridObject } from 'react-native-nitro-modules'
export interface Contact
  extends HybridObject<{ ios: 'swift'; android: 'kotlin' }> {
  getAll(): void
}
