import type { HybridObject } from 'react-native-nitro-modules'

export interface ContactTest extends HybridObject<{ android: 'kotlin' }> {
  getAll(): void
}
