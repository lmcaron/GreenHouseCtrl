// Green House Control
// Louis-Martin Caron 2022-05-04

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 6     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

//sorties relais
const int relay[4] = {10,11,12,13};

//autres variables
long now = 180000;
long time0 = 0;
long time1 = 0;
long time2 = 0;
long time3 = 0;
long deltaTime1 = 0;
long deltaTime2 = 0;
long deltaTime3 = 0;
long heatTime = 0;
bool countState = LOW;
bool ventilation = LOW;
int incomingByte = 0;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  for (int j = 0; j < sizeof(relay)/sizeof(relay[0]); j++){ 
    pinMode(relay[j], OUTPUT);
    digitalWrite(relay[j], HIGH);    
  }
  Serial.begin(9600);
  //Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  now = millis();

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //  // Compute heat index in Fahrenheit (the default)
  //  float hif = dht.computeHeatIndex(f, h);
  //  // Compute heat index in Celsius (isFahreheit = false)
  //  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity:");
  Serial.println(h, 1);
  Serial.print("Temperature:");
  Serial.println(t, 1);

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if(incomingByte == 48){
      digitalWrite(relay[2], HIGH);
      }
    if(incomingByte == 49){
      digitalWrite(relay[2], LOW);
      }
  }
}
