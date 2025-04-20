#ifndef INDICATORS_BOLLINGER_H
#define INDICATORS_BOLLINGER_H
#include "ma.h"
#include "stdint.h"

#define DEFAULT_BOLLINGER_MULTIPLIER 2
#define DEFAULT_BOLLINGER_LOOKBACK_PERIODS 20

struct bollinger_s
{
    sma_t *price;
    sma_t *price_sq;
    double std;
    double multiplier;
    uint8_t ready;
};

typedef struct bollinger_s bollinger_t;

bollinger_t *bollinger_init(double lookback_periods, double multiplier);
void bollinger_push_val(bollinger_t *bollinger, double price);

inline double bollinger_get_lower(bollinger_t *bollinger)
{
    return sma_get_val(bollinger->price) - bollinger->std * bollinger->multiplier;
}
inline double bollinger_get_upper(bollinger_t *bollinger)
{
    return sma_get_val(bollinger->price) + bollinger->std * bollinger->multiplier;
}

#endif // INDICATORS_BOLLINGER_H