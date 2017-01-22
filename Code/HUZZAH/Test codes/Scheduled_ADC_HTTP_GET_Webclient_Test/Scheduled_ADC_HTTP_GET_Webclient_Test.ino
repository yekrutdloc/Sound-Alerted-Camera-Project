/*
  ---------------------------------------------------------------
    This is a simple test which combines Scheduler, ADC and HTTP GET Webclient.
    The ESP8266 keeps polling the ADC, getting the latest ADC values. Sometimes, it will send a signal
    to the task which is sending HTTP GET Requests, telling it to send some values to a webserver.
    This is to simulate whenever an accident is detected, that it sends important data to the database and controls the camera
    For this test we will mainly focus on showing how to read analog values using the ESP8266, how task-to-task communication works.

    Notes:
    -There is noise on the ADC when receiving/transmitting on Wi-Fi while using the ADC! Try to use one function at a time to minimize ADC noise
    -Sometimes it won't be able to connect to Wi-Fi after uploading new code, try pressing the RESET switch on the ESP8266, this should reset the Wi-Fi module.
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
