#ifndef WEB_H
#define WEB_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <credentials.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

#include "webHome.h"

void handleServerRequests() {
  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
  // Add service to MDNS-SD
  //MDNS.addService("http", "tcp", 80);
}

#endif
