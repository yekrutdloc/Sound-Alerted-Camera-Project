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
int buzzerPin = 10;

const uint8_t adcFilterBufferSize = 10; // Change buffer size here
uint16_t adcFilterBufferA[adcFilterBufferSize];
uint16_t adcFilterBufferB[adcFilterBufferSize];

const uint16_t amountOfPolls = 4000; // The amount of times to poll
uint16_t valuesA[amountOfPolls];
uint16_t valuesB[amountOfPolls];
uint16_t timeA = 0;
uint16_t timeB = 0;
uint16_t timeADone = 0;
uint16_t timeBDone = 0;
uint16_t timeAX = 0;
uint16_t timeBX = 0;

uint32_t timeHigh = 2080;
uint32_t timeLow = 2020;

uint32_t timeTestStart = 0;
uint32_t timeTestEnd = 0;

uint32_t timeLoopStart = 0;
uint32_t timeBuzzerBegin = 10000; // what time to start buzzer
uint32_t timeBuzzerLength = 30000; // set length of buzzer in microseconds

//multiplex channel pins
uint8_t channelA = 50;
uint8_t channelB = 47;
uint8_t channelC = 41;


void getMicVal(uint16_t &pmicAData, uint16_t &pmicBData) {

  //Get Mic B data from channel 0(pin 13 on mx)
  digitalWrite(channelA, LOW);
  digitalWrite(channelB, LOW);
  digitalWrite(channelC, LOW);
  delayMicroseconds(1);   // Delay to give mx some time to switch channel
  PIO_Set(PIOB, PIO_PB27B_TIOB0);
  while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY)
  {}; //Wait for end of conversion
  PIO_Clear(PIOB, PIO_PB27B_TIOB0);
  pmicBData = adc_get_latest_value(ADC); // Read ADC
  //pmicBData = analogRead(DA);

  delayMicroseconds(1);

  //Get Mic A data from channel 3(pin 12 on mx)
  digitalWrite(channelA, HIGH);
  digitalWrite(channelB, HIGH);
  digitalWrite(channelC, LOW);
  delayMicroseconds(1);   // Delay to give mx some time to switch channel
  PIO_Set(PIOB, PIO_PB27B_TIOB0);
  while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY)
  {}; //Wait for end of conversion
  PIO_Clear(PIOB, PIO_PB27B_TIOB0);
  pmicAData = adc_get_latest_value(ADC); // Read ADC
  //pmicAData = analogRead(DA);
}

