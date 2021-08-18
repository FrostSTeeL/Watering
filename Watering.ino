/*


  ██╗    ██╗ █████╗ ████████╗███████╗██████╗ ██╗███╗   ██╗ ██████╗
  ██║    ██║██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██║████╗  ██║██╔════╝
  ██║ █╗ ██║███████║   ██║   █████╗  ██████╔╝██║██╔██╗ ██║██║  ███╗
  ██║███╗██║██╔══██║   ██║   ██╔══╝  ██╔══██╗██║██║╚██╗██║██║   ██║
  ╚███╔███╔╝██║  ██║   ██║   ███████╗██║  ██║██║██║ ╚████║╚██████╔╝
   ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
                                             v0.2.0 by FrostSTeeL

  WATERING is an Arduino project to water plants autonomously by
  using soil moisture sensor and a pump.
  https://github.com/FrostSTeeL/Watering

  Milisecond examples *********************************************
  12 Hours     = 43200000 ms
  6 Hours      = 21600000 ms
  1 Hour       = 3600000 ms
  30 Minutes   = 1800000 ms
  1 Minute     = 60000 ms
  30 Seconds   = 30000 ms
  15 Seconds   = 15000 ms

  Pump specs ******************************************************
  12v 30 seconds = 750ml
  12v 15 seconds = 375ml

*/
// Don't touch ****************************************************
const int probe = A0;     // Probe analog port
int probeRead;            // Probe data variable
const int pumpPin1 = 2;
const int pumpPin2 = 3;
const int fanPin1 = 5;
const int fanPin2 = 6;


// Settings *******************************************************
int soilHigh = 800;      // Dry soil reading
int soilLow = 500;       // Moist soil reading
int pumpTime = 5000;     // Miliseconds to pump
int waitTime = 1000;     // Miliseconds to wait for remeasure
int measureTime = 1000;  // Time between measurements
int moistureLvl = 20;    // Moisture level to trigger pump (0-100%)

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pumpPin1, OUTPUT);
  pinMode(pumpPin2, OUTPUT);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  digitalWrite(fanPin1, HIGH); // Start the cooling fan
  digitalWrite(fanPin2, LOW);  // Start the cooling fan
}

// Main logic *****************************************************
void loop() {
  probeRead = analogRead(probe);

  // Map sensor data to %
  probeRead = map(probeRead, soilLow, soilHigh, 100, 0);

  /* Sensor data smoothing (might be useful)
    int numReads = 30;
    int senseSum = 0;
    for (int k = 0; k < numReads; k++) {
    senseSum += probeRead;
    delay(2000);
    }
    int senseAve = senseSum / numReads;
  */

  Serial.print(F("Raw probe data: "));
  Serial.print(analogRead(probe));
  Serial.print(F(" - Soil moisture: "));
  Serial.print(probeRead);
  Serial.println(F("%"));
  delay(measureTime);

  // Pump trigger
  if (probeRead < moistureLvl)
  {
    digitalWrite(LED_BUILTIN, HIGH);

    digitalWrite(pumpPin1, HIGH);
    digitalWrite(pumpPin2, LOW);

    Serial.println(F("Pumping for "));
    Serial.print(pumpTime);
    Serial.println(F(" ms"));
    delay(pumpTime);
    digitalWrite(pumpPin1, LOW);
    digitalWrite(pumpPin2, LOW);
    Serial.println(F("Stopping pump, waiting "));
    Serial.print(waitTime);
    Serial.println(F(" ms to remeasure"));
    digitalWrite(LED_BUILTIN, LOW);

    delay(waitTime);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pumpPin1, LOW);
    digitalWrite(pumpPin2, LOW);
  }
}
