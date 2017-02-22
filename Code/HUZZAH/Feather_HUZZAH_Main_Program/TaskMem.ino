/*
  ---------------------------------------------------------------
  MemTask class declaration
  Prints free heap memory
  ---------------------------------------------------------------
*/
class MemTask : public Task {
  public:
    void setup() {
      taskMemStarted = 1; // Set started flag
    }

    void loop() {
      yield(); // Allow other essential backgrund tasks to run
      delay(10000);
      Serial.print(F("Free Heap: "));
      Serial.print(ESP.getFreeHeap());
      Serial.println(F(" bytes"));
    }
} mem_task;
