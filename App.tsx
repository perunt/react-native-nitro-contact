import React, {useMemo, useState} from 'react';
import {
  TouchableOpacity,
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  useColorScheme,
  View,
} from 'react-native';
const ITERATION = 10;
import {Colors} from 'react-native/Libraries/NewAppScreen';
import {NitroContact} from './modules/contact/src';
import Contacts from '@s77rt/react-native-contacts';

const ComparisonCard = ({title, timers, iteration}) => (
  <View style={styles.card}>
    <Text style={styles.cardTitle}>{title}</Text>
    <View style={styles.timerContainer}>
      <View style={styles.timerItem}>
        <Text style={styles.timerLabel}>Average</Text>
        <Text style={styles.timerValue}>{timers.averageTime}ms</Text>
      </View>
      <View style={styles.timerItem}>
        <Text style={styles.timerLabel}>Fastest</Text>
        <Text style={styles.timerValue}>{timers.lowestTime}ms</Text>
      </View>
      <View style={styles.timerItem}>
        <Text style={styles.timerLabel}>Slowest</Text>
        <Text style={styles.timerValue}>{timers.highestTime}ms</Text>
      </View>
    </View>
  </View>
);

const Button = ({onPress, title, variant = 'primary', disabled = false}) => (
  <TouchableOpacity
    onPress={onPress}
    disabled={disabled}
    style={[
      styles.button,
      variant === 'secondary' ? styles.buttonSecondary : styles.buttonPrimary,
      variant === 'warm' && styles.buttonWarm,
      disabled && styles.buttonDisabled,
    ]}>
    <Text
      style={[
        styles.buttonText,
        variant === 'secondary'
          ? styles.buttonTextSecondary
          : styles.buttonTextPrimary,
        variant === 'warm' && styles.buttonTextWarm,
        disabled && styles.buttonTextDisabled,
      ]}>
      {title}
    </Text>
  </TouchableOpacity>
);

function calculateSpeedDifference(fasterTime, slowerTime) {
  const percentageFaster = ((slowerTime - fasterTime) / slowerTime) * 100;
  return percentageFaster;
}

