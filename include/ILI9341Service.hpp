#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class ILI9341Service
{
private:
  Adafruit_ILI9341 tft;

public:
  ILI9341Service(int cs, int dc, int rst);
  ~ILI9341Service();
  void Init();
};

// 使用初始化列表构造成员变量 tft
ILI9341Service::ILI9341Service(int cs, int dc, int rst)
  : tft(cs, dc, rst) {}

ILI9341Service::~ILI9341Service() {}

void ILI9341Service::Init()
{
  Serial.println("ILI9341 Init...");
  tft.begin();
}
