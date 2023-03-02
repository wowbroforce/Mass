#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "WebPageContent.h"

typedef String (*GraphData) (void);

struct WebPage {
//  ESP8266WebServer server = ESP8266WebServer(80);
  ESP8266WebServer server = {80};
  unsigned long currentTime = millis();
  unsigned long previousTime = 0; 
  const long timeoutTime = 2000;
  String header;
  GraphData graphData;

  WebPage();

  void setup();
  void update();
  void root();
  void test();
  void data();
};


WebPage::WebPage() {
};

void WebPage::root() {
//  String s = ;
  server.send_P(200, "text/html", webpage);
};

void WebPage::test() {
  server.send(200, "application/json", "{'message': 'success'}");
};

void WebPage::data() {
  String data = graphData();
  server.send(200, "text/html", data);
}

void WebPage::setup() {
  if (MDNS.begin("mashass")) {
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
  
  server.on("/chart", HTTP_GET, [=](){ this->root(); });
  server.on("/test", HTTP_GET, [=](){ this->test(); });
  server.on("/chart/data", HTTP_GET, [=](){ this->data(); });
  server.begin();
};

void WebPage::update() {
  server.handleClient();
  MDNS.update();
};

#endif
