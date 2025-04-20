#include "keltner.h"
#include "ma.h"
#include "atr.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

keltner_t *keltner_init(uint32_t ema_periods, uint32_t atr_periods, double multiplier)
{
    keltner_t *keltner = (keltner_t *)malloc(sizeof(keltner_t));
    keltner->ema = ema_init(ema_periods);
    keltner->atr = atr_init(atr_periods);
    keltner->multiplier = multiplier;
    keltner->ready = 0;
    return keltner;
}

void keltner_push_val(keltner_t *keltner, double high, double low, double close)
{
    ema_push_val(keltner->ema, close);
    atr_push_val(keltner->atr, high, low, close);
    if (!keltner->ready)
    {
        keltner->ready = keltner->ema->ready & keltner->atr->ready;
        return;
    }
    return;
}
