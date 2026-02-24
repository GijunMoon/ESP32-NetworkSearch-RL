#ifndef NETWORK_MGR_H
#define NETWORK_MGR_H

#include <stdint.h>

int32_t NETWORK_Connect(const char * ssid);

float NETWORK_MeasureReward(int32_t * latency_out);

#endif /* NETWORK_MGR_H */