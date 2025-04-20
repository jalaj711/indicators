#ifndef INDICATORS_WILLIAMS_R_H
#define INDICATORS_WILLIAMS_R_H

#include "utils/rw_minmax.h"
#include "stdint.h"

#define DEFAULT_WILLIAMS_R_LOOKBACK_PERIOD 14

struct williams_r_s {
    double k;
    double val_count;
    rw_minmax_t *rw;
    uint32_t lookback_periods;
    uint8_t ready;
};

typedef struct williams_r_s williams_r_t;



williams_r_t *williams_r_init(uint32_t lookback_periods);
void williams_r_push_val(williams_r_t *stoch, double close);

inline double williams_r_get_r(williams_r_t *stoch)
{
    return stoch->k;
}


#endif