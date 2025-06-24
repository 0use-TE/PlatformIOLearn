#pragma once

#include <ESPAsyncWebServer.h>

class DynamicRoutesService {
public:
    void registerRoutes(AsyncWebServer& server) {
        server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest* req) {
            req->send(200, "application/json", "{\"status\":\"ok\"}");
        });

        server.on("/api/hello", HTTP_GET, [](AsyncWebServerRequest* req) {
            req->send(200, "text/plain", "Hello from DynamicRoutesService");
        });
    }
};
