#include <WiFi.h>

class WifiService
{
public:
    const String ssid;
    const String password;

    WifiService(const String &ssid, const String &password)
        : ssid(ssid), password(password) {}

    bool ConnectWifi(unsigned long timeout_ms = 10000) // 默认超时10秒
    {
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
            if (millis() - startAttemptTime >= timeout_ms)
            {
                Serial.println("\n连接超时，WiFi连接失败！");
                return false; // 超时失败返回false
            }
            Serial.print(".");
            delay(500);
        }
        Serial.println("\nWiFi连接成功！");
        Serial.print("IP地址: ");
        Serial.println(WiFi.localIP());
        return true; // 连接成功返回true
    }
};
