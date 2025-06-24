#include <WiFi.h> 

class WifiService {
public:
    const String ssid;
    const String password;

    WifiService(const String& ssid, const String& password)
        : ssid(ssid), password(password) {}

    void ConnectWifi() {
        Serial.println(ssid);

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        Serial.print("连接到 WiFi: ");
        }

        Serial.println("\nWiFi连接成功！");
        Serial.print("IP地址: ");
        Serial.println(WiFi.localIP());
    }
};
