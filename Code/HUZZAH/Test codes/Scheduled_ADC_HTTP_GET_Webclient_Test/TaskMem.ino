/*
  ---------------------------------------------------------------
  MemTask class declaration
  Prints free heap memory
  ---------------------------------------------------------------
*/
class MemTask : public Task {
  public:
    void loop() {
      Serial.print("Free Heap: ");
      Serial.print(ESP.getFreeHeap());
      Serial.println(" bytes");

      delay(10000);
    }
} mem_task;
