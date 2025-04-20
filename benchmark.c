#include "ma.h"
#include "macd.h"
#include "rsi.h"
#include "stochastic.h"
#include "williams_r.h"
#include "mfi.h"
#include "bollinger.h"
#include "atr.h"
#include "supertrend.h"
#include "keltner.h"
#include "cci.h"
#include "obv.h"
#include "linreg_slope.h"
#include "time.h"
#include "string.h"

#define MAX_LINE_LENGTH 1024
#define OPEN_IDX 1
#define HIGH_IDX 2
#define LOW_IDX 3
#define CLOSE_IDX 4
#define VOLUME_IDX 5
#define OPENTIME_IDX 0
#define CLOSETIME_IDX 6

#define DATA_FILE "backtest_data.csv"

typedef struct kline_s
{
    char *sym;
    double o;
    double c;
    double h;
    double l;
    double v;
    uint64_t open_time;
    uint64_t close_time;
} kline_t;

sma_t *ma50 = NULL;
ema_t *ema50 = NULL;
macd_t *macd = NULL;
rsi_t *rsi = NULL;
stochastic_t *stoch = NULL;
williams_r_t *williams = NULL;
mfi_t *mfi = NULL;
bollinger_t *bollinger = NULL;
atr_t *atr = NULL;
supertrend_t *supertrend = NULL;
keltner_t *keltner = NULL;
cci_t *cci = NULL;
linreg_slope_t *linreg_slope = NULL;
obv_t *obv = NULL;

uint64_t count = 0;
uint64_t ticks = 0;

int read_klines_from_file(char *data_file, void (*push_val)(kline_t *))
{
    FILE *fp = fopen(data_file, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    kline_t kline;
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ",");
        int token_idx = 0;
        char *end;
        while (token != NULL)
        {
            if (token_idx == OPEN_IDX)
            {
                kline.o = strtod(token, &end);
            }
            else if (token_idx == CLOSE_IDX)
            {
                kline.c = strtod(token, &end);
            }
            else if (token_idx == HIGH_IDX)
            {
                kline.h = strtod(token, &end);
            }
            else if (token_idx == LOW_IDX)
            {
                kline.l = strtod(token, &end);
            }
            else if (token_idx == VOLUME_IDX)
            {
                kline.v = strtod(token, &end);
            }
            else if (token_idx == OPENTIME_IDX)
            {
                kline.open_time = strtoull(token, &end, 10);
            }
            else if (token_idx == CLOSETIME_IDX)
            {
                kline.close_time = strtoull(token, &end, 10);
            }

            token = strtok(NULL, ",");

            token_idx++;
        }
        push_val(&kline);
        count++;
    }

    fclose(fp);
    return count;
}

void klines_on_data(kline_t *kline)
{
    clock_t t1 = clock();
    double avg = (kline->o + kline->c) / 2;

    sma_push_val(ma50, avg);
    ema_push_val(ema50, avg);
    macd_push_val(macd, avg);
    rsi_push_val(rsi, kline->o, kline->c);
    stochastic_push_val(stoch, kline->c);
    williams_r_push_val(williams, kline->c);
    mfi_push_val(mfi, kline->h, kline->l, kline->c, kline->v);
    bollinger_push_val(bollinger, avg);
    atr_push_val(atr, kline->h, kline->l, kline->c);
    supertrend_push_val(supertrend, kline->h, kline->l, kline->c);
    keltner_push_val(keltner, kline->h, kline->l, kline->c);
    cci_push_val(cci, kline->h, kline->l, kline->c);
    linreg_slope_push_val(linreg_slope, kline->c);
    obv_push_val(obv, kline->o, kline->c, kline->v);

    double _ma50 = sma_get_val(ma50);
    double _ema50 = ema_get_val(ema50);
    double _macd = macd_get_macd(macd);
    double _signal = macd_get_signal(macd);
    double _histogram = macd_get_histogram(macd);
    double _rsi = rsi_get_val(rsi);
    double _k = stochastic_get_k(stoch);
    double _d = stochastic_get_d(stoch);
    double _williams_r = williams_r_get_r(williams);
    double _mfi = mfi_get_val(mfi);
    double _bollinger_l = bollinger_get_lower(bollinger);
    double _bollinger_h = bollinger_get_upper(bollinger);
    double _atr = atr_get_val(atr);
    double _supertrend = supertrend_get_val(supertrend);
    double _trend = supertrend_get_trend(supertrend);
    double _keltner_lower = keltner_get_lower(keltner);
    double _keltner_middle = keltner_get_middle(keltner);
    double _keltner_upper = keltner_get_upper(keltner);
    double _cci = cci_get_val(cci);
    double _linreg_slope = linreg_slope_get_val(linreg_slope);
    double _obv = obv_get_val(obv);

    clock_t t2 = clock();
    // printf("Time taken: Total: %fs\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
    // printf("Symbol: %s\n", kline->sym);
    // printf("Start Time: %ld End Time: %ld\n", kline->open_time, kline->close_time);
    // printf("O: %.10f H: %.10f L: %.10f C: %.10f V: %.10f\n", kline->o, kline->h, kline->l, kline->c, kline->v);
    // printf("SMA:   50: %.10f\n", _ma50);
    // printf("EMA:   50: %.10f\n", _ema50);
    // printf("MACD:  M: %.10f S: %.10f  H: %.10f\n", _macd, _signal, _histogram);
    // printf("RSI:   V: %.10f R: %d\n", _rsi, rsi->ready);
    // printf("STOCH: K: %.10f D: %.10f R: %d\n", _k, _d, stoch->ready);
    // printf("WILIM: R: %.10f R: %d\n", _williams_r, williams->ready);
    // printf("MFI:   R: %.10f\n", _mfi);
    // printf("BOLING:U: %.10f L: %.10f R: %d\n", _bollinger_h, _bollinger_l, bollinger->ready);
    // printf("ATR:   V: %.10f R: %d\n", _atr, atr->ready);
    // printf("SUPERT:V: %.10f T: %f R: %d\n", _supertrend, _trend, supertrend->ready);
    // printf("KELT:  L: %.10f M: %.10f U: %.10f R: %d\n", _keltner_lower, _keltner_middle, _keltner_upper, keltner->ready);
    // printf("CCI:   V: %.10f R: %d\n", _cci, cci->ready);
    // printf("LR_SLP:V: %.15f R: %d\n\n", _linreg_slope, linreg_slope->ready);
    // printf("OBV:   V: %.15f R: %d\n\n", _obv, obv->ready);
    count++;
    ticks += t2 - t1;
}

int main()
{
    ma50 = sma_init(50);
    ema50 = ema_init(50);
    macd = macd_init(DEFAULT_MACD_SIGNAL_PERIODS, DEFAULT_MACD_FIRST_EMA_PERIODS, DEFAULT_MACD_SECOND_EMA_PERIODS);
    rsi = rsi_init(DEFAULT_RSI_PERIODS);
    stoch = stochastic_init(DEFAULT_STOCHASTIC_LOOKBACK_PERIOD, DEFAULT_STOCHASTIC_MOD_D_PERIODS);
    williams = williams_r_init(DEFAULT_WILLIAMS_R_LOOKBACK_PERIOD);
    mfi = mfi_init(DEFAULT_MFI_LOOKBACK_PERIOD);
    bollinger = bollinger_init(DEFAULT_BOLLINGER_LOOKBACK_PERIODS, DEFAULT_BOLLINGER_MULTIPLIER);
    atr = atr_init(DEFAULT_ATR_LOOKBACK_PERIOD);
    supertrend = supertrend_init(DEFAULT_SUPERTREND_LOOKBACK, DEFAULT_SUPERTREND_MULTTIPLER);
    keltner = keltner_init(DEFAULT_KELTNER_EMA_PERIOD, DEFAULT_KELTNER_ATR_PERIOD, DEFAULT_KELTNER_MULTIPLIER);
    cci = cci_init(DEFAULT_CCI_SMA_PERIOD);
    linreg_slope = linreg_slope_init(DEFAULT_LINEAR_REG_SLOPE_PERIODS);
    obv = obv_init();

    read_klines_from_file(DATA_FILE, klines_on_data);

    printf("Total data points: %ld.\nTotal time taken: %fs.\nAverage time per iteration: %fs\n", count, (double)ticks / CLOCKS_PER_SEC, (double)ticks / CLOCKS_PER_SEC / count);

    return 0;
}
