const int RAIN_PIN = D6;

bool getRain() {
 bool sensorValue = 0;
 sensorValue = digitalRead(RAIN_PIN);
 if(sensorValue == 0) {
   Serial.print(F("Sensor Chuva: "));
   Serial.println(sensorValue);

   sendRainData(1);
 }
 return sensorValue == 0;
}
