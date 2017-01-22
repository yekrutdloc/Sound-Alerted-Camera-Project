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
      Serial.print(F("Free Heap: "));
      Serial.print(ESP.getFreeHeap());
      Serial.println(F(" bytes"));

      delay(10000);
    }
} mem_task;