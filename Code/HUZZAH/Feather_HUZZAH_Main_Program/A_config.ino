/*
  ---------------------------------------------------------------
  This is the config tab.
  All tweakable settings are here.
  It must be named "A_" in the start of the tab-name or else it won't compile
  ---------------------------------------------------------------
*/

/*
  ---------------------------------------------------------------
  HTTP/Wi-Fi settings
  ---------------------------------------------------------------
*/
const char* ssid = "mahproj";
const char* password = "maffia14";
const uint8_t wifiConnectTimeout = 10; // The amount of seconds to wait until giving up connecting to Wi-Fi
const char* testingHost = "wifitest.adafruit.com";
const char* cameraIP = "192.168.11.20";
const char* databaseIP = "188.166.72.14";
const String cam_id = "1";
const String location = "55.610823,12.9928";

/*
  ---------------------------------------------------------------
  Pin-outs
  ---------------------------------------------------------------
*/
const uint8_t ledRedPin = 0; // pin to the red LED, used to show if HUZZAH program is running or not, also used in sync with buzzer
const uint8_t ledBluePin = 2; // pin to the blue LED. DON't USE!(dont pinmode!), used for checking Wi-Fi traffic!!
const uint8_t buzzerPin = 14; // pin to buzzer
const uint8_t sensorPinA = 12; // pin to Sound sensor A
const uint8_t sensorPinB = 13; // pin to Sound sensor B

/*
  ---------------------------------------------------------------
   Execution frequency in microseonds(does not mean sample time and does not account for execution times).
   So if a task has an exeution frequency of 10ms, and the task takes 5ms to execute one loop of its code,
   then the total sample time is 15ms(10+5).
  ---------------------------------------------------------------
*/
const uint16_t soundSensorExeutionFrequency = 1000; // How often to check if both sound sensors has triggered
const uint16_t httpExeutionFrequency = 1000; // How often to check if a HTTP request is scheduled to run
const uint16_t buzzerExeutionFrequency = 1000; // How often to check if a HTTP request is scheduled to run

/*
  ---------------------------------------------------------------
  Sound sensors
  ---------------------------------------------------------------
*/

