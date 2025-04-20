#ifndef INDICATORS_MACD_H
#define INDICATORS_MACD_H
#include "ma.h"

#define DEFAULT_MACD_FIRST_EMA_PERIODS 12
#define DEFAULT_MACD_SECOND_EMA_PERIODS 26
#define DEFAULT_MACD_SIGNAL_PERIODS 9

struct macd_s
{
    double macd;
    double histogram;
    ema_t *signal;
    ema_t *first;
    ema_t *second;
    uint8_t ready;
    uint8_t ema_ready;
};

typedef struct macd_s macd_t;

macd_t *macd_init(double signal_periods, double fast_ema_periods, double slow_ema_periods);
void macd_push_val(macd_t *macd, double val);

/**
 * Inline functions
 */
static inline double macd_get_macd(macd_t *macd)
{
    return macd->macd;
}

static inline double macd_get_signal(macd_t *macd)
{
    return ema_get_val(macd->signal);
}

static inline double macd_get_histogram(macd_t *macd)
{
    return macd->histogram;
}

#endif // INDICATORS_MACD_H