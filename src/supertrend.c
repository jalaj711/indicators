#include "supertrend.h"
#include "atr.h"
#include "stdlib.h"

supertrend_t *supertrend_init(uint32_t lookback_periods, double multiplier)
{
    supertrend_t *supertrend = (supertrend_t *)malloc(sizeof(supertrend_t));
    supertrend->atr = atr_init(lookback_periods);
    supertrend->supertrend = 0;
    supertrend->prev_close = 0;
    supertrend->prev_upper = 0;
    supertrend->prev_lower = 0;
    supertrend->trend = SUPERTREND_UNDEFINED;
    supertrend->ready = 0;
    supertrend->multiplier = multiplier;
    return supertrend;
}

void supertrend_push_val(supertrend_t *supertrend, double high, double low, double close)
{

    if (!supertrend->ready)
    {
        supertrend->prev_close = close;
        atr_push_val(supertrend->atr, high, low, close);
        if (supertrend->atr->ready)
        {
            double mid = (high + low) / 2;
            double atr = atr_get_val(supertrend->atr);
            double upper = mid + supertrend->multiplier * atr;
            double lower = mid - supertrend->multiplier * atr;
            if (close > upper)
            {
                supertrend->trend = SUPERTREND_UP;
                supertrend->supertrend = lower;
            }
            else
            {
                supertrend->trend = SUPERTREND_DOWN;
                supertrend->supertrend = upper;
            }
            supertrend->ready = 1;
            return;
        }
        if (!supertrend->ready)
            return;
    }

    double mid = (high + low) / 2;
    double atr = atr_get_val(supertrend->atr);
    double upper = mid + supertrend->multiplier * atr;
    double lower = mid - supertrend->multiplier * atr;

    double new_upper = upper < supertrend->prev_upper ||
                               supertrend->prev_close > supertrend->prev_upper
                           ? upper
                           : supertrend->prev_upper;
    double new_lower = lower > supertrend->prev_lower ||
                               supertrend->prev_close < supertrend->prev_lower
                           ? lower
                           : supertrend->prev_lower;

    if (supertrend->trend == SUPERTREND_DOWN)
        supertrend->trend = close > new_upper ? SUPERTREND_UP : SUPERTREND_DOWN;
    else
        supertrend->trend = close < new_lower ? SUPERTREND_DOWN : SUPERTREND_UP;
    supertrend->supertrend = supertrend->trend == SUPERTREND_UP ? new_lower : new_upper;

    supertrend->prev_close = close;
    supertrend->prev_lower = new_lower;
    supertrend->prev_upper = new_upper;
    atr_push_val(supertrend->atr, high, low, close);
}
