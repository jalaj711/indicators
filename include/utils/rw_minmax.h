#ifndef UTILS_RW_MIN_MAX_H
#define UTILS_RW_MIN_MAX_H

#include "stdint.h"
#include "utils/deque.h"

struct rw_minmax_s
{
    double *buffer;
    deque_t *max_deque;
    deque_t *min_deque;
    uint32_t window_size;
    uint32_t count;
};

typedef struct rw_minmax_s rw_minmax_t;

rw_minmax_t *rw_minmax_init(uint32_t size);
void rw_minmax_push_val(rw_minmax_t *rw, double value);
void rw_minmax_free(rw_minmax_t *rw);

static inline double rw_minmax_get_max(rw_minmax_t *rw)
{
    return deque_peek_front(rw->max_deque);
}

static inline double rw_minmax_get_min(rw_minmax_t *rw)
{
    return deque_peek_front(rw->min_deque);
}

#endif // UTILS_RW_MIN_MAX_H