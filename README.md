# ESP32 Samsung Galaxy Watch BLE Spoofer
Dieses Projekt demonstriert, wie ein **ESP32 Bluetooth Low Energy (BLE)** nutzt, um sich als eine **Samsung Galaxy Pair Watch** auszugeben. Das Besondere an diesem Code ist die dynamische Änderung der **MAC-Adresse** und des Gerätenamens in kurzen Intervallen.

# 🚀 Funktionen
**Dynamisches MAC-Spoofing:** Generiert bei jedem Durchlauf eine neue, gültige Random-Static **MAC-Adresse**.

**Gerätenamen-Variation:** Erstellt zufällige Namen **(z. B. Galaxy Watch 442)**.

**Samsung Ecosystem Simulation:** Verwendet spezifische Manufacturer Data **(Samsung ID 0x0075)**, um von anderen Geräten als Samsung-Zubehör erkannt zu werden.

**Continuous Advertising:** Startet das **BLE-Advertising** nach jeder Identitätsänderung automatisch neu.

# 🛠 Hardware & Software Anforderungen
**ESP32 Development Board (z.B. ESP32-WROOM-32, ESP32-S3, etc.)**

**Micro-USB** oder **USB-C Kabel**

# Software / Bibliotheken
**Arduino IDE (oder PlatformIO)**

# ESP32 Arduino Core

**Standard-Bibliotheken** (im Core enthalten):

**BLEDevice.h**
**esp_bt_main.h**
**esp_mac.h**

# 💻 Funktionsweise des Codes
Der Kern des Projekts liegt in der Funktion **updateIdentity():**

**Deinitialisierung:** Der aktuelle **BLE-Stack** wird gestoppt.

**MAC-Generierung:** Eine neue MAC-Adresse wird über den Hardware-Zufallsgenerator **(esp_random())** erzeugt.

**Bit-Manipulation:** Das erste Byte wird angepasst **((newMac[0] & 0xFE) | 0x02)**, um die Adresse als **"Locally Administered"** zu kennzeichnen.

**Advertising:** Das Gerät sendet ein Paket mit dem **Samsung-spezifischen Payload** aus.

# 📝 Installation
Klone das Repository oder kopiere den Code in einen neuen **Arduino-Sketch**.

Stelle sicher, dass in der **Arduino IDE** das richtige **ESP32 Board** ausgewählt ist.

Wähle den passenden **ESP Port** aus.

Klicke auf **Upload**.

Öffne den **Seriellen Monitor (115200 Baud)**, um die **Identitätswechsel** live zu verfolgen.

# ⚠️ Rechtlicher Hinweis & Disclaimer
Dieses Projekt dient ausschließlich Bildungszwecken und der Erforschung von **BLE-Protokollen**.

Das massenhafte Aussenden von **Werbepaketen (Advertising)** kann die Funktion anderer **Bluetooth-Geräte** in der Umgebung beeinträchtigen.

Bitte beachte die lokalen Gesetze zur **Funkkommunikation**.

**Der Ersteller übernimmt keine Haftung für Missbrauch oder Schäden!**

# 📄 Lizenz
Dieses Projekt ist unter der **MIT-Lizenz** lizenziert.
