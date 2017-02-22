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
volatile bool taskSoundSensorsStarted = 0;
volatile bool taskBuzzerStarted = 0;
volatile bool taskHTTPStarted = 0;
volatile bool taskMemStarted = 0;

/*
  ---------------------------------------------------------------
  Task-to-Task communication
  ---------------------------------------------------------------
*/
// HTTP
volatile bool sendGETRequestPing = 0; // tell HTTP task to send a HTTP GET-Request test
volatile bool sendDatabaseInfo = 0; // tell HTTP task to send information to database
// Buzzer
volatile bool doStartupChime = 0; // Tell buzzer to do startup chime
volatile bool doWifiNotFoundChime = 0; // Tell buzzer to do "Wi-Fi not found" chime
volatile bool doLoudNoiseDetected = 0; // Tell buzzer to do "Loud Noise Detected" chime

/*
  ---------------------------------------------------------------
  Sound Sensor
  ---------------------------------------------------------------
*/
volatile unsigned long sensorASoundDetected = 0; // Has a value above 0 when a sound is detected
volatile unsigned long sensorBSoundDetected = 0; // Has a value above 0 when a sound is detected
volatile int8_t degreeOfSound = 0;
