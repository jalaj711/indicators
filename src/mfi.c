#include "mfi.h"
#include "stdlib.h"

mfi_t *mfi_init(uint32_t lookback_periods)
{
    mfi_t *mfi = (mfi_t *)malloc(sizeof(mfi_t));
    mfi->tp_buffer = (double *)malloc(sizeof(double) * lookback_periods);
    for (uint32_t i = 0; i < lookback_periods; i++)
    {
        mfi->tp_buffer[i] = 0;
    }
    mfi->positive_sum = 0;
    mfi->negative_sum = 0;
    mfi->prev_tp = 0;
    mfi->buffer_ptr = 0;
    mfi->lookback_periods = lookback_periods;

    return mfi;
}

void mfi_push_val(mfi_t *mfi, double high, double low, double close, double volume)
{
    double tp = (high + low + close) / 3;
    if (mfi->tp_buffer[mfi->buffer_ptr] > 0)
    {
        mfi->positive_sum -= mfi->tp_buffer[mfi->buffer_ptr];
    }
    else
    {
        mfi->negative_sum += mfi->tp_buffer[mfi->buffer_ptr];
    }

    double rmf = tp * volume;
    if (tp == mfi->prev_tp)
    {
        mfi->tp_buffer[mfi->buffer_ptr] = 0;
    }
    else if (tp > mfi->prev_tp)
    {
        mfi->positive_sum += rmf;
        mfi->tp_buffer[mfi->buffer_ptr] = rmf;
    }
    else
    {
        mfi->negative_sum += rmf;
        mfi->tp_buffer[mfi->buffer_ptr] = -rmf;
    }
    mfi->prev_tp = tp;
    mfi->buffer_ptr = (mfi->buffer_ptr + 1) % (mfi->lookback_periods);
}
