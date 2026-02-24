#ifndef WIFI_SCAN_H
#define WIFI_SCAN_H

#include <stdint.h>
#include "rl_ucb.h"

uint32_t WIFI_Scan(ap_stat_t * ap_list, uint32_t max_count);

#endif /* WIFI_SCAN_H */