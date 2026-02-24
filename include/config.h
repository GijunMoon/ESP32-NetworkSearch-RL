#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#define MAX_AP_COUNT            (10U)
#define MAX_SSID_LENGTH         (32U)
#define UCB_EXPLORATION_COEFF   (1.0F)
#define MIN_EXPLORE_COUNT       (5U)
#define EXPLORATION_BONUS       (0.5f)
#define MIN_CONNECTION_TIME_S   (60U)
#define MIN_STAY_TIME_MS    (60000U)
#define HANDOVER_PENALTY    (20.0f)

#endif /* CONFIG_H */