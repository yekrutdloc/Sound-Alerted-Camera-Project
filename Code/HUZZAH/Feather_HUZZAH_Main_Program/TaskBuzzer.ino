/*
  ---------------------------------------------------------------
  Buzzer class declaration
  Provides user feedback using a buzzer

  Signals during startup:
  3 short beeps: Module started up and connected to Wi-Fi.
  a 3 second long beep: Wi-Fi not found, reset module(cut power and reinsert. RESET pin doesn't fix bug).

  Signal during normal operation:
  2 long beeps: Accident found!
  (TO-DO)3 long beeps: Wi-Fi connection lost, reset module(cut power and reinsert. RESET pin doesn't fix bug).

  Notes:

  ---------------------------------------------------------------
*/
class BuzzerTask : public Task {
  protected:
    void setup() {
      // initialize buzzer and LED as an output.
      pinMode(buzzerPin, OUTPUT);
      digitalWrite(buzzerPin, LOW); // Turn off Buzzer
      Serial.println(F("Started Buzzer Task"));
      delay(100); // Some time for serial buffer to empty
      taskBuzzerStarted = 1; // Set startup flag
    }

    void loop() {
      //Loud Noise Detected
      if (doLoudNoiseDetected) {
        Serial.println(F("[BUZZER] Running loud noise detected -chime"));
        setBuzzerBlueLED(HIGH);
        delay(50);
        setBuzzerBlueLED(LOW);
        doLoudNoiseDetected = 0;
      }

      //Startup chime
      if (doStartupChime) {
        Serial.println(F("[BUZZER] Running startup -chime"));
        setBuzzerBlueLED(HIGH);
        delay(50);
        setBuzzerBlueLED(LOW);
        delay(50);
        setBuzzerBlueLED(HIGH);
        delay(50);
        setBuzzerBlueLED(LOW);
        delay(50);
        setBuzzerBlueLED(HIGH);
        delay(50);
        setBuzzerBlueLED(LOW);
        delay(50);
        doStartupChime = 0;
      }

      //Wi-Fi-not-found chime
      if (doWifiNotFoundChime) {
        Serial.println(F("[BUZZER] Running Wi-Fi-not-found -chime"));
        setBuzzerBlueLED(HIGH);
        delay(3000);
        setBuzzerBlueLED(LOW);
        doWifiNotFoundChime = 0;
      }
      yield(); // Allow other essential backgrund tasks to run
      delayMicroseconds(buzzerExeutionFrequency); //How often to check if buzzer should run
    }
    void setBuzzerBlueLED(bool status) {
      digitalWrite(buzzerPin, status);
      digitalWrite(ledRedPin, status);
    }
  private:

} buzzer_task;

