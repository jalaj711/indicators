#include "ma.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

sma_t *sma_init(uint32_t periods)
{
    double *values = (double *)malloc(periods * sizeof(double));
    memset(values, 0, periods * sizeof(double));
    sma_t *sma = (sma_t *)malloc(sizeof(sma_t));
    sma->values = values;
    sma->index = 0;
    sma->sum = 0;
    sma->periods = periods;
    sma->ready = 0;
    return sma;
}

uint8_t sma_push_val(sma_t *sma, double val)
{
    double *next = sma->values + sma->index;
    if (*next != 0)
        sma->sum -= *next;
    *next = val;
    sma->sum += val;
    sma->index = (sma->index + 1) % sma->periods;
    if (!sma->ready && sma->index == 0)
        return sma->ready = 1;
    return 0;
}
