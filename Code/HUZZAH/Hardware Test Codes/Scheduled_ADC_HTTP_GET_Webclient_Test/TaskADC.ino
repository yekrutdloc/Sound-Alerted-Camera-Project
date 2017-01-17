/*
  ---------------------------------------------------------------
  ADC class declaration
  Using the ADC
  ---------------------------------------------------------------
*/
class ADCTask : public Task {
  protected:
    void setup() {
    }

    void loop() {
      analogVal = analogRead(A0); // read the input pin
      Serial.println(analogVal); // Print value
      delay(100);

      // Every 5 seconds(100ms x 50 = 5000ms) send GET request
      if (count == 50) {
        Serial.println("Telling GET Task to send");
        // Tell HTTP Task to send GET Request
        sendGETRequestPing = 1;
        // Wait in this loop until GET request is finished sending
        while (sendGETRequestPing) {
          delay(500);
        }
        Serial.println("GET-task told ADC-task to continue");
        count = 0; // reset counter
      }
      count++;
    }

  private:
    int analogVal;
    int count = 0;
} adc_task;

