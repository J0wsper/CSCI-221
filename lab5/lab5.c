#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lab5.h"

//There's some bug with the implementation of this and how it interacts with make_mask. Check it.
uint32_t make_mask(uint32_t start, uint32_t end) {
    uint32_t mask = 0b0;
    int length = end-start;
    int index = 0;
    while (index < length) {
        double exponent = 31-start-index;
        uint32_t val = pow(2, exponent);
        mask += val;
        index++;
    }
    return mask;
}

uint32_t add_halves(uint32_t val) {
    return (val >> 16) + ((val << 16) >> 16);
}

void add_with_overflow(uint32_t x, uint32_t y, uint32_t* result_upper, uint32_t* result_lower) {
    *result_lower = x+y;
    *result_upper = 0;
    if (* result_lower < x || *result_lower < y) {
        *result_upper = 1;
    }
}

