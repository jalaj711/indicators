#ifndef INDICATORS_OBV_H
#define INDICATORS_OBV_H
#include "stdint.h"

struct obv_s
{
    double value;
    uint8_t ready;
};

typedef struct obv_s obv_t;

obv_t *obv_init();
uint8_t obv_push_val(obv_t *obv, double open, double close, double volume);

static inline double obv_get_val(obv_t *obv)
{
    return obv->value;
}

#endif