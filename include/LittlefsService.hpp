#pragma once
#include <Arduino.h>
#include <LittleFS.h>
class LittlefsService
{
private:
    /* data */
public:
    LittlefsService(/* args */);
    ~LittlefsService();
    bool init()
    {
        // 初始化 LittleFS
        Serial.println("Mounting LittleFS...");
        auto result=LittleFS.begin(true);
        if(result)
        {
            Serial.println("LittleFS Mount Failed!");
        }
        else
        { 
            // true 表示如果未格式化则自动格式化
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
    };
};

LittlefsService::LittlefsService()
{
}

LittlefsService::~LittlefsService()
{
}
