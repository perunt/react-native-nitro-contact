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

function App(): React.JSX.Element {
  const isDarkMode = useColorScheme() === 'dark';
  const [data, setData] = useState([]);

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  function fetchContacts() {
    // const contacts = NitroContact.getAll([
    //   'firstName',
    //   'lastName',
    //   // 'phoneNumbers',
    //   'emailAddresses',
    //   // 'imageData',
    //   'thumbnailImageData',
    // ]);
    const contacts = NitroContact.getAll();
    // setData(c);
    console.log('Pressed:', contacts);
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
