#include "Arduino.h"
class   LEDService
{
private:
    const uint8_t led = 17;
public:
    LEDService(/* args */){

    };
    ~LEDService(){

    };
    void init()
    {
        pinMode(led, OUTPUT);
    };
    void flash()
    {
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
    }
};
