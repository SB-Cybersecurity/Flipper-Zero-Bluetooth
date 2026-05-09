#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEAdvertising.h>
#include <esp_bt_main.h>
#include <esp_bt_device.h>
#include "esp_mac.h"

void updateIdentity() {
    BLEDevice::deinit(true);

    uint8_t newMac[6];
    uint32_t rng = esp_random();
    memcpy(newMac, &rng, 4);
    rng = esp_random();
    memcpy(newMac + 4, &rng, 2);
    newMac[0] = (newMac[0] & 0xFE) | 0x02; 
    
    esp_base_mac_addr_set(newMac);

    String watchName = "Galaxy Watch " + String(random(100, 999));
    BLEDevice::init(watchName.c_str());
    
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    oAdvertisementData.setFlags(0x06); 

    uint8_t samsung_payload[] = {
      0x75, 0x00, 
      0x01, 0x00, 0x02, 0x00, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x43, 0x03, 0x01, 0x04
    };

    String dataString = "";
    for (int i = 0; i < sizeof(samsung_payload); i++) {
        dataString += (char)samsung_payload[i];
    }
    oAdvertisementData.setManufacturerData(dataString);
    
    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->setMinInterval(0x30); 
    pAdvertising->setMaxInterval(0x30);
    
    pAdvertising->start();
    
    Serial.printf("Identität gewechselt! Name: %s | MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", 
                  watchName.c_str(), newMac[0], newMac[1], newMac[2], newMac[3], newMac[4], newMac[5]);
}

void setup() {
    Serial.begin(115200);
    updateIdentity();
}

void loop() {
    delay(800);
    updateIdentity();
}
