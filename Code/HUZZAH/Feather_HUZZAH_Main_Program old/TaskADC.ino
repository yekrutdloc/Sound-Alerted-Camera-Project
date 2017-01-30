/*
  ---------------------------------------------------------------
  ADC class declaration
  Using the ADC
  ---------------------------------------------------------------
*/
class ADCTask : public Task {
  protected:
    void setup() {
      taskADCStarted = 1; //Set startup flag
      pinMode(ledRedPin, OUTPUT);
      memset(adcFilterBuffer, 0, sizeof(adcFilterBuffer)); // Set ADC filter buffer values to zeroes(so that there is no runtime error when running the loop)
    }

    void loop() {
      //Moving average filter
      for (uint8_t i = 0; i < adcFilterBufferSize - 1; i++) { // Remove the oldest value by moving all values one step closer to the start of the array
        adcFilterBuffer[i] = adcFilterBuffer[i + 1];
      }
      adcFilterBuffer[adcFilterBufferSize - 1] = analogRead(micAdcPin); // Save the latest ADC value at the back of the array.
      uint16_t adcFilterBufferSum = 0;
      for (uint8_t i = 0; i < adcFilterBufferSize; i++) { // Add up all the values
        adcFilterBufferSum += adcFilterBuffer[i];
      }
      micValue = adcFilterBufferSum / adcFilterBufferSize; // Get the average

      // RAW values without filter. Uncomment when you want to circumvent the filter
      //micValue = analogRead(A0); // read the input pin

      // Print out the serial value every few times, so that the overall program doesn't slow down due to serial throttling
      // Only used for debugging purposes, comment out for normal use!
//      if (serialCounter = adcSerialPrintFrequency) {
//        Serial.println(micValue);  //Print the value. Recommended to comment this out, as Serial can slow down the performance/task execution rate of HUZZAH
//        serialCounter = 0; // reset counter
//      }

      //Compare mic value with threshold
      if (micValue >= micVolumeThreshold) {
        Serial.print("THRESHHOLD REACHED: ");
        Serial.println(micValue);
        digitalWrite(ledRedPin, LOW);  //Turn ON Led(LOW=ON)
        doLoudNoiseDetected = 1; // Tell buzzer to the "loud noise detected" chime
        while (doLoudNoiseDetected) delay(100); // Wait for "loud noise detected" chime to finish
        //        if (taskHTTPGETStarted && !sendGETRequestPing) {
        //          sendGETRequestPing = 1; // Tell HTTP Task to send GET Request
        //          while (sendGETRequestPing) delay(500); // Wait in this loop until GET request is finished sending
        //        }
        memset(adcFilterBuffer, 0, sizeof(adcFilterBuffer)); // Clear buffer so it doesn't instantly thinks it detects another loud sound
        delay(500);
      }
      else {
        //Serial.println("THRESHHOLD NOT REACHED");
        digitalWrite(ledRedPin, HIGH);  //Turn OFF Led(HIGH=OFF)
      }

      serialCounter++;
      delay(adcExeutionFrequency); // How often to perform the task(excluding the execution time)
    }

  private:
    uint8_t serialCounter = 0; // counter to print adc value every few times
    uint16_t adcFilterBuffer[adcFilterBufferSize]; // Declare filter buffer
} adc_task;

