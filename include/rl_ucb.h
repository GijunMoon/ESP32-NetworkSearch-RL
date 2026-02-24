#ifndef RL_UCB_H
#define RL_UCB_H

#include <stdint.h>

typedef struct
{
    char     ssid[33];
    float    avg_reward;
    uint32_t select_count;
} ap_stat_t;

void RL_UCB_Init(ap_stat_t * ap_list, uint32_t max_count);

int32_t RL_UCB_Select(ap_stat_t * ap_list,
                      uint32_t ap_count);

void RL_UCB_Update(ap_stat_t * ap,
                   float reward);

#endif