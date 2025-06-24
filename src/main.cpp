#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char* ssid = "ouse"; // 替换为你的 WiFi 名称
const char* password = "80231314w"; // 替换为你的 WiFi 密码

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000); // 等待串口初始化

  // 初始化 LittleFS
  Serial.println("Mounting LittleFS...");
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS Mount Failed!");
    return;
  }
  Serial.println("LittleFS Mounted Successfully");

  // 列出文件（调试用）
  Serial.println("Listing files:");
  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.printf("File: %s, Size: %lu bytes\n", file.name(), file.size());
    file = root.openNextFile();
  }
  root.close();

  // 连接 WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Still connecting...");
  }
  Serial.println("Connected to WiFi, IP: " + WiFi.localIP().toString());

  // 配置静态文件服务
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  // 添加动态路由（示例）
  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"status\":\"ok\"}");
  });

  // 处理 404
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });

  // 启动服务器
  server.begin();
  Serial.println("Web server started");
}

void loop() {}