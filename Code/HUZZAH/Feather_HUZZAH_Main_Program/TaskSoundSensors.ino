/*
  ---------------------------------------------------------------
  Here are the functions necessary for using the sound sensors.
  The sound sensors gives out HIGH and LOW to indicate when a sound
  is detected or not detected. We have two mics/sound sensors, so two pins are used to
  read the two sound sensor mics. The two pins are attached to interrupts,
  which means we don't have to poll the pins. Interrupts don't slow down
  the HUZZAH compared to when we have to poll the pins. Also when the
  sensors detected a sound we know about it with almost zero response time,
  making the angle detection much more accurate.

  Pins confirmed working flawlessy:
  12, 13, 14, 4, 5

  TO-DO:
  Change attachinterrupt modes(RISING or FALLING depending on comparator circuit)
  ---------------------------------------------------------------
*/

class SoundSensorsTask : public Task {
  protected:
    /*
      ---------------------------------------------------------------
      setup()
      ---------------------------------------------------------------
    */
    void setup() {
      while (!taskBuzzerStarted) delay(100); // Wait for buzzer task to start

      // Set sensors-pins as INPUT_PULLUP
      pinMode(sensorPinA, INPUT_PULLUP);
      pinMode(sensorPinB, INPUT_PULLUP);

      // Attach interrupts to pins
      attachInterrupt(digitalPinToInterrupt(sensorPinA), ::sensorAInterruptWrap, RISING); //MAYBE CHANGE IN FUTURE TO RISING OR FALLING
      attachInterrupt(digitalPinToInterrupt(sensorPinB), ::sensorBInterruptWrap, RISING); //MAYBE CHANGE IN FUTURE TO RISING OR FALLING

      Serial.println(F("Started Sound Sensor Task"));

      // Set startup flag
      delay(100); // Some time for serial buffer to empty
      taskSoundSensorsStarted = 1; // Set startup flag
    }
    /*
      ---------------------------------------------------------------
      loop()
      Check to see if one of the sensor-interrupts has gone off(if a sound is detected)
      ---------------------------------------------------------------
    */
    void loop()  {
      // If both Sensor A and B detected a sound then run calculations
      if ((sensorASoundDetected > 0) && (sensorBSoundDetected > 0)) {

        //Comment out the previous functions to calculate time difference
        if (sensorASoundDetected > 0 && sensorBSoundDetected > 0) {
          // Calculate time difference
          int32_t timeDifference = sensorASoundDetected - sensorBSoundDetected; // If difference + then B first, if - then A first
          sensorASoundDetected = 0;
          sensorBSoundDetected = 0;

          //Limit max degree
          double theta = 0;;
          if (timeDifference > 453) {
            degreeOfSound = 80;
          }  else if (timeDifference < -453) {
            degreeOfSound = -80;
          } else {
            theta = asin((double)((timeDifference * pow(10, -6)) * soundSpeed) / distance);
            degreeOfSound = (theta * 180) / M_PI;
          }

          Serial.print("SoundSpeed: ");
          Serial.print(soundSpeed);
          Serial.print(" Distance: ");
          Serial.print(distance);
          Serial.print(" Diff: ");
          Serial.print(timeDifference);
          Serial.print(" Theta: ");
          Serial.print(theta);
          Serial.print(" Angle: ");
          Serial.println(degreeOfSound);

          delay(500);
        }

        doLoudNoiseDetected = 1; // Tell buzzer to do the "loud noise detected" chime
        //while (doLoudNoiseDetected) delay(1); // Wait for "loud noise detected" chime to finish

        //TO-DO Send data to database
        //sendDatabaseInfo = 1;

        // Clear detection-variables
        sensorASoundDetected = 0;
        sensorBSoundDetected = 0;

        // Send angle to camera, wait for HTTP to finish
        sendDatabaseInfo = 1;
        while (sendDatabaseInfo) delay(1000);

        // TO-DO: Pause for several seconds(minutes?) untill checking for new car crash!
      }
      delayMicroseconds(soundSensorExeutionFrequency); // Loop delay

      //TESTING
      //      delay(5000);// wait 5 seconds
      //      sendDatabaseInfo = 1; // test database
      //      while (1) { // Stop program
      //        delay(1000);
      //      }
    }
  public:
    /*
      ---------------------------------------------------------------
      sensorAInterrupt()
      Runs whenever sensor A senses a noise.
      This function has to be as fast as possible, in order to not
      "block" the other sensors or other functions. It's recommended
      to only use this function to set a variable, then use a task to poll the variable.
      ---------------------------------------------------------------
    */
    void sensorAInterrupt() {
      sensorASoundDetected = micros(); // Store current time(program runtime)
    }
    /*
      ---------------------------------------------------------------
      sensorBInterrupt()
      Runs whenever sensor A senses a noise.
      This function has to be as fast as possible, in order to not
      "block" the other sensors or other functions. It's recommended
      to only use this function to set a variable, then use a task to poll the variable.
      ---------------------------------------------------------------
    */
    void sensorBInterrupt() {
      sensorBSoundDetected = micros(); // Store current time(program runtime)
    }
  private:
    const double soundSpeed = 330;
    const double distance = 0.15;
} soundsensors_task;


