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

void rsi_push_val(rsi_t *rsi, double open, double close)
{
    double change = (close - open) / open;
    double gain = 0.0, loss = 0.0;
    if (change > 0)
    {
        gain = change;
    }
    else
    {
        loss = -change;
    }

    if (!rsi->ready)
    {
        sma_push_val(rsi->gains, gain);
        sma_push_val(rsi->losses, loss);
        if (rsi->gains->ready & rsi->losses->ready)
        {
            rsi->avg_gain = sma_get_val(rsi->gains);
            rsi->avg_loss = sma_get_val(rsi->losses);
            free(rsi->gains);
            free(rsi->losses);
            rsi->ready = 1;
        }
        else
            return;
    }

    rsi->avg_gain = ((rsi->avg_gain * (rsi->periods - 1)) + gain) / rsi->periods;
    rsi->avg_loss = ((rsi->avg_loss * (rsi->periods - 1)) + loss) / rsi->periods;

    if (rsi->avg_loss == 0.0)
    {
        rsi->rsi = 100.0;
    }
    else
    {
        rsi->rsi = 100.0 - (100.0 / (1 + (rsi->avg_gain / rsi->avg_loss)));
    }
}
