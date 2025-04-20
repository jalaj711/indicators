#include "williams_r.h"
#include "stdlib.h"
#include "utils/rw_minmax.h"

williams_r_t *williams_r_init(uint32_t lookback_periods)
{
    williams_r_t *williams_r = (williams_r_t *)malloc(sizeof(williams_r_t));
    williams_r->rw = rw_minmax_init(lookback_periods);
    williams_r->k = 0;
    williams_r->val_count = 0;
    williams_r->ready = 0;
    williams_r->lookback_periods = lookback_periods;

    return williams_r;
}

void williams_r_push_val(williams_r_t *stoch, double close)
{
    rw_minmax_push_val(stoch->rw, close);

    if (!stoch->ready)
    {
        if (++stoch->val_count < stoch->lookback_periods)
        {
            return;
        }
        stoch->ready = 1;
        return;
    }

    double low = rw_minmax_get_min(stoch->rw);
    double high = rw_minmax_get_max(stoch->rw);

    stoch->k = high == low ? -50.0 : ((high - close) / (high - low) * -100);
}
