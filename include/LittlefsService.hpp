#include <Arduino.h>
#include <LittleFS.h>
class LittlefsService
{
private:
    /* data */
public:
    LittlefsService(/* args */);
    ~LittlefsService();
void setup() {
  Serial.begin(115200);
  delay(1000); // 等待串口初始化

  // 初始化 LittleFS
  Serial.println("Mounting LittleFS...");
  if (!LittleFS.begin(true)) { // true 表示如果未格式化则自动格式化
    Serial.println("LittleFS Mount Failed!");
    return;
  }
  // 挂载成功
  Serial.println("LittleFS Mounted Successfully!");

  // 检查文件系统空间
  size_t totalBytes = LittleFS.totalBytes();
  size_t usedBytes = LittleFS.usedBytes();
  Serial.printf("Total space: %lu bytes\n", totalBytes);
  Serial.printf("Used space: %lu bytes\n", usedBytes);
  Serial.printf("Free space: %lu bytes\n", totalBytes - usedBytes);

  // 列出文件
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

void loop() {}

};

LittlefsService::LittlefsService(/* args */)
{
}

LittlefsService::~LittlefsService()
{
}

