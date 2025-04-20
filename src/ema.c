#include "ma.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

ema_t *ema_init(uint32_t periods)
{
    ema_t *ema = (ema_t *)malloc(sizeof(ema_t));
    ema->alpha = (double)2 / (periods + 1);
    ema->prev = 0;
    ema->curr = 0;
    ema->sma = sma_init(periods);
    ema->ready = 0;
    return ema;
}

// returns 1 only on the tick when ema is ready after that
// it will still return 0 even though ema is ready
uint8_t ema_push_val(ema_t *ema, double val)
{
    if (!ema->ready)
    {
        if (sma_push_val(ema->sma, val))
        {
            double sma = sma_get_val(ema->sma);
            // we don't need the sma anymore so clear it
            free(ema->sma);
            ema->sma = NULL;

            // initialise ema
            ema->ready = 1;
            ema->prev = sma;
            ema->curr = sma;
        }
        return ema->ready;
    }
    ema->prev = ema->curr;
    ema->curr = val * ema->alpha + ema->prev * (1 - ema->alpha);
    return 0;
}
