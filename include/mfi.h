#ifndef INDICATORS_MFI_H
#define INDICATORS_MFI_H
#include "stdint.h"
#define DEFAULT_MFI_LOOKBACK_PERIOD 14

struct mfi_s {
    double prev_tp;
    double positive_sum;
    double negative_sum;
    double *tp_buffer;
    uint32_t lookback_periods;
    uint32_t buffer_ptr;
};

typedef struct mfi_s mfi_t;

mfi_t *mfi_init(uint32_t lookback_periods);
void mfi_push_val(mfi_t *mfi, double high, double low, double close, double volume);

static double mfi_get_val(mfi_t *mfi)
{
    if (mfi->negative_sum == 0)
        return 100;

    return 100 - (100 / (1 + (mfi->positive_sum / mfi->negative_sum)));
}


#endif