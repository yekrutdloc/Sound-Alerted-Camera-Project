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
const uint8_t wifiConnectTimer = 10; // The amount of seconds to wait untill giving up connecting to Wi-Fi

/*
  ---------------------------------------------------------------
  Pin-outs
  ---------------------------------------------------------------
*/
const uint8_t buzzerPin = 14; // pin to buzzer
