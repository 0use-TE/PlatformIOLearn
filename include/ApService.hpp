#pragma once

#include <Arduino.h>
#include <WiFi.h>

class ApService {
private:
    const String ssid;
    const String password;
    IPAddress localIP = IPAddress(192, 168, 4, 1); // ESP32 默认AP IP

public:
    ApService(const String ssid, const String password)
        : ssid(ssid), password(password) {}

    bool begin() {
        Serial.printf("Starting WiFi AP: %s\n", ssid);
        bool res = WiFi.softAP(ssid, password);
        if (!res) {
            Serial.println("Failed to start AP!");
            return false;
        }
        Serial.print("AP started, IP address: ");
        Serial.println(WiFi.softAPIP().toString());
        return true;
    }

    IPAddress getIP() const {
        return WiFi.softAPIP();
    }

    void stop() {
        WiFi.softAPdisconnect(true);
        Serial.println("AP stopped.");
    }
};
