#ifndef INDICATORS_ATR_H
#define INDICATORS_ATR_H
#include "ma.h"
#include "stdint.h"

#define DEFAULT_ATR_LOOKBACK_PERIOD 14

struct atr_s
{
    ema_t *ema;
    double prev_close;
    uint8_t ready;
};

typedef struct atr_s atr_t;

atr_t *atr_init(double loockback_periods);
void atr_push_val(atr_t *atr, double high, double low, double close);

static inline double atr_get_val(atr_t *atr)
{
    return ema_get_val(atr->ema);
}

#endif // INDICATORS_ATR_H