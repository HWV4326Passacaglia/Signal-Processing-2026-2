#define SIGMA_DELTA_PIN 18
//https://docs.espressif.com/projects/arduino-esp32/en/latest/api/sigmadelta.html

void setup() {
  //setup on pin 18 with frequency 312500 Hz
  sigmaDeltaAttach(SIGMA_DELTA_PIN, 312500);
  //set pin 18 to off
  sigmaDeltaWrite(SIGMA_DELTA_PIN, 0);
}

void loop() {
  //slowly ramp-up the value
  //will overflow at 256
  static uint8_t i = 0;
  sigmaDeltaWrite(SIGMA_DELTA_PIN, i++);
  delay(100);
}
