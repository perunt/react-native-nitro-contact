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

import Contacts from '@s77rt/react-native-contacts';

function App(): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  const [data, setData] = useState([]);
  const [count, setCount] = useState(0);

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  function fetchContacts() {
    const startTime = performance.now();
    NitroContact.getAll(['FIRST_NAME', 'LAST_NAME', 'PHONE_NUMBERS', 'EMAIL_ADDRESSES'])
      .then(contacts => {
        const endTime = performance.now();
        const duration = endTime - startTime;

        console.log(
          `Fetched ${contacts.length} contacts. Time taken: ${duration.toFixed(
            2,
          )} milliseconds`,
        );
        setData(duration);
        setCount(contacts.length);
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
      .then(contacts => {
        const endTime = performance.now();
        const duration = endTime - startTime;

        console.log(
          `Fetched ${contacts.length} contacts. Time taken: ${duration.toFixed(
            2,
          )} milliseconds`,
        );
        setData(duration);
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
          <Button title="Press me" onPress={fetchContacts} />
          <Button
            title="Press me"
            onPress={fetchContactsCompare}
            style={{marginTop: 20}}
          />
          <Text
            style={{color: 'red', alignSelf: 'center', marginVertical: 80}}>
            {data}
          </Text>
          <Text
            style={{color: 'red', alignSelf: 'center', marginVertical: 80}}>
            {count}
          </Text>
          <Button
            title="Reset"
            onPress={() => {
              setData([]);
              contacts(0);
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
