#ifndef INDICATORS_KELTNER_H
#define INDICATORS_KELTNER_H

#include "ma.h"
#include "atr.h"
#include "stdint.h"

#define DEFAULT_KELTNER_EMA_PERIOD 20
#define DEFAULT_KELTNER_ATR_PERIOD 10
#define DEFAULT_KELTNER_MULTIPLIER 2

struct keltner_s
{
    ema_t *ema;
    atr_t *atr;
    double multiplier;
    uint8_t ready;
};

typedef struct keltner_s keltner_t;

keltner_t *keltner_init(uint32_t ema_periods, uint32_t atr_periods, double multiplier);
void keltner_push_val(keltner_t *keltner, double high, double low, double close);

static inline double keltner_get_middle(keltner_t *keltner)
{
    return ema_get_val(keltner->ema);
}

static inline double keltner_get_upper(keltner_t *keltner)
{
    return ema_get_val(keltner->ema) + keltner->multiplier * atr_get_val(keltner->atr);
}

static inline double keltner_get_lower(keltner_t *keltner)
{
    return ema_get_val(keltner->ema) - keltner->multiplier * atr_get_val(keltner->atr);
}

#endif