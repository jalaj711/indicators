#ifndef INDICATORS_STOCHASTIC_H
#define INDICATORS_STOCHASTIC_H

#include "ma.h"
#include "utils/rw_minmax.h"
#include "stdint.h"

#define DEFAULT_STOCHASTIC_LOOKBACK_PERIOD 14
#define DEFAULT_STOCHASTIC_MOD_D_PERIODS 3

struct stochastic_s
{
    double k;
    double val_count;
    sma_t *mod_d;
    rw_minmax_t *rw;
    uint32_t lookback_periods;
    uint8_t ready;
};

typedef struct stochastic_s stochastic_t;

stochastic_t *stochastic_init(uint32_t lookback_periods, uint32_t mod_d_periods);
void stochastic_push_val(stochastic_t *stoch, double close);

inline double stochastic_get_k(stochastic_t *stoch)
{
    return stoch->k;
}

inline double stochastic_get_d(stochastic_t *stoch)
{
    return sma_get_val(stoch->mod_d);
}

#endif