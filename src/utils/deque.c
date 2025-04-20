#include "utils/deque.h"
#include "stdlib.h"
#include "stdint.h"

deque_t* deque_init(uint32_t size) {
    deque_t* deque = (deque_t*)malloc(sizeof(deque_t));
    deque->buffer = (double*)malloc(size*sizeof(double));
    deque->back = -1;
    deque->front = 0;
    deque->size = 0;
    deque->cap = size;

    return deque;
}

void deque_push_front(deque_t* deque, double data) {
    deque->front = (deque->front - 1 + deque->cap) % deque->cap;
    deque->buffer[deque->front] = data;
    deque->size++;
}


void deque_push_rear(deque_t* deque, double data) {
    deque->back = (deque->back + 1) % deque->cap;
    deque->buffer[deque->back] = data;
    deque->size++;
}


double deque_pop_front(deque_t* deque) {
    double data = deque->buffer[deque->front];
    deque->front = (deque->front + 1) % deque->cap;
    deque->size--;
    return data;
}

double deque_pop_rear(deque_t* deque) {
    double data = deque->buffer[deque->back];
    deque->back = (deque->back - 1 + deque->cap) % deque->cap;
    deque->size--;
    return data;
}

void deque_free(deque_t* deque) {
    free(deque->buffer);
    free(deque);
}
