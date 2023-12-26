#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi.h"

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t characteristic_switch_on;

#define PIN_BUTTON 0
#define PIN_RELAY 12
#define PIN_LED 13

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_LED, HIGH);

  Serial.begin(115200);
  wifi_connect();

  // Reset HomeKit when onboard button is pressed during boot.
  if (digitalRead(PIN_BUTTON) == LOW) {
    homekit_storage_reset();
  }

  characteristic_switch_on.setter = characteristic_switch_on_setter;
  arduino_homekit_setup(&config);
}

void loop() {
  arduino_homekit_loop();
  delay(10);
}

void characteristic_switch_on_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  characteristic_switch_on.value.bool_value = on;

  digitalWrite(PIN_RELAY, on ? HIGH : LOW);
  digitalWrite(PIN_LED, on ? LOW : HIGH);
}
