// Choose to use filter or not
// Moving average filter with changeable buffer size
// LED toggle is inverted, in order to toggle LED on it has to be set LOW, or to turn it off set to HIGH
// HUZZAH has two LEDs, red LED on pin 0, and blue LED on pin 2

/*
   How to plot values to matlab
   Run this project on the HUZZAH with serial monitor open
   in matlab run x = 0:1:999 (change the 999 to the amount of polls you make here)
   then paste y = [, and copy paste the results on mic A the Serial window, and close with ]
   then run plot(x,y)
   then run hold on
   then do the same but with mic B, y2 = [].....
   then run plot(x,y2)
*/


int DA = A0; // Pin for Analog Output - AO
const uint8_t ledRedPin = 0; // pin to the red LED
const uint8_t ledBluePin = 2; // pin to the blue LED
int led = ledBluePin;
int threshold = 560; //Change this
int adcValue = 0;

const uint8_t adcFilterBufferSize = 5; // Change buffer size here
uint16_t adcFilterBuffer[adcFilterBufferSize];

const uint16_t amountOfPolls = 2000; // The amount of times to poll
uint16_t valuesA[amountOfPolls];
uint16_t valuesB[amountOfPolls];

//multiplex channel pins
uint8_t channelA = 2;
uint8_t channelB = 16;
uint8_t channelC = 15;

// Give an array of
void getMicVal(uint16_t &pmicAData, uint16_t &pmicBData) {
  //Get Mic B data from channel 0(pin 13 on mx)
  digitalWrite(channelA, LOW);
  digitalWrite(channelB, LOW);
  digitalWrite(channelC, LOW);
  delayMicroseconds(1);   // Delay to give mx some time to switch channel
  pmicBData = (uint16_t)analogRead(DA);

  delayMicroseconds(1);

  //Get Mic A data from channel 3(pin 12 on mx)
  digitalWrite(channelA, HIGH);
  digitalWrite(channelB, HIGH);
  digitalWrite(channelC, LOW);
  delayMicroseconds(1);   // Delay to give mx some time to switch channel
  pmicAData = (uint16_t)analogRead(DA);
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  // init mx
  pinMode(channelA, OUTPUT);
  pinMode(channelB, OUTPUT);
  pinMode(channelC, OUTPUT);

  memset(adcFilterBuffer, 0, sizeof(adcFilterBuffer)); // Set all values in buffer to 0
  delay(500);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  delay(500);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("BOOTED DUAL MIC TESTSCRIPT.. GET READY....");
  delay(2000);
  Serial.println(" ");
  Serial.print("READY..");
  delay(1000);
  Serial.print("SET..");
  delay(1000);
  Serial.println("GO..");
  Serial.println("SAMPLING...");

  //poll data

  for (int i = 0; i < amountOfPolls; i++) {
    /////RAW WITHOUT FILTER
    getMicVal(valuesA[i], valuesB[i]);

    /////MOVING AVERAGE FILTER
    //    for (uint8_t i = 0; i < adcFilterBufferSize - 1; i++) { // Remove the oldest value by moving all values one step closer to the start of the array
    //      adcFilterBuffer[i] = adcFilterBuffer[i + 1];
    //    }
    //
    //    adcFilterBuffer[adcFilterBufferSize - 1] = analogRead(DA); // Save the latest ADC value at the back of the array.
    //    uint16_t adcFilterBufferSum = 0;
    //    for (uint8_t i = 0; i < adcFilterBufferSize; i++) { // Add up all the values
    //      adcFilterBufferSum += adcFilterBuffer[i];
    //    }
    //    adcValue = adcFilterBufferSum / adcFilterBufferSize; // Get the average
    //    values[i] = adcValue;
    ///MOVING AVERAGE FILTER

    //    if (adcValue >= threshold) { //Compare analog value with threshold
    //      digitalWrite(led, LOW);  //Turn ON Led(LOW=ON)
    //    }
    //    else {
    //      digitalWrite(led, HIGH);  //Turn OFF Led(HIGH=OFF)
    //    }
  delayMicroseconds(100);   // Delay to give mx some time to switch channel
  }

  //Print out
  delay(500);
  Serial.println("DONE SAMPLING... ");
  Serial.println("PRINTING MIC A VALUES... ");
  Serial.println(" ");
  for (int i = 0; i < amountOfPolls; i++) {
    Serial.print(valuesA[i]);
    Serial.print(" ");
  }
  delay(500);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("PRINTING MIC B VALUES... ");
  Serial.println(" ");
  for (int i = 0; i < amountOfPolls; i++) {
    Serial.print(valuesB[i]);
    Serial.print(" ");
  }
}

void loop() {
  //End program
  while (1) {
    delay(100);
  }
}
