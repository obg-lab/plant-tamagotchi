const int SOIL_PIN = A0;

int soilReadInterval = 5 * 1000;
long lastSoilMillis = millis() + soilReadInterval;
int lastSoilRead = 0;

const int airValue = 610;
const int waterValue = 320;
int soilmoisturepercent=0;

int getSoil() {
  if (millis() - lastSoilMillis > soilReadInterval) {
   int sensorValue = analogRead(SOIL_PIN);
   soilmoisturepercent = map(sensorValue, airValue, waterValue, 0, 100);
   lastSoilRead = soilmoisturepercent;

   // Serial.print(F("Calibragem do Solo: "));
   // Serial.println(sensorValue);

   Serial.print(F("Sensor Solo: "));
   Serial.println(soilmoisturepercent);

   sendSoilData(soilmoisturepercent);
   lastSoilMillis = millis();
  }
  return lastSoilRead;
}
