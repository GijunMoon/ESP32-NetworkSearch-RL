#include <Arduino.h>
#include "app.h"

void setup(void)
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("timestamp,ssid,index,latency,reward,avg_reward,select_count");

    APP_Init();
}

void loop(void)
{
    APP_Run();

    static uint32_t last = 0;

    if (millis() - last > 5000)
    {
        last = millis();
        APP_Run();
    }
}