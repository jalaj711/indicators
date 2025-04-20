#include "atr.h"
#include "ma.h"
#include "stdlib.h"
#include "math.h"

atr_t *atr_init(double lookback_periods)
{
    atr_t *atr = (atr_t *)malloc(sizeof(atr_t));
    atr->ema = ema_init(lookback_periods);
    atr->prev_close = -1;
    atr->ready = 0;
    return atr;
}

void atr_push_val(atr_t *atr, double high, double low, double close)
{
    double tr = high - low;
    if (atr->prev_close != -1)
    {
        tr = fmax(tr, fabs(high - atr->prev_close));
        tr = fmax(tr, fabs(low - atr->prev_close));
    }
    ema_push_val(atr->ema, tr);
    atr->prev_close = close;

    if (!atr->ready)
    {
        atr->ready = atr->ema->ready;
        return;
    }
}