#include "bollinger.h"
#include "ma.h"
#include "stdlib.h"
#include "math.h"

bollinger_t *bollinger_init(double lookback_periods, double multiplier)
{
    bollinger_t *bollinger = (bollinger_t *)malloc(sizeof(bollinger_t));

    bollinger->price = sma_init(lookback_periods);
    bollinger->price_sq = sma_init(lookback_periods);
    bollinger->multiplier = multiplier;
    bollinger->std = 0;
    bollinger->ready = 0;

    return bollinger;
}

void bollinger_push_val(bollinger_t *bollinger, double price)
{
    sma_push_val(bollinger->price, price);
    sma_push_val(bollinger->price_sq, price * price);

    if (!bollinger->ready)
    {
        bollinger->ready = bollinger->price->ready;
        return;
    }

    double price_mean = sma_get_val(bollinger->price);
    bollinger->std = sqrt(sma_get_val(bollinger->price_sq) - price_mean * price_mean);
}
