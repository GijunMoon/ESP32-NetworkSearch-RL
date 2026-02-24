#include "rl_ucb.h"

#define EMA_ALPHA   (0.2f)
#define EXPLORATION (1.0f) // 탐색 시간

void RL_UCB_Init(ap_stat_t * ap_list, uint32_t max_count)
{
    uint32_t i;

    for (i = 0U; i < max_count; i++)
    {
        ap_list[i].avg_reward  = 0.0f;
        ap_list[i].select_count = 0U;
    }
}

int32_t RL_UCB_Select(ap_stat_t * ap_list,
                      uint32_t ap_count)
{
    uint32_t i;
    float best_score = -1000000.0f;
    int32_t best_index = -1;

    for (i = 0U; i < ap_count; i++)
    {
        float score;

        if (ap_list[i].select_count == 0U)
        {
            return (int32_t)i; /* explore first */
        }

        score = ap_list[i].avg_reward + // 점수 측정
                (EXPLORATION /
                 (float)ap_list[i].select_count);

        if (score > best_score)
        {
            best_score = score;
            best_index = (int32_t)i;
        }
    }

    return best_index;
}

void RL_UCB_Update(ap_stat_t * ap,
                   float reward)
{
    ap->select_count++;

    ap->avg_reward = // 보상 함수
        ap->avg_reward +
        (EMA_ALPHA * (reward - ap->avg_reward));
}