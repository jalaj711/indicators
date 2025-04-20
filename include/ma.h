#ifndef INDICATORS_MA_H
#define INDICATORS_MA_H
#include "stdint.h"

/*
 * Functions and structs for the Simple Moving Average
 */
struct sma_s
{
    double *values;
    double sum;
    uint32_t index;
    uint32_t periods;
    uint8_t ready;
};

typedef struct sma_s sma_t;

sma_t *sma_init(uint32_t periods);
uint8_t sma_push_val(sma_t *sma, double val);

static inline double sma_get_val(sma_t *sma)
{
    return sma->sum / sma->periods;
}

/*
 * Functions and structs for the Exponential Moving Average
 */
struct ema_s
{
    double alpha;
    double prev;
    double curr;
    sma_t *sma;
    uint8_t ready;
};

typedef struct ema_s ema_t;

ema_t *ema_init(uint32_t periods);
uint8_t ema_push_val(ema_t *ema, double val);

static inline double ema_get_val(ema_t *ema)
{
    return ema->curr;
}

#endif // INDICATORS_MA_H