#include "cci.h"
#include "ma.h"
#include "stdlib.h"
#include "stdint.h"
#include "math.h"

cci_t *cci_init(uint32_t sma_periods)
{
    cci_t *cci = (cci_t *)malloc(sizeof(cci_t));
    cci->sma = sma_init(sma_periods);
    cci->mad = sma_init(sma_periods);
    cci->cci = 0;
    cci->ready = 0;
    return cci;
}

void cci_push_val(cci_t *cci, double high, double low, double close)
{
    double tp = (high + low + close) / 3;
    sma_push_val(cci->sma, tp);
    if (!cci->ready)
    {
        if (!cci->sma->ready)
            return;
        sma_push_val(cci->mad, fabs(tp - sma_get_val(cci->sma)));
        cci->ready = cci->mad->ready;
        return;
    }
    double sma = sma_get_val(cci->sma);
    sma_push_val(cci->mad, fabs(tp - sma));
    cci->cci = (tp - sma) / (0.015 * sma_get_val(cci->mad));
    return;
}
