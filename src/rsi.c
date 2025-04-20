#include "rsi.h"
#include "stdlib.h"

rsi_t *rsi_init(uint32_t periods)
{
    rsi_t *rsi = (rsi_t *)malloc(sizeof(rsi_t));
    rsi->gains = sma_init(periods);
    rsi->losses = sma_init(periods);
    rsi->avg_gain = 0;
    rsi->avg_loss = 0;
    rsi->rsi = 0;
    rsi->ready = 0;
    rsi->periods = periods;

    return rsi;
}
