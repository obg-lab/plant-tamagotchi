#include <Arduino.h>
#include <time.h>

unsigned long lastMillis = 0;
time_t now;
time_t nowish = 1510592825;

#ifdef USE_SUMMER_TIME_DST
uint8_t DST = 1;
#else
uint8_t DST = 0;
#endif


void NTPConnect(void)
{
  Serial.print("Configurando hora via NTP ");
  configTime(TIME_ZONE * 3600, DST * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("feito!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Hora atual: ");
  Serial.print(ctime(&now));
}

time_t getNow() {
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);

  return now;
}
