import { NitroModules } from 'react-native-nitro-modules'
import type { Contact } from './Contact.nitro'

export const NitroContact = NitroModules.createHybridObject<Contact>('Contact')
