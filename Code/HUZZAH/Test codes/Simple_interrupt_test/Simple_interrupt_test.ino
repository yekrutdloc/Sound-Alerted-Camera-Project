/*

   Simple interrupt test and time difference test for microphones

   One interrupt takes 0-2 us to run(sensorASoundDetected = micros()). This difference is small enough to
   ignore in the time difference calculation

*/

#include <math.h>

const double soundSpeed = 330;
const double distance = 0.15;

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


  //  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("");
  Serial.println("");
  Serial.println(F("Started Sound Sensor Task"));
  delay(100); // Some time for serial buffer to empty

}

void loop() {
  //    digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
  //    delay(100);                       // wait for a second
  //    digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
  //    delay(1000);

  //  if (sensorASoundDetected > 0) {
  //    Serial.print(F("A: "));
  //    Serial.println(sensorASoundDetected);
  //    sensorASoundDetected = 0;
  //  }
  //
  //  if (sensorBSoundDetected > 0) {
  //    Serial.print(F("B: "));
  //    Serial.println(sensorBSoundDetected);
  //    sensorBSoundDetected = 0;
  //  }

  //Comment out the previous functions to calculate time difference
  if (sensorASoundDetected > 0 && sensorBSoundDetected > 0) {
    // Calculate time difference
    int32_t timeDifference = sensorASoundDetected - sensorBSoundDetected; // If difference + then B first, if - then A first
    sensorASoundDetected = 0;
    sensorBSoundDetected = 0;

    double degree = 0;
    double theta = 0;
    //Limit
    if (timeDifference > 453) {
      degree = 80;
    }  else if (timeDifference < -453) {
      degree = -80;
    } else {
      theta = asin((double)((timeDifference * pow(10, -6)) * soundSpeed) / distance);
      degree = (theta * 180) / M_PI;
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
    Serial.println(degree);

    delay(1500);
  }
}



