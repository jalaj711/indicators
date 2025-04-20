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

void rsi_push_val(rsi_t *rsi, double open, double close);

static inline double rsi_get_val(rsi_t *rsi)
{
    return rsi->rsi;
}

#endif // INDICATORS_RSI_H