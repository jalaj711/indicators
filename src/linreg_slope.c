#include "linreg_slope.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

linreg_slope_t *linreg_slope_init(uint32_t periods)
{
    double *prices = (double *)malloc(periods * sizeof(double));
    memset(prices, 0, periods * sizeof(double));
    linreg_slope_t *linreg_slope = (linreg_slope_t *)malloc(sizeof(linreg_slope_t));
    linreg_slope->prices = prices;
    linreg_slope->prices_sum = 0;
    linreg_slope->prices_mul_time_sum = 0;
    linreg_slope->time_sum = 0;
    linreg_slope->time2_sum = 0;
    for (uint32_t i = 1; i <= periods; i++)
    {
        linreg_slope->time_sum += i;
        linreg_slope->time2_sum += i * i;
    }
    linreg_slope->index = 0;
    linreg_slope->periods = periods;
    linreg_slope->ready = 0;
    return linreg_slope;
}

uint8_t linreg_slope_push_val(linreg_slope_t *linreg_slope, double val)
{
    double *next = linreg_slope->prices + linreg_slope->index;
    if (*next != 0)
    {
        linreg_slope->prices_mul_time_sum -= linreg_slope->prices_sum;
        linreg_slope->prices_sum -= *next;
    }

    *next = val;
    linreg_slope->prices_sum += val;
    if (linreg_slope->ready)
        linreg_slope->prices_mul_time_sum += val * linreg_slope->periods;
    linreg_slope->index = (linreg_slope->index + 1) % linreg_slope->periods;

    if (!linreg_slope->ready && linreg_slope->index == 0)
    {
        for (uint32_t i = 0; i < linreg_slope->periods; i++)
        {
            linreg_slope->prices_mul_time_sum += (linreg_slope->prices[i]) * (i + 1);
        }
        return linreg_slope->ready = 1;
    }
    return 0;
}
