/*


  ██╗    ██╗ █████╗ ████████╗███████╗██████╗ ██╗███╗   ██╗ ██████╗
  ██║    ██║██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██║████╗  ██║██╔════╝
  ██║ █╗ ██║███████║   ██║   █████╗  ██████╔╝██║██╔██╗ ██║██║  ███╗
  ██║███╗██║██╔══██║   ██║   ██╔══╝  ██╔══██╗██║██║╚██╗██║██║   ██║
  ╚███╔███╔╝██║  ██║   ██║   ███████╗██║  ██║██║██║ ╚████║╚██████╔╝
   ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
                                             v0.1.0 by FrostSTeeL

  WATERING is an Arduino project to water plants autonomously by
  using soil moisture sensor and a pump.

  Milisecond examples *********************************************
  12 Hours     = 43200000 ms
  6 Hours      = 21600000 ms
  1 Hour       = 3600000 ms
  30 Minutes   = 1800000 ms
  1 Minute     = 60000 ms
  30 Seconds   = 30000 ms
  15 Seconds   = 15000 ms

  Pump specs ******************************************************
  9v 1 minute = 1.5 liters

*/
// Don't touch ****************************************************
int probe = A0;     // Probe analog port
int probeRead;      // Probe data variable
int pump = 8;       // Pump digital port

// Settings *******************************************************
int soilHigh = 831;     // Dry soil reading
int soilLow = 500;      // Moist soil reading
int pumpTime = 5000;    // Miliseconds to pump
int waitTime = 10000;   // Miliseconds to wait for remeasure

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);
}

// Main logic *****************************************************
void loop() {
  probeRead = analogRead(probe);

  // Map sensor data to %
  probeRead = map(probeRead, soilLow, soilHigh, 100, 0);

  // Sensor data smoothing
  int numReads = 20;
  int senseSum = 0;
  for (int k = 0; k < numReads; k++) {
    senseSum += probeRead;
    delay(100);
  }

  int senseAve = senseSum / numReads;
  delay(500);
  Serial.print("Raw probe data: ");
  Serial.print(analogRead(probe));
  Serial.print(" - Soil moisture: ");
  Serial.print(senseAve);
  Serial.println("%");

  // Pump trigger
  if (senseAve < 20)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pump, LOW);
    Serial.println("Pumping Water for 5 seconds");
    delay(pumpTime);
    Serial.println("Stopping pump, waiting 10 seconds to remeasure");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pump, HIGH);
    delay(waitTime);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pump, HIGH);
  }
}
