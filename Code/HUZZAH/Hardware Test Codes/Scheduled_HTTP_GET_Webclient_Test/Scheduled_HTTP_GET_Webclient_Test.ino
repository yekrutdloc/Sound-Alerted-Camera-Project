/*
  ---------------------------------------------------------------
    This is a simple test which combines Scheduler and HTTP GET Webclient.
    While it continously makes GET-requests, it also blinks the onboard LED.

    Notes:
    Sometimes it won't be able to connect to Wi-Fi after uploading new code, try pressing the RESET switch on the ESP8266, this should reset the Wi-Fi module.
  ---------------------------------------------------------------
*/

/*
  ---------------------------------------------------------------
  Library includes
  ---------------------------------------------------------------
*/
//Needed for Scheduler
#include <Arduino.h>
#include <Scheduler.h>
//Needed for HTTP GET Webclient
#include <ESP8266WiFi.h>

/*
  ---------------------------------------------------------------
  Needed here to setup scheduler.
  Always keep these "function prototypes" on the bottom of this tab.
  ---------------------------------------------------------------
*/
void setup();
void loop();
