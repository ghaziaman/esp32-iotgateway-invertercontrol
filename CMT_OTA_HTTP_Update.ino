
#include <Arduino.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

#define USE_SERIAL Serial2

WiFiClient OTAclient;

void OTA_update(String OTA_link){

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
        USE_SERIAL.print("Updating the firmware using link:  ");
        USE_SERIAL.print(OTA_link);
        t_httpUpdate_return ret = ESPhttpUpdate.update(OTA_link);
        switch(ret) {
            case HTTP_UPDATE_FAILED:
                USE_SERIAL.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                break;

            case HTTP_UPDATE_NO_UPDATES:
                USE_SERIAL.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                USE_SERIAL.println("HTTP_UPDATE_OK");
                break;
  }
}
