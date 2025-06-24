#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

class HttpServerService {
private:
    AsyncWebServer server;
    const char* ssid;
    const char* password;

public:
    HttpServerService(const char* ssid, const char* password)
        : server(80), ssid(ssid), password(password) {}

    void init() {

        Serial.println("Mounting LittleFS...");
        if (!LittleFS.begin(true)) {
            Serial.println("LittleFS Mount Failed!");
            return;
        }
        listFiles();

        Serial.printf("Connecting to WiFi: %s\n", ssid);
        WiFi.begin(ssid, password);
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

private:
    void listFiles() {
        Serial.println("Listing files:");
        File root = LittleFS.open("/");
        if (!root) {
            Serial.println("Failed to open root directory!");
            return;
        }
        File file = root.openNextFile();
        while (file) {
            Serial.printf("File: %s, Size: %lu bytes\n", file.name(), file.size());
            file = root.openNextFile();
        }
        root.close();
    }
};
