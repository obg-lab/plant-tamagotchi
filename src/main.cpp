#include <Arduino.h>
#include <secrets.h>

#include <wifi.h>
#include <ntp.h>
#include <mqtt.h>

#include <display.h>
#include <sensorRain.h>
#include <sensorSoil.h>
#include <sensorEnvironment.h>
#include <environmentSensor.h>

void checkWiFiThenMQTT(void)
{
  connectToWiFi("Checking WiFi");
  connectToMqtt();
}

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println();
  Serial.println();

  setupDisplay();
  setupWifi();
  NTPConnect();
  setupSSL();
  setupMQTT();
  setupEnvironmentSensor();

  connectToMqtt();

  showBitmap("fine");
}

void loop() {
  now = time(nullptr);
  if (!client.connected()) {
    checkWiFiThenMQTT();
  } else {
    client.loop();
    delay(500);

    // // RAIN
    bool isRaining = getRain();
    // SOIL
    int soil = getSoil();
    // ENVIRONMENT
    struct environmentSensor envSensor = getEnvironment();

    // update oled data
    writeOLED(envSensor.temperature, envSensor.humidity, soil);

    if(soil < 5) {
      showBitmap("thirst");
    } else if (soil < 30 && envSensor.humidity < 30) {
      showBitmap("sad");
    } else if (isRaining) {
      showBitmap("happy");
    } else {
      showBitmap("fine");
    }

    loopDisplay();
  }
}
