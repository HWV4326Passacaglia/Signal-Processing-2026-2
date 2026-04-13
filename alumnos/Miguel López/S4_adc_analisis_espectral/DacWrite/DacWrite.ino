#define PIN_ADC 32
#define PIN_DAC 25
#define ADC_RESOLUTION 12
//https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/dac.html

// Parámetros para señal coseno (comentado por defecto)
// #define FRECUENCIA 1.0
// #define AMPLITUD 127.5
// #define Parámetro sorpresa que necesitarán después

 int adcValue;
 int dacValue;
 float cosineValue;

void setup() {
  Serial.begin(115200);

  // configure ADC resolution to 12 bits (0-4095)
  analogReadResolution(ADC_RESOLUTION);
}

void loop() {
  // read analog value from ADC pin
  adcValue = analogRead(PIN_ADC);
  
  // map ADC resolution (12-bit) to DAC resolution (8-bit)
  dacValue = map(adcValue, 0, 4095, 0, 255);
  
  // write value to DAC output
  dacWrite(PIN_DAC, dacValue);
  
  // print values for monitoring
  Serial.printf("ADC: %d -> DAC: %d\n", adcValue, dacValue);
  
  // TODO: Implementar generación de señal coseno
  // Descomentar el siguiente bloque para generar señal coseno en lugar de copiar ADC
  /*
  unsigned long currentTime = millis();
  float timeSeconds = currentTime / 1000.0;
  
  //Poner mucha atención porque se requerirá un valor más
  cosineValue = AMPLITUD * cos(2 * PI * FRECUENCIA * timeSeconds);  
  dacWrite(PIN_DAC, cosineValue;
  
  Serial.printf("Time: %.3f s, DAC: %d\n", timeSeconds, dacValue);
  */
  
  delay(10);
}