#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h> 
#include "homework5.h"


int32_t negation(int32_t val) {
    uint32_t mask = 0xFFFFFFFF;
    int32_t inv = (mask^(val))-1;
    return inv;
}

uint32_t conditional(uint32_t x, uint32_t y, uint32_t z) {
    int32_t is_zero = (x == 0);
    return z*is_zero + y*!is_zero;
}

void add_with_overflow(uint32_t x, uint32_t y, uint32_t* result_upper, uint32_t* result_lower) {
    *result_lower = x+y;
    if (*result_lower < x || *result_lower < y) {
        *result_upper = 1;
    }
    else {
        *result_upper = 0;
    }
}

void multiply_overflow(uint32_t x, uint32_t y, uint32_t* result_upper, uint32_t* result_lower) {
    *result_lower = (x*y);
    if (x != 0 && *result_lower/x != y) {
        *result_lower = 0;
        uint32_t* greater;
        uint32_t* lesser;
        if (x < y) {
            greater = &y;
            lesser = &x;
        }
        else {
            greater = &x;
            lesser = &y;
        }
        uint32_t index = 0;
        while (index < 32) {
            uint32_t mask = make_mask(31-index,32-index);
            uint32_t desired_bit = mask & *lesser;
            if (desired_bit != 0) {
                int shift = log2(desired_bit);
                uint32_t upper_shift;
                uint32_t lower_shift;
                shift_overflow(*greater,shift,&upper_shift,&lower_shift);
                *result_upper += upper_shift;
                uint32_t carry = 0;
                add_with_overflow(lower_shift,*result_lower,&carry,result_lower);
                *result_upper += carry;
            }
            index++;
        }
    }
}

void shift_overflow(uint32_t x, int shift, uint32_t* result_upper, uint32_t* result_lower) {
    uint32_t shift_mask = make_mask(0,shift);
    uint32_t lower_shifted = x << shift;
    *result_lower = lower_shifted;
    uint32_t upper_shifted = (shift_mask & x) >> 32-shift;
    *result_upper = upper_shifted;
}

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
