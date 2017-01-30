/*
  ---------------------------------------------------------------
    Main program for Feather HUZZAH
    Combines Scheduler, task-to-task communication, Buzzer feedback, Interrupts 
    and HTTP GET/POST request Webclient to this projects.

    The buzzer will be used to provide feedback. When Wi-Fi is not 
    found, an error beep occurs, when it starts up successfully, a 
    startup beep occurs. When an accident is found, a beep alert occurs etc.


    Notes:
    
    -There is noise on the ADC when receiving/transmitting on Wi-Fi 
    while using the ADC! Try to use one function at a time to minimize ADC noise
    
    -Sometimes it won't be able to connect to Wi-Fi after uploading new 
    code, try pressing the RESET switch on the ESP8266, this should reset the Wi-Fi module.
      If it didn't work, try disconnecting then reconnecting the power/USB-cable.
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
  Needed here to compile.
  Always keep these "function prototypes" on the bottom of this tab, or else the code might not compile.
  ---------------------------------------------------------------
*/
void setup();
void loop();
void sensorAInterruptWrap();
void sensorBInterruptWrap();


