#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

class HttpServerService {
private:
    AsyncWebServer server;

public:
    HttpServerService(const int port=80)
        : server(port) {}

    bool init() {
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
        }
        Serial.println();
        Serial.println("WiFi connected, IP: " + WiFi.localIP().toString());
    }

    void start(std::function<void(AsyncWebServer&)> setupRoutes) {
        server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html").setCacheControl("max-age=86400");

        if (setupRoutes) {
            setupRoutes(server);
        }

        server.onNotFound([](AsyncWebServerRequest* req) {
            req->send(404, "text/plain", "Not found");
        });

        server.begin();
        Serial.println("Web server started.");
    }
};
