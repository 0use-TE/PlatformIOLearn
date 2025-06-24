#include "ApService.hpp"
#include "HttpServerService.hpp"
#include "DynamicRoutesService.hpp"

const char* ap_ssid = "OuseAP";
const char* ap_password = "12345678";

ApService apService(ap_ssid, ap_password);
HttpServerService httpServer("", ""); 
DynamicRoutesService apiService;

void setup() {
    Serial.begin(115200);
    delay(1000);

    if (!apService.begin()) {
        Serial.println("AP启动失败，停止程序");
        while(true) delay(1000);
    }

    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS挂载失败");
        while(true) delay(1000);
    }

    httpServer.start([&](AsyncWebServer& server){
        apiService.registerRoutes(server);
    });
}

void loop() {
}
