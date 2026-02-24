#include <WiFi.h>
#include "wifi_scan.h"

uint32_t WIFI_Scan(ap_stat_t * ap_list,
                   uint32_t max_count)
{
    int n;
    uint32_t count = 0U;

    n = WiFi.scanNetworks();

    for (int i = 0; (i < n) && (count < max_count); i++)
    {
        strncpy(ap_list[count].ssid,
                WiFi.SSID(i).c_str(),
                32);

        ap_list[count].ssid[32] = '\0';

        count++;
    }

    return count;
}