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
  // Initialize Serial
  Serial.begin(115200);
  Serial.println("");
  delay(1000);

  // Declare tasks
  Serial.println("Starting scheduler");
  delay(1000);
  Scheduler.start(&adc_task); // Declare ADC task
  Scheduler.start(&gethttp_task); // Declare HTTP GET webclient task
  //Scheduler.start(&mem_task); // Declare printing of heap memory task

  // Start scheduler/all tasks declared
  Scheduler.begin();
}

/*
  ---------------------------------------------------------------
    This loop function is not used.
  ---------------------------------------------------------------
*/
void loop() {
  // Program never enter this function
}
