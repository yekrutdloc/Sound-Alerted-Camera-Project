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
      Serial.println(F("Started buzzer Task"));
      // initialize buzzer as an output.
      pinMode(buzzerPin, OUTPUT);
      taskBuzzerStarted = 1; // Set startup flag
    }

    void loop() {
      //Startup chime
      if (doStartupChime) {
        Serial.println(F("Doing startup chime"));
        digitalWrite(buzzerPin, HIGH);
        delay(50);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        digitalWrite(buzzerPin, HIGH);
        delay(50);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        digitalWrite(buzzerPin, HIGH);
        delay(50);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        doStartupChime = 0;
      }

      //Wi-Fi-not-found chime
      if (doWifiNotFoundChime) {
        Serial.println(F("Doing Wi-Fi-not-found chime"));
        digitalWrite(buzzerPin, HIGH);
        delay(3000);
        digitalWrite(buzzerPin, LOW);
        doWifiNotFoundChime = 0;
      }

      delay(500);
    }

  private:

} buzzer_task;

