import React, {useState} from 'react';
import {
  Button,
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
} from 'react-native';

import {Colors, Header} from 'react-native/Libraries/NewAppScreen';

import {NitroContact} from './modules/contact/src';
// import {NitroContact} from '@modules/contact';

// import Contacts from '@s77rt/react-native-contacts';

function App(): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  const [data, setData] = useState([]);

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  function fetchContacts() {
    // const startTime = performance.now();
    // const contacts = NitroContact.getAll(['firstName', 'lastName', 'phoneNumbers', 'emailAddresses']);
    // const endTime = performance.now();
    // const duration = endTime - startTime;

    // console.log(`Fetched ${contacts.length} contacts`);
    // console.log(`Time taken: ${duration.toFixed(2)} milliseconds`);
    // setData(contacts);
    /////// TODO:
    const startTime = performance.now();
    NitroContact.getAll(['firstName', 'lastName', 'phoneNumbers', 'emailAddresses'])
      // Contacts.getAll(['firstName', 'lastName'])
      .then(contacts => {
        // console.log(contacts);
        const endTime = performance.now();
        const duration = endTime - startTime;

        console.log(`Fetched ${contacts.length} contacts`);
        console.log(`Time taken: ${duration.toFixed(2)} milliseconds`);
        // console.log('Pressed:', contacts.length);
      })
      .catch(error => {
        const endTime = performance.now();
        const duration = endTime - startTime;

        console.error(
          `Error occurred after ${duration.toFixed(2)} milliseconds:`,
          error,
        );
      });
  }
  function fetchContactsCompare() {
    const startTime = performance.now();
    Contacts.getAll(['firstName', 'lastName', 'phoneNumbers', 'emailAddresses'])
      // Contacts.getAll(['firstName', 'lastName'])
      .then(contacts => {
        // console.log(contacts);
        const endTime = performance.now();
        const duration = endTime - startTime;

        console.log(`Fetched ${contacts.length} contacts`);
        console.log(`Time taken: ${duration.toFixed(2)} milliseconds`);
        // console.log('Pressed:', contacts.length);
      })
      .catch(error => {
        const endTime = performance.now();
        const duration = endTime - startTime;

        console.error(
          `Error occurred after ${duration.toFixed(2)} milliseconds:`,
          error,
        );
      });
  }

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar
        barStyle={isDarkMode ? 'light-content' : 'dark-content'}
        backgroundColor={backgroundStyle.backgroundColor}
      />
      <ScrollView
        contentInsetAdjustmentBehavior="automatic"
        style={backgroundStyle}>
        <Header />
        <View
          style={{
            backgroundColor: isDarkMode ? Colors.black : Colors.white,
          }}>
          <Text style={styles.highlight}>App.tsx</Text>
          <Button title="Press me" onPress={fetchContacts} />
          <Button
            title="Press me"
            onPress={fetchContactsCompare}
            style={{marginTop: 20}}
          />
          <Text
            style={{color: 'white', alignSelf: 'center', marginVertical: 80}}>
            {data.length}
          </Text>
          <Button
            title="Reset"
            onPress={() => {
              setData([]);
            }}
          />
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
  highlight: {
    fontWeight: '700',
  },
});

export default App;
