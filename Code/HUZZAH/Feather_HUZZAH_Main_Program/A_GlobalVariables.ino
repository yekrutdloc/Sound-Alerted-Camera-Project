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
bool taskSoundSensorsStarted = 0;
bool taskBuzzerStarted = 0;
bool taskHTTPStarted = 0;
bool taskMemStarted = 0;

/*
  ---------------------------------------------------------------
  Task-to-Task communication
  ---------------------------------------------------------------
*/
// HTTP
bool sendGETRequestPing = 0; // tell HTTP task to send a HTTP GET-Request test
bool sendDatabaseInfo = 0; // tell HTTP task to send information to database
// Buzzer
bool doStartupChime = 0; // Tell buzzer to do startup chime
bool doWifiNotFoundChime = 0; // Tell buzzer to do "Wi-Fi not found" chime
bool doLoudNoiseDetected = 0; // Tell buzzer to do "Loud Noise Detected" chime

/*
  ---------------------------------------------------------------
  Sound Sensor
  ---------------------------------------------------------------
*/
unsigned long sensorASoundDetected = 0; // Has a value above 0 when a sound is detected
unsigned long sensorBSoundDetected = 0; // Has a value above 0 when a sound is detected
int8_t degreeOfSound = 0;
