#include "macd.h"
#include "ma.h"
#include "stdlib.h"

inline macd_t *macd_init(double signal_periods, double fast_ema_periods, double slow_ema_periods)
{
    macd_t *macd = (macd_t *)malloc(sizeof(macd_t));
    macd->histogram = 0;
    macd->macd = 0;
    macd->signal = ema_init(signal_periods);
    macd->first = ema_init(fast_ema_periods);
    macd->second = ema_init(slow_ema_periods);
    macd->ready = 0;
    macd->ema_ready = 0;

    return macd;
}

inline void macd_push_val(macd_t *macd, double val)
{
    ema_push_val(macd->first, val);
    ema_push_val(macd->second, val);

    if (!macd->ema_ready)
    {
        macd->ema_ready = macd->first->ready & macd->second->ready;
        return;
    }

    macd->macd = ema_get_val(macd->first) - ema_get_val(macd->second);
    ema_push_val(macd->signal, macd->macd);
    macd->histogram = macd->macd - ema_get_val(macd->signal);

    if (!macd->ready)
        macd->ready = (macd->signal->ready);
}
