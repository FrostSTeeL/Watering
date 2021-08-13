/*


  ██╗    ██╗ █████╗ ████████╗███████╗██████╗ ██╗███╗   ██╗ ██████╗
  ██║    ██║██╔══██╗╚══██╔══╝██╔════╝██╔══██╗██║████╗  ██║██╔════╝
  ██║ █╗ ██║███████║   ██║   █████╗  ██████╔╝██║██╔██╗ ██║██║  ███╗
  ██║███╗██║██╔══██║   ██║   ██╔══╝  ██╔══██╗██║██║╚██╗██║██║   ██║
  ╚███╔███╔╝██║  ██║   ██║   ███████╗██║  ██║██║██║ ╚████║╚██████╔╝
   ╚══╝╚══╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
                                             v0.1.0 by FrostSTeeL

  Watering is an Arduino project to water plants autonomously by
  using soil moisture sensor and a pump.

  Milisecond examples *********************************************
  12 Hours   = 43200000 ms
  6 Hours    = 21600000 ms
  1 Hour     = 3600000 ms
  30 Minutes = 1800000 ms
  1 Minute   = 60000 ms

  Pump specs ******************************************************
  9v 1 minute = 1.5 liters


*/

int probe = A0;     // Probe analog port
int probeRead;      // Probe data variable
int pump = 8;       // Pump digital port
int soilLow = 438;  // Moist soil reading
int soilHigh = 500; // Dry soil reading

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  delay(1000);
}

void loop() {


  // Main logic ************************************************
  probeRead = analogRead(probe);
  // Debug *****************************************************
  // Serial.println(probeRead);
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
  // Serial.println(probeRead);
  delay(500);

  Serial.print("Soil moisture: ");
  Serial.print(senseAve);
  Serial.println("%");
  // Pump trigger
  if (senseAve < 30)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pump, LOW);
    Serial.println("Pumping Water for 30 seconds");
    delay(30000);
    Serial.println("Stopping pump, waiting 30 seconds to remeasure");
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pump, HIGH);
    delay(30000);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(pump, HIGH);
  }
}
