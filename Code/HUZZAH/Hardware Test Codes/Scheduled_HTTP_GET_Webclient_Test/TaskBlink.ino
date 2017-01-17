/*
  ---------------------------------------------------------------
  BlinkTask class declaration
  Blinks LED
  ---------------------------------------------------------------
*/
class BlinkTask : public Task {
  protected:
    void setup() {
      state = HIGH;

      pinMode(2, OUTPUT);
      pinMode(2, state);
    }

    void loop() {
      state = state == HIGH ? LOW : HIGH;
      pinMode(2, state);

      delay(1000);
    }

  private:
    uint8_t state;
} blink_task;

