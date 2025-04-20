#ifndef INDICATORS_SUPERTREND_H
#define INDICATORS_SUPERTREND_H

#include "atr.h"
#include "stdint.h"

#define DEFAULT_SUPERTREND_MULTTIPLER 3
#define DEFAULT_SUPERTREND_LOOKBACK 14

enum SUPERTREND
{
    SUPERTREND_UP,
    SUPERTREND_DOWN,
    SUPERTREND_UNDEFINED
};

struct supertrend_s
{
    atr_t *atr;
    enum SUPERTREND trend;
    double prev_upper;
    double prev_lower;
    double prev_close;
    double supertrend;
    double multiplier;
    uint8_t ready;
};

typedef struct supertrend_s supertrend_t;

supertrend_t *supertrend_init(uint32_t lookback_periods, double multiplier);
void supertrend_push_val(supertrend_t *supertrend, double high, double low, double close);

static double supertrend_get_val(supertrend_t *supertrend)
{
    return supertrend->supertrend;
}

static enum SUPERTREND supertrend_get_trend(supertrend_t *supertrend)
{
    return supertrend->trend;
}

#endif // INDICATORS_SUPERTREND_H