#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#define TFT_CS    5
#define TFT_DC    4
#define TFT_RST   2

Adafruit_ILI9341 tft (TFT_CS,TFT_DC, TFT_RST);
void init() {
  Serial.println("ILI9341 Test!"); 
  tft.begin();
  tft.setRotation(3);
  Serial.print("Display Power Mode: 0x");
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
}

