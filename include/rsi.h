#ifndef INDICATORS_RSI_H
#define INDICATORS_RSI_H
#include "ma.h"
#include "stdlib.h"
#define DEFAULT_RSI_PERIODS 14

struct rsi_s
{
    sma_t *gains;
    sma_t *losses;
    double avg_gain;
    double avg_loss;
    double rsi;
    uint32_t periods;
    uint8_t ready;
};

typedef struct rsi_s rsi_t;

rsi_t *rsi_init(uint32_t periods);

inline void rsi_push_val(rsi_t *rsi, double open, double close)
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

inline double rsi_get_val(rsi_t *rsi)
{
    return rsi->rsi;
}

#endif // INDICATORS_RSI_H