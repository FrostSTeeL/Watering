const int probe = A0;
int probeRead;
int pump = 8;
int soilLow = 600;  // Moist soil reading
int soilHigh = 850; // Dry soil reading

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  delay(1000);
}

void loop() {
  // Debug *******************************************
  //Serial.println(probe);

  // Main logic **************************************
  probeRead = analogRead(probe);
  // Map sensor data to %
  probeRead = map(probeRead, soilLow, soilHigh, 100, 0);
  // Sensor data smoothing
  int numReads = 10;
  int senseSum = 0;
  for (int k = 0; k < numReads; k++) {
    senseSum += probeRead;
    delay(100);
  }
  int senseAve = senseSum / numReads;
  // Serial monitor print
  Serial.print("Soil moisture: ");
  Serial.print(senseAve);
  Serial.println("%");
  //Pump trigger
  if (senseAve > 50)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pump, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pump, LOW);
  }

}
