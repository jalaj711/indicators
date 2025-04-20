#ifndef INDICATORS_CCI_H
#define INDICATORS_CCI_H

#include "ma.h"
#include "stdint.h"

#define DEFAULT_CCI_SMA_PERIOD 20

struct cci_s
{
    sma_t *sma;
    sma_t *mad;
    double cci;
    uint8_t ready;
};

typedef struct cci_s cci_t;

cci_t *cci_init(uint32_t sma_periods);
void cci_push_val(cci_t *cci, double high, double low, double close);

static inline double cci_get_val(cci_t *cci)
{
    return cci->cci;
}

#endif