#include "stochastic.h"
#include "stdlib.h"
#include "ma.h"
#include "utils/rw_minmax.h"

stochastic_t *stochastic_init(uint32_t lookback_periods, uint32_t mod_d_periods)
{
    stochastic_t *stochastic = (stochastic_t *)malloc(sizeof(stochastic_t));
    stochastic->mod_d = sma_init(mod_d_periods);
    stochastic->rw = rw_minmax_init(lookback_periods);
    stochastic->k = 0;
    stochastic->val_count = 0;
    stochastic->ready = 0;
    stochastic->lookback_periods = lookback_periods;

    return stochastic;
}

void stochastic_push_val(stochastic_t *stoch, double close)
{
    rw_minmax_push_val(stoch->rw, close);

    if (!stoch->ready)
    {
        if (++stoch->val_count < stoch->lookback_periods)
        {
            return;
        }

        double low = rw_minmax_get_min(stoch->rw);
        double high = rw_minmax_get_max(stoch->rw);
        stoch->k = high == low ? 50.0 : ((close - low) / (high - low) * 100);
        sma_push_val(stoch->mod_d, stoch->k);
        stoch->ready = stoch->mod_d->ready;
        return;
    }

    double low = rw_minmax_get_min(stoch->rw);
    double high = rw_minmax_get_max(stoch->rw);
    stoch->k = high == low ? 50.0 : ((close - low) / (high - low) * 100);
    sma_push_val(stoch->mod_d, stoch->k);
}
