#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "ChartWebPage.h"
#include "SettingsWebPage.h"

typedef String (*ChartDataRequest) (void);

struct WebServer {
//  ESP8266WebServer server = ESP8266WebServer(80);
  ESP8266WebServer server = {80};
  uint32_t currentTime = millis();
  uint32_t previousTime = 0; 
  ChartDataRequest onChartDataRequest;

  WebServer();

  void setup();
  void update();

  void getChart();
  void getChartData();
  void getSettings();
};


WebServer::WebServer() {
};

void WebServer::getChart() {
  server.send_P(200, "text/html", chartWebPage);
};

void WebServer::getChartData() {
  String data = onChartDataRequest();
  server.send(200, "text/html", data);
};

void WebServer::getSettings() {
  server.send_P(200, "text/html", settingsWebPage);
};

void WebServer::setup() {
  if (MDNS.begin("mass.server")) {
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
  
  server.on("/chart", HTTP_GET, [=](){ this->getChart(); });
  server.on("/chart/data", HTTP_GET, [=](){ this->getChartData(); });
  server.on("/settings", HTTP_GET, [=](){ this->getSettings(); });
  server.begin();
};

void WebServer::update() {
  server.handleClient();
  MDNS.update();
};

#endif
