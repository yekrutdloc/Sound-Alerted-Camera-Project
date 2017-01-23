/*
  ---------------------------------------------------------------
  This is the global logical variables tab.
  All global variables are here.
  What differs from logical variables and config variables are 
  that logical variables are used for logical functions, and should NOT be changed.
  It must be named "A_" in the start of the tab-name or else it won't compile
  ---------------------------------------------------------------
*/

/*
  ---------------------------------------------------------------
  Task initialized
  Some tasks depend on other tasks to start before starting itself,
  with these variables they can check if the depending task has started
  ---------------------------------------------------------------
*/
bool taskADCStarted = 0;
bool taskBuzzerStarted = 0;
bool taskHTTPGETStarted = 0;
bool taskMemStarted = 0;

/*
  ---------------------------------------------------------------
  Task-to-Task communication
  ---------------------------------------------------------------
*/
// HTTP
bool sendGETRequestPing = 0; // tell HTTPGET task to send a GETRequest
// Buzzer
bool doStartupChime = 0; // Tell buzzer to do startup chime
bool doWifiNotFoundChime = 0; // Tell buzzer to do "Wi-Fi not found" chime
bool doLoudNoiseDetected = 0; // Tell buzzer to do "Loud Noise Detected" chime

/*
  ---------------------------------------------------------------
  ADC task
  ---------------------------------------------------------------
*/
uint16_t micValue = 0; // The filtered(or unfiltered) value from the ADC, which is connected to the microphone

