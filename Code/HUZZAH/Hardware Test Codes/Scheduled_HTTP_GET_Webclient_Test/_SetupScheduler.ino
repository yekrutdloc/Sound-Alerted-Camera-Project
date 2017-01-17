/*
  ---------------------------------------------------------------
    This tab has to be the last tab in order to compile,
    that is why there is an "_" (underscore) in front of the tab name.
    This function is the first function to be ran by Arduino,
    here we set up the scheduler.
  ---------------------------------------------------------------
*/
void setup() {
  // Initialize Serial
  Serial.begin(115200);
  Serial.println("");
  delay(1000);

  // Connecting to the WiFi network
  // This has to be here because WiFi.status()-function does not work anywhere else than in this function and in loop()
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Declare tasks
  Serial.println("Starting scheduler");
  delay(1000);
  //Scheduler.start(&blink_task); // Declare LED blink task
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
