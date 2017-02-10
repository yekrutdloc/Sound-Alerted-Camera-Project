const uint8_t sensorPinA = 12; // pin to Sound sensor A
const uint8_t sensorPinB = 13; // pin to Sound sensor B

unsigned long sensorASoundDetected = 0; // Has a value above 0 when a sound is detected
unsigned long sensorBSoundDetected = 0; // Has a value above 0 when a sound is detected

void sensorAInterrupt() {
  sensorASoundDetected = micros(); // Store current time(program runtime)
}
void sensorBInterrupt() {
  sensorBSoundDetected = micros(); // Store current time(program runtime)
}

void setup() {
  Serial.begin(115200);
  delay(100); // Some time for serial buffer to empty

  // put your setup code here, to run once:
  pinMode(sensorPinA, INPUT_PULLUP);
  pinMode(sensorPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(sensorPinA), sensorAInterrupt, RISING); //MAYBE CHANGE IN FUTURE TO RISING OR FALLING
  attachInterrupt(digitalPinToInterrupt(sensorPinB), sensorBInterrupt, RISING); //MAYBE CHANGE IN FUTURE TO RISING OR FALLING

  Serial.println("");
  Serial.println("");
  Serial.println(F("Started Sound Sensor Task"));
  delay(100); // Some time for serial buffer to empty

}

void loop() {
  // put your main code here, to run repeatedly:
  if (sensorASoundDetected > 0) {
    Serial.println(F("A"));
    sensorASoundDetected = 0;
  }

  if (sensorBSoundDetected > 0) {
    Serial.println(F("B"));
    sensorBSoundDetected = 0;
  }

  // Comment out the previous functions to calculate time difference
  if (sensorASoundDetected > 0 && sensorBSoundDetected > 0) {
    // Calculate time difference
    unsigned long timeDifference = 0;
    if (sensorASoundDetected > sensorBSoundDetected) {
      timeDifference = sensorASoundDetected - sensorBSoundDetected;
    } else {
      timeDifference = sensorBSoundDetected - sensorASoundDetected;
    }
    Serial.println(timeDifference);
  }
}