void setup() {
  Serial.begin(115200);
  //pinMode(led, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // init mx
  pinMode(channelA, OUTPUT);
  pinMode(channelB, OUTPUT);
  pinMode(channelC, OUTPUT);
  delay(500);

  //ADC init
  pinMode(DA, INPUT);
  pmc_enable_periph_clk(ID_ADC); // To use peripheral, we must enable clock distributon to it
  adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST); // initialize, set maximum posibble speed
  adc_disable_interrupt(ADC, 0xFFFFFFFF);
  adc_set_resolution(ADC, ADC_12_BITS);
  adc_configure_power_save(ADC, 0, 0); // Disable sleep
  adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1); // Set timings - standard values
  adc_set_bias_current(ADC, 1); // Bias current - maximum performance over current consumption
  adc_stop_sequencer(ADC); // not using it
  adc_disable_tag(ADC); // it has to do with sequencer, not using it
  adc_disable_ts(ADC); // deisable temperature sensor
  adc_disable_channel_differential_input(ADC, ADC_CHANNEL_7);
  adc_configure_trigger(ADC, ADC_TRIG_SW, 1); // triggering from software, freerunning mode
  adc_disable_all_channel(ADC);
  adc_enable_channel(ADC, ADC_CHANNEL_7); // just one channel enabled
  adc_start(ADC);

  getMicVal(valuesA[0], valuesB[0]); // init mx

  delay(500);
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("BOOTED DUAL MIC TESTSCRIPT.. GET READY....");


  memset(adcFilterBufferA, 0, sizeof(adcFilterBufferA)); // Set all values in buffer to 0
  memset(adcFilterBufferB, 0, sizeof(adcFilterBufferB)); // Set all values in buffer to 0
  for (uint8_t i = 0; i < adcFilterBufferSize; i++) { // Fill buffers with current adc values
    getMicVal(valuesA[i], valuesB[i]);
    adcFilterBufferA[i] = valuesA[i];
    adcFilterBufferB[i] = valuesB[i];
    delayMicroseconds(100);
  }

  //poll datax
  delay(50);
  timeLoopStart = micros();
  for (int i = 0; i < amountOfPolls; i++) {
    /////RAW WITHOUT FILTER
    //timeTestStart = micros();
    getMicVal(valuesA[i], valuesB[i]);



    uint16_t adcFilterBufferSum = 0;
    /////MOVING AVERAGE FILTER A
    for (uint8_t i = 0; i < adcFilterBufferSize - 1; i++) { // Remove the oldest value by moving all values one step closer to the start of the array
      adcFilterBufferA[i] = adcFilterBufferA[i + 1];
    }

    adcFilterBufferA[adcFilterBufferSize - 1] = valuesA[i]; // Save the latest ADC value at the back of the array.
    adcFilterBufferSum = 0;
    for (uint8_t i = 0; i < adcFilterBufferSize; i++) { // Add up all the values
      adcFilterBufferSum += adcFilterBufferA[i];
    }
    valuesA[i] = adcFilterBufferSum / adcFilterBufferSize; // Get the average

    ///MOVING AVERAGE FILTER B
    for (uint8_t i = 0; i < adcFilterBufferSize - 1; i++) { // Remove the oldest value by moving all values one step closer to the start of the array
      adcFilterBufferB[i] = adcFilterBufferB[i + 1];
    }

    adcFilterBufferB[adcFilterBufferSize - 1] = valuesB[i]; // Save the latest ADC value at the back of the array.
    adcFilterBufferSum = 0;
    for (uint8_t i = 0; i < adcFilterBufferSize; i++) { // Add up all the values
      adcFilterBufferSum += adcFilterBufferB[i];
    }
    valuesB[i] = adcFilterBufferSum / adcFilterBufferSize; // Get the average
    ///MOVING AVERAGE FILTER





    //    if (adcValue >= threshold) { //Compare analog value with threshold
    //      digitalWrite(led, LOW);  //Turn ON Led(LOW=ON)
    //    }
    //    else {
    //      digitalWrite(led, HIGH);  //Turn OFF Led(HIGH=OFF)
    //    }

    uint32_t currenttime = micros() - timeLoopStart;
    // Get difference
    if ((valuesA[i] > timeHigh || valuesA[i] < timeLow) && !timeADone) {
      timeA = currenttime;
      timeADone = 1;
      timeAX = i;
    }
    if ((valuesB[i] > timeHigh || valuesB[i] < timeLow) && !timeBDone) {
      timeB = currenttime;
      timeBDone = 1;
      timeBX = i;
    }

    //Buzzer
    if (currenttime > timeBuzzerBegin + timeBuzzerLength) {
      digitalWrite(buzzerPin, LOW);
    } else if (currenttime > timeBuzzerBegin) {
      digitalWrite(buzzerPin, HIGH);
    }
    //timeTestEnd = micros();
    //Serial.println(timeTestEnd - timeTestStart);
    //delayMicroseconds(1);
  }

  //Print out
  delay(500);
  Serial.println("DONE SAMPLING... ");

  Serial.print("TIME A peak: ");
  Serial.print(timeA);
  Serial.print("us X: ");
  Serial.println(timeAX);

  Serial.print("TIME B peak:");
  Serial.print(timeB);
  Serial.print("us X: ");
  Serial.println(timeBX);

  Serial.print("DIFFERENCE ");
  if (timeA > timeB)
    Serial.println(timeA - timeB);
  else
    Serial.println(timeB - timeA);


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
    delay(1000);
  }
}
