#include <ESP8266WiFi.h>
#include "wifi_credentials.h"

void wifi_connect() {
  WiFi.persistent(true);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("WiFi connecting...");

  while (!WiFi.isConnected()) {
    delay(100);
    Serial.print(".");
  }

  Serial.printf("\nWiFi connected, IP: %s\n", WiFi.localIP().toString().c_str());
}
