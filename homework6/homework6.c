#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "homework6.h"

uint8_t sig_mask(uint8_t x) {
    return 0b111 & x;
}

uint8_t get_bit(uint8_t x, int index) {
    x = x >> index;
    x = x & 0b1;
    return x;
}

uint8_t exp_mask(uint8_t x) {
    return (0b01111000 & x) >> 3;
}

uint8_t sign_mask(uint8_t x) {
    return (0b10000000 & x) >> 7;
}

uint8_t add_quarter(uint8_t x, uint8_t y) {
    uint8_t x_exp = exp_mask(x);
    uint8_t y_exp = exp_mask(y);
    uint8_t x_sig = sig_mask(x);
    uint8_t y_sig = sig_mask(y);
    uint8_t x_sign = sign_mask(x);
    uint8_t y_sign = sign_mask(y);
    uint8_t* sign;
    uint8_t* greater_exp;
    uint8_t* greater_sig;
    uint8_t* lesser_sig;
    uint8_t* lesser_exp;

    //Check the exponents, see which one is larger
    //Shift the lesser over by the difference between their exponents
    //Add them together
    //Add the exponents if necessary
    if (x_exp < y_exp) {
        sign = &y_sign;
        greater_exp = &y_exp;
        greater_sig = &y_sig;
        lesser_exp = &x_exp;
        lesser_sig = &x_sig;
    }
    else {
        sign = &x_sign;
        greater_exp = &x_exp;
        greater_sig = &x_sig;
        lesser_exp = &y_exp;
        lesser_sig = &y_sig;
    }

    //Adding the implicit leading 1
    *greater_sig = 0b1000 | *greater_sig;
    *lesser_sig = 0b1000 | *lesser_sig;

    //Shifting over lesser_sig so that it is effectively "correctly-aligned"
    uint8_t exp_offset = *greater_exp - *lesser_exp;
    
    //Shift the greater one left
    *lesser_sig = *lesser_sig >> exp_offset;
    uint8_t sig_total = 0;
    uint8_t exp_total = *greater_exp;

    //If the signs differ, it is subtraction; otherwise, it is addition
    uint8_t total;
    if (x_sign == y_sign) {
        sig_total = *lesser_sig + *greater_sig;
        if (sig_total >= 0b10000) {
            exp_total++;
            sig_total = sig_total >> 1;
            sig_total = sig_mask(sig_total);
        }
        total = (*sign << 7) + (exp_total << 3) + sig_total;
        return total;
    }
    else {
        sig_total = *greater_sig - *lesser_sig;
        if (sig_total == 0) {
            return 0;
        }
        int i = 4;
        while (i >= 0) {
            if (get_bit(sig_total,i) == 1) {
                break;
            }
            i--;
        }
        sig_total = sig_total << (3-i);
        sig_total = sig_mask(sig_total);
    }
    return (*sign << 7) + (exp_total << 3) + sig_total;
}

uint8_t multiply_quarter(uint8_t x, uint8_t y) {
    uint8_t x_sig = sig_mask(x);
    uint8_t y_sig = sig_mask(y);
    uint8_t x_exp = exp_mask(x);
    uint8_t y_exp = exp_mask(y);
    uint8_t x_sign = sign_mask(x);
    uint8_t y_sign = sign_mask(y);
    uint8_t result_sign = 0;
    uint8_t result_exp = 0;
    uint8_t result_sig = 0;

    //Calculates the sign of the result
    if (x_sign  == y_sign) {
        result_sign = 0;
    }
    else {
        result_sign = 1;
    }
    
    //Finds their 'true' exponent factoring in bias
    int temp_exp;
    int x_exp_offset = x_exp - 7;
    int y_exp_offset = y_exp - 7;
    temp_exp = 7 + x_exp_offset + y_exp_offset;

    //Subnormal number
    if (temp_exp < 0) {
        result_exp = 0;
    }

    //Special number
    else if (temp_exp >= 0b1111) {
        result_exp = 0b1111;
        return (result_sign << 7) + (result_exp << 3);
    }

    //Normal number
    else {
        result_exp += temp_exp;
    }

    //Adding the implicit leading 1; gotta remove it later
    x_sig = 0b1000 | x_sig;
    y_sig = 0b1000 | y_sig;

    //To get the significand, multiply them together and pass it to temp_sig
    //From there, shift temp_sig over so it is back to 4 bits and add to the exponent as necessary
    //Then, remove the implicit leading 1
    uint8_t temp_sig = x_sig * y_sig;
    temp_sig = temp_sig >> 3;
    if (temp_sig > 0b10000) {
        temp_sig = temp_sig >> 1;
        if (temp_exp >= 0) {
            result_exp++;
        }
    }
    temp_sig = temp_sig & 0b111;
    result_sig = temp_sig;


    return (result_sign << 7) + (result_exp << 3) + (result_sig);
}