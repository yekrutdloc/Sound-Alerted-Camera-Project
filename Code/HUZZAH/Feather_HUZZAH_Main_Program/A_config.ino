/*
  ---------------------------------------------------------------
  This is the config tab.
  All tweakable settings are here.
  It must be named "A_" in the start of the tab-name or else it won't compile
  ---------------------------------------------------------------
*/

/*
  ---------------------------------------------------------------
  Wi-Fi settings
  ---------------------------------------------------------------
*/
const char* ssid = "Router";
const char* password = "kungarike";
const char* host = "wifitest.adafruit.com";
const uint8_t wifiConnectTimeout = 10; // The amount of seconds to wait until giving up connecting to Wi-Fi

/*
  ---------------------------------------------------------------
  Pin-outs
  ---------------------------------------------------------------
*/
const uint8_t ledRedPin = 0; // pin to the red LED
const uint8_t ledBluePin = 2; // pin to the blue LED
const uint8_t buzzerPin = 14; // pin to buzzer
const uint8_t micAdcPin = A0; // pin to ADC/microphone

/*
  ---------------------------------------------------------------
   Execution frequency(does not account for execution times).
   So if a task has an exeution frequency of 10ms, and the task takes 5ms to execute one loop of its code, 
   then the total sample time is 15ms(10+5).
  ---------------------------------------------------------------
*/
const uint16_t adcExeutionFrequency = 10; // ADC

/*
  ---------------------------------------------------------------
  ADC-task
  ---------------------------------------------------------------
*/
// How often to print out the adc value. Because of how fast we poll the mic, when we try to print out every
// ADC value it slows down the overall program. In some 
// instances the sample rate of the task slows down 500% when printing the mic value vs when not.
// If this value is set to 3, then we print out every third value we poll
const uint8_t adcSerialPrintFrequency = 10; 

const uint16_t micVolumeThreshold = 550;// Threshold the adc value should reach past when a loud sound occurs
const uint8_t adcFilterBufferSize = 3; // Size of the moving average filtering buffer

