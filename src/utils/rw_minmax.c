#include "utils/rw_minmax.h"
#include "utils/deque.h"
#include "stdlib.h"
#include "stdint.h"

rw_minmax_t* rw_minmax_init(uint32_t size) {
    rw_minmax_t *rw = (rw_minmax_t*) malloc(sizeof(rw_minmax_t));
    rw->buffer = (double*) malloc(size * sizeof(double));
    rw->max_deque = deque_init(size);
    rw->min_deque = deque_init(size);
    rw->window_size = size;
    rw->count = 0;
    return rw;
}

void rw_minmax_push_val(rw_minmax_t *rw, double value) {    
    if (rw->count != 0) {
        while(!deque_is_empty(rw->min_deque) && deque_peek_rear(rw->min_deque) > value) {
            deque_pop_rear(rw->min_deque);
        }

        while(!deque_is_empty(rw->max_deque) && deque_peek_rear(rw->max_deque) < value) {
            deque_pop_rear(rw->max_deque);
        }
    }

    uint32_t pos = rw->count % rw->window_size;

    if (rw->count >= rw->window_size) {
        if (!deque_is_empty(rw->min_deque) && deque_peek_front(rw->min_deque) == rw->buffer[pos]) {
            deque_pop_front(rw->min_deque);
        }
        if (!deque_is_empty(rw->max_deque) && deque_peek_front(rw->max_deque) == rw->buffer[pos]) {
            deque_pop_front(rw->max_deque);
        }
    }

    rw->buffer[pos] = value;
    deque_push_rear(rw->max_deque, value);
    deque_push_rear(rw->min_deque, value);
    rw->count++;
}

void rw_minmax_free(rw_minmax_t *rw) {
    if (rw) {
        free(rw->buffer);
        deque_free(rw->min_deque);
        deque_free(rw->max_deque);
        free(rw);
    }
}