const int ADC_PIN = 32;                    // Pin ADC (GPIO32 por defecto)
const int ADC_RESOLUTION = 12;             // Resolución ADC en bits (12 bits = 0-4095)
const float SAMPLING_FREQUENCY = 10000.0;  // Frecuencia de muestreo en Hz
const float SAMPLE_DURATION = 1.0;         // Duración del muestreo en segundos

const int BUFFER_SIZE = (int)(SAMPLING_FREQUENCY * SAMPLE_DURATION);
uint16_t* sampleBuffer;
volatile int sampleIndex = 0;
volatile bool samplingComplete = false;

hw_timer_t* timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  
  if (sampleIndex < BUFFER_SIZE) {
    sampleBuffer[sampleIndex] = analogRead(ADC_PIN);
    sampleIndex++;
  } else {
    samplingComplete = true;
  }
  
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  analogReadResolution(ADC_RESOLUTION);
  analogSetAttenuation(ADC_11db); // Rango completo 0-3.3V
  
  // Asignar memoria para el buffer
  sampleBuffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
  if (sampleBuffer == NULL) {
    Serial.println("Error: No se pudo asignar memoria");
    while(1);
  }
  
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  
  uint64_t timerPeriod = (uint64_t)(1000000.0 / SAMPLING_FREQUENCY);
  timerAlarmWrite(timer, timerPeriod, true);
  
  Serial.println("Sistema iniciado");
  Serial.print("Frecuencia de muestreo: ");
  Serial.print(SAMPLING_FREQUENCY);
  Serial.println(" Hz");
  Serial.print("Tamaño del buffer: ");
  Serial.print(BUFFER_SIZE);
  Serial.println(" muestras");
  Serial.println("---");
  
  delay(2000);
}

void loop() {
  sampleIndex = 0;
  samplingComplete = false;
  
  // Iniciar muestreo
  timerAlarmEnable(timer);
  
  // Esperar a que se complete el muestreo
  while (!samplingComplete) {
    yield();
  }
  
  // Detener timer
  timerAlarmDisable(timer);
  
  // Imprimir muestras para Serial Plotter
  for (int i = 0; i < BUFFER_SIZE; i++) {
    Serial.println(sampleBuffer[i]);
  }
  
  // Pausa antes del siguiente ciclo
  delay(1000);
}