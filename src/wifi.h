#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#define emptyString String()

BearSSL::WiFiClientSecure net;
BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

void connectToWiFi(String init_str)
{
  if (init_str != emptyString)
    Serial.print(init_str);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (init_str != emptyString)
    Serial.println("ok!");
}

void setupWifi() {
  WiFi.hostname("EUGENIO " THINGNAME);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  connectToWiFi(String("Tentando conectar na rede wifi: ") + String(ssid));
}

void setupSSL() {
  net.setInsecure();
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
}