function App() {
  const isDarkMode = useColorScheme() === 'dark';
  const [count, setCount] = useState(0);
  const [iteration, setIteration] = useState(0);
  const [isWarming, setIsWarming] = useState(false);
  const [nitroTimers, setNitroTimers] = useState({
    averageTime: '0',
    lowestTime: '0',
    highestTime: '0',
  });
  const [turboTimers, setTurboTimers] = useState({
    averageTime: '0',
    lowestTime: '0',
    highestTime: '0',
  });

  const reset = () => {
    setIteration(0);
    setNitroTimers({
      averageTime: '0',
      lowestTime: '0',
      highestTime: '0',
    });
    setTurboTimers({
      averageTime: '0',
      lowestTime: '0',
      highestTime: '0',
    });
  };

  function warmContacts() {
    setIsWarming(true);
    NitroContact.getAll([
      'FIRST_NAME',
      'LAST_NAME',
      'PHONE_NUMBERS',
      'EMAIL_ADDRESSES',
    ]).then(contacts => {
      setCount(contacts.length);
      setIsWarming(false);
    });
  }

  function benchmarkContactFetch(iterations = 10, interval = 5000, label) {
    let executionTimes = [];
    let executionCount = 0;

    function runBenchmark() {
      setIteration(executionCount);
      if (executionCount >= iterations) {
        const averageTime =
          executionTimes.reduce((sum, time) => sum + time, 0) / iterations;
        const lowestTime = Math.min(...executionTimes);
        const highestTime = Math.max(...executionTimes);

        const saveData = label === 'Nitro' ? setNitroTimers : setTurboTimers;
        saveData({
          averageTime: averageTime.toFixed(2),
          lowestTime: lowestTime.toFixed(2),
          highestTime: highestTime.toFixed(2),
        });
        return;
      }

      const startTime = performance.now();
      const Module = label === 'Nitro' ? NitroContact : Contacts;
      const moduleParams =
        label === 'Nitro'
          ? ['FIRST_NAME', 'LAST_NAME', 'PHONE_NUMBERS', 'EMAIL_ADDRESSES', 'IMAGE_DATA']
          : [
              'firstName',
              'lastName',
              'phoneNumbers',
              'emailAddresses',
              'thumbnail',
            ];

      Module.getAll(moduleParams).then(contacts => {
        const endTime = performance.now();
        const duration = endTime - startTime;
        executionTimes.push(duration);
        executionCount++;
        setTimeout(runBenchmark, interval);
        setCount(contacts.length);
      });
    }

    runBenchmark();
  }

  const result = useMemo(() => {
    return (
      calculateSpeedDifference(
        +nitroTimers.averageTime,
        +turboTimers.averageTime,
      ).toFixed(2) || 0
    );
  }, [nitroTimers.averageTime, turboTimers.averageTime]);

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  return (
    <SafeAreaView style={[styles.container, backgroundStyle]}>
      <StatusBar
        barStyle={isDarkMode ? 'light-content' : 'dark-content'}
        backgroundColor={backgroundStyle.backgroundColor}
      />
      <ScrollView contentInsetAdjustmentBehavior="automatic">
        <View style={styles.header}>
          <Text style={styles.title}>Contact Module Speed Test</Text>
          <Text style={styles.subtitle}>
            Testing performance of Nitro vs Turbo modules
          </Text>
        </View>

        <View style={styles.content}>
          <View style={styles.warmupSection}>
            <Button
              title={isWarming ? 'Warming Up...' : 'Warm Up Modules'}
              onPress={warmContacts}
              variant="warm"
              disabled={isWarming}
            />
            {count > 0 && (
              <Text style={styles.warmupText}>
                Module warmed up with {count} contacts
              </Text>
            )}
          </View>

          <View style={styles.buttonContainer}>
            <TouchableOpacity
              style={[styles.buttonTest, isWarming && styles.buttonDisabled]}
              onPress={() => benchmarkContactFetch(ITERATION, 5000, 'Nitro')}
              disabled={isWarming}>
              <Text
                style={[styles.buttonText, styles.buttonTextPrimary]}
                numberOfLines={1}>
                Run Nitro Test
              </Text>
            </TouchableOpacity>
            <TouchableOpacity
              style={[styles.buttonTest, isWarming && styles.buttonDisabled]}
              onPress={() => benchmarkContactFetch(ITERATION, 5000, 'Turbo')}
              disabled={isWarming}>
              <Text
                style={[styles.buttonText, styles.buttonTextPrimary]}
                numberOfLines={1}>
                Run Turbo Test
              </Text>
            </TouchableOpacity>
          </View>

          <View style={styles.progressContainer}>
            <Text style={styles.progressText}>Iteration: {iteration}/{ITERATION}</Text>
            <Text style={styles.contactCount}>Contacts processed: {count}</Text>
          </View>

          <ComparisonCard
            title="Nitro Module Performance"
            timers={nitroTimers}
            iteration={iteration}
          />

          <ComparisonCard
            title="Turbo Module Performance"
            timers={turboTimers}
            iteration={iteration}
          />

          {result > 0 && (
            <View style={styles.resultCard}>
              <Text style={styles.resultText}>
                Nitro Module is {result}% faster
              </Text>
            </View>
          )}

          <Button
            title="Reset Tests"
            onPress={reset}
            variant="secondary"
            disabled={isWarming}
          />
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  header: {
    padding: 24,
    backgroundColor: '#f8f9fa',
    borderBottomWidth: 1,
    borderBottomColor: '#e9ecef',
  },
  title: {
    fontSize: 24,
    fontWeight: 'bold',
    color: '#212529',
  },
  subtitle: {
    fontSize: 16,
    color: '#6c757d',
    marginTop: 4,
  },
  content: {
    padding: 16,
  },
  warmupSection: {
    marginBottom: 24,
  },
  warmupText: {
    textAlign: 'center',
    color: '#2E7D32',
    marginTop: 8,
    fontSize: 14,
  },
  buttonContainer: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    gap: 8,
    marginBottom: 24,
    // backgroundColor: 'red',
    marginHorizontal: 8,
  },
  button: {
    flex: 1,
    marginHorizontal: 8,
    paddingVertical: 12,
    paddingHorizontal: 24,
    borderRadius: 8,
    alignItems: 'center',
  },
  buttonPrimary: {
    backgroundColor: '#007AFF',
  },
  buttonSecondary: {
    backgroundColor: '#ffffff',
    borderWidth: 1,
    borderColor: '#6c757d',
  },
  buttonWarm: {
    backgroundColor: '#FFA726',
  },
  buttonDisabled: {
    opacity: 0.5,
  },
  buttonTest: {
    flex: 1,
    paddingVertical: 12,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#007AFF',
    borderRadius: 8,
  },
  buttonText: {
    fontSize: 16,
    fontWeight: '600',

    flex: 1,
  },
  buttonTextPrimary: {
    color: '#ffffff',
  },
  buttonTextSecondary: {
    color: '#6c757d',
  },
  buttonTextWarm: {
    color: '#ffffff',
  },
  buttonTextDisabled: {
    color: '#999999',
  },
  progressContainer: {
    alignItems: 'center',
    marginBottom: 24,
  },
  progressText: {
    fontSize: 18,
    fontWeight: '600',
    color: '#212529',
  },
  contactCount: {
    fontSize: 14,
    color: '#6c757d',
    marginTop: 4,
  },
  card: {
    backgroundColor: '#ffffff',
    borderRadius: 12,
    padding: 16,
    marginBottom: 16,
    shadowColor: '#000',
    shadowOffset: {
      width: 0,
      height: 2,
    },
    shadowOpacity: 0.1,
    shadowRadius: 4,
    elevation: 3,
  },
  cardTitle: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#212529',
    marginBottom: 16,
  },
  timerContainer: {
    flexDirection: 'row',
    justifyContent: 'space-between',
  },
  timerItem: {
    flex: 1,
    alignItems: 'center',
  },
  timerLabel: {
    fontSize: 14,
    color: '#6c757d',
    marginBottom: 4,
  },
  timerValue: {
    fontSize: 20,
    fontWeight: '600',
    color: '#212529',
  },
  resultCard: {
    backgroundColor: '#e3f2fd',
    borderRadius: 12,
    padding: 16,
    marginBottom: 16,
    alignItems: 'center',
  },
  resultText: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#1976d2',
  },
});

export default App;
