/*
  ---------------------------------------------------------------
    Here we set up the scheduler.
    This tab has to be the last tab in order to compile,
    that is why there is an "_" (underscore) in front of the tab name.
    These functions are the first function to be ran by Arduino, but has to be in the last tab because
    programming is linear and all calls made from these funtions has to be declared in previous tabs.
  ---------------------------------------------------------------
*/
void setup() {
  // Initialize Red Status LED
  pinMode(ledRedPin, OUTPUT);
  digitalWrite(ledRedPin, LOW); // Turn on LED(LED is inverted, so HIGH is off)

  // Initialize Serial
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  Serial.println("");
  Serial.println("");
  Serial.println("Starting scheduler...");
  delay(100); // Some time for serial buffer to empty

  // Declare tasks
  //Scheduler.start(&buzzer_task); // Declare Buzzer task
  Scheduler.start(&soundsensors_task); // Declare SoundSensors task
  Scheduler.start(&http_task); // Declare HTTP webclient task

  //Scheduler.start(&mem_task); // Declare printing of heap memory task

  // Start scheduler/all tasks declared
  Scheduler.begin();
}
/*
  ---------------------------------------------------------------
  Needed for interrupt-functions to properly work within classes.
  Read more: http://forum.arduino.cc/index.php?topic=41713.0
  ---------------------------------------------------------------
*/
SoundSensorsTask soundSensorTask;
void sensorAInterruptWrap() {
  soundSensorTask.sensorAInterrupt();
}
void sensorBInterruptWrap() {
  soundSensorTask.sensorBInterrupt();
}
void pauseInterruptsWrap() {
  soundSensorTask.pauseInterrupts();
}
void unpauseInterruptsWrap() {
  soundSensorTask.unpauseInterrupts();
}
/*
  ---------------------------------------------------------------
    This loop function is not used.
  ---------------------------------------------------------------
*/
void loop() {
  // Program never enter this function
}
