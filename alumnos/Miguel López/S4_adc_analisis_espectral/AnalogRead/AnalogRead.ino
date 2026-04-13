#define ADC_PIN 28
#define ANALOG_RESOLUTION 12

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  //set the resolution to 12 bits (0-4095)
  analogReadResolution(ANALOG_RESOLUTION);
}

void loop() {
  // read the analog / millivolts value for pin 2:
  int analogValue = analogRead(ADC_PIN);
  int analogVolts = analogReadMilliVolts(ADC_PIN);

  // print out the values you read:
  Serial.printf("ADC analog value = %d\n", analogValue);
  Serial.printf("ADC millivolts value = %d\n", analogVolts);

  //TODO Modificarlo para que en Serial Plotter se vea la salida de analog value y milivolts value
  //¿Por qué son diferentes?
  //Hint:https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/adc.html

  delay(100);  // delay in between reads for clear read from serial
}
