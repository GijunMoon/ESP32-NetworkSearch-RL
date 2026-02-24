#include <WiFi.h>
#include "network_mgr.h"

static int32_t measure_latency_ms(void)
{
    WiFiClient client;
    uint32_t start_time;
    uint32_t elapsed;

    start_time = millis();

    if (WiFi.status() != WL_CONNECTED)
    {
        return -1000;
    }

    elapsed = millis() - start_time;

    client.stop();

    return (int32_t)elapsed;
}

float NETWORK_MeasureReward(int32_t * latency_out)
{
    int32_t latency = measure_latency_ms();

    if (latency_out != NULL)
    {
        *latency_out = latency;
    }

    /* 실패 처리 */
    if (latency < 0)
    {
        return -1000.0f;
    }

    return (float)(1.0f / (1.0f + latency));
}