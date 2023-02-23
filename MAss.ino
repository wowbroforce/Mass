#include <WiFiManager.h>
#include <EEPROM.h>
#include "WebPage.h"
#include "State.h"

// MiFi Manager
#define AC_SSID "MAss WiFI Setup"
#define AC_PASS "11111111"

WebPage page;

void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);
  Serial.println();
  delay(1000);
    
  Serial.println("Starting WiFi manager to auto connect...");
  WiFiManager wifiManager;
  wifiManager.setDebugOutput(false);
  wifiManager.autoConnect(AC_SSID, AC_PASS);
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  page.setup();
}

void loop() {
  // put your main code here, to run repeatedly:

  page.update();
}
