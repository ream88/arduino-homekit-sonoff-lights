#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void accessory_identify(homekit_value_t _value) {}

// Used in sketch.ino
homekit_characteristic_t characteristic_switch_on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t characteristic_name = HOMEKIT_CHARACTERISTIC_(NAME, "Switch");

homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(
      .id = 1,
      .category = homekit_accessory_category_switch,
      .services = (homekit_service_t *[]){
        HOMEKIT_SERVICE(
          ACCESSORY_INFORMATION,
          .characteristics = (homekit_characteristic_t *[]){
            HOMEKIT_CHARACTERISTIC(NAME, "Switch"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Arduino HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, accessory_identify),
            NULL }),
        HOMEKIT_SERVICE(SWITCH, .primary = true, .characteristics = (homekit_characteristic_t *[]){ &characteristic_switch_on, &characteristic_name, NULL }), NULL }),
  NULL
};

homekit_server_config_t config = {
  .accessories = accessories,
  .password = "111-11-111"
};