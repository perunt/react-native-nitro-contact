import { NitroModules } from 'react-native-nitro-modules'
import type { ContactTest } from './ContactTest.nitro'

export const NitroContact =
  NitroModules.createHybridObject<ContactTest>('ContactTest')
