#ifndef UTILS_DEQUE_H
#define UTILS_DEQUE_H

#include "stdint.h"
#include "stdio.h"

struct deque_s
{
    double *buffer;
    uint32_t front;
    uint32_t back;
    uint32_t size;
    uint32_t cap;
};

typedef struct deque_s deque_t;

deque_t *deque_init(uint32_t size);
void deque_push_front(deque_t *deque, double data);
void deque_push_rear(deque_t *deque, double data);
double deque_pop_front(deque_t *deque);
double deque_pop_rear(deque_t *deque);
void deque_free(deque_t *deque);

static inline double deque_peek_front(deque_t *deque)
{
    return deque->buffer[deque->front];
}

static inline double deque_peek_rear(deque_t *deque)
{
    return deque->buffer[deque->back];
}
static inline uint8_t deque_is_empty(deque_t *deque)
{
    return deque->size == 0;
}

static inline uint8_t deque_is_full(deque_t *deque)
{
    return deque->size == deque->cap;
}

#endif // UTILS_DEQUE_H