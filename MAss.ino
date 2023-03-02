#include <WiFiManager.h>
#include <EEPROM.h>
#include <NTPClient.h>
#include <Adafruit_MAX31865.h>
#include "WebPage.h"
#include "State.h"

// MiFi Manager
#define AC_SSID "MAss WiFI Setup"
#define AC_PASS "11111111"

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0
#define THERNO_CLK  D4
#define THERMO_SDO  D3
#define THERMO_SDI  D2
#define THERMO_CS   D1


WebPage page;
State state;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
Adafruit_MAX31865 thermo = Adafruit_MAX31865(THERMO_CS, THERMO_SDI, THERMO_SDO, THERNO_CLK);

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

  Serial.println("Starting time client...");
  timeClient.begin();
  Serial.println("Starting MAX31865 client...");
  thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary

  page.setup();
  page.graphData = graphData;
}

unsigned long timeClientLastUpdate;
unsigned long timeClientUpdateInterval = 5000;

void loop() {
  // put your main code here, to run repeatedly:
  page.update();

  unsigned long currentMillis = millis();
  unsigned long duration = currentMillis - timeClientLastUpdate;
  
  if (duration < timeClientUpdateInterval) return;
  timeClientLastUpdate = currentMillis;
  timeClient.update();
  
  readTempAndTimestamp();
}

String graphData() {
  String data = state.toString();
  Serial.println("Data = " + data);
  return data;
}

void readTempAndTimestamp() {
  uint16_t rtd = thermo.readRTD();
  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  float temp = thermo.temperature(RNOMINAL, RREF);
  
//  unsigned short temp = random(22, 82);
  Serial.print("Temperature = "); Serial.println(temp);

  unsigned long ts = timeClient.getEpochTime();

  Serial.print("Timestamp = "); Serial.println(ts);
  
  state.addTemp(temp, ts);
}
