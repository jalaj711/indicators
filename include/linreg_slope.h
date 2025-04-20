#ifndef INDICATORS_LINEAR_REG_SLOPE_H
#define INDICATORS_LINEAR_REG_SLOPE_H
#include "stdint.h"

#define DEFAULT_LINEAR_REG_SLOPE_PERIODS 14

struct linreg_slope_s
{
    double *prices;
    double prices_sum;
    double prices_mul_time_sum;
    uint32_t time_sum;
    uint32_t time2_sum;
    uint32_t index;
    uint32_t periods;
    uint8_t ready;
};

typedef struct linreg_slope_s linreg_slope_t;

linreg_slope_t *linreg_slope_init(uint32_t periods);
uint8_t linreg_slope_push_val(linreg_slope_t *linreg_slope, double val);

static inline double linreg_slope_get_val(linreg_slope_t *linreg_slope)
{
    return (linreg_slope->periods * linreg_slope->prices_mul_time_sum - linreg_slope->time_sum * linreg_slope->prices_sum) / (linreg_slope->periods * linreg_slope->time2_sum - linreg_slope->time_sum * linreg_slope->time_sum);
}

#endif