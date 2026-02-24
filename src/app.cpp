#include <Arduino.h>
#include <WiFi.h>
#include "app.h"
#include "wifi_scan.h"
#include "network_mgr.h"
#include "rl_ucb.h"
#include "config.h"

static ap_stat_t g_ap_list[MAX_AP_COUNT];
static uint32_t  g_ap_count = 0U;
static uint32_t  g_last_switch_time = 0U;
static int32_t   g_current_index = -1;
int32_t latency;
float reward;

static void log_learning(uint32_t timestamp,
                         const char * ssid,
                         int32_t index,
                         int32_t latency,
                         float reward,
                         float avg_reward,
                         uint32_t select_count)
{
    Serial.print(timestamp);
    Serial.print(",");

    Serial.print(ssid);
    Serial.print(",");

    Serial.print(index);
    Serial.print(",");

    Serial.print(latency);
    Serial.print(",");

    Serial.print(reward, 3);
    Serial.print(",");

    Serial.print(avg_reward, 3);
    Serial.print(",");

    Serial.println(select_count);
}

void APP_Init(void)
{
    RL_UCB_Init(g_ap_list, MAX_AP_COUNT);
}

void APP_Run(void)
{
    int32_t selected_index;
    float reward_local;
    uint32_t now;

    g_ap_count = WIFI_Scan(g_ap_list, MAX_AP_COUNT);

    if (g_ap_count == 0U)
    {
        return;
    }

    selected_index = RL_UCB_Select(g_ap_list,
                                   g_ap_count);

    now = millis();

    /* Policy: 최소 유지 시간 */
    if ((g_current_index >= 0) &&
        ((now - g_last_switch_time) < MIN_STAY_TIME_MS))
    {
        selected_index = g_current_index;
    }

    if (selected_index >= 0)
    {
        if (selected_index != g_current_index)
        {
            WiFi.begin(g_ap_list[selected_index].ssid, "pw");
            g_last_switch_time = now;
            g_current_index = selected_index;
        }

        reward_local = NETWORK_MeasureReward(&latency);
        if(g_ap_list[selected_index].select_count < MIN_EXPLORE_COUNT)
        {
            reward_local += EXPLORATION_BONUS;
        }

        // Handover Penalty
        bool is_handover = (selected_index != g_current_index);

        if (is_handover)
        {
            reward_local -= HANDOVER_PENALTY;
        }

        RL_UCB_Update(&g_ap_list[selected_index],
                      reward);

        /* 로그 출력 */
        log_learning(millis(),
             g_ap_list[selected_index].ssid,
             selected_index,
             latency,
             reward_local,
             g_ap_list[selected_index].avg_reward,
             g_ap_list[selected_index].select_count);
    }
}