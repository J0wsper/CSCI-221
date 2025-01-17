#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "lab6.h"

encoding encoding_type(uint8_t val) {
    uint8_t shifted = val >> 4;
    if (shifted == 0) {
        return subnormal;
    }
    else if (shifted == 0b1111) {
        return special;
    }
    else {
        return normal;
    }
}

//This all assumes that 0 <= round <= 3 or else it doesn't make much sense
uint8_t round_to_even(uint8_t val, int round) {
    int breakpoint;
    if (round <= 0) {
        breakpoint = 1;
    }
    else {
        breakpoint = 0b1 << round;
    }
    uint8_t sig_mask = 0b11111111 << round;
    uint8_t round_mask = 0b11111111 << round;
    uint8_t sig = sig_mask & val;
    //Round up
    if (sig > breakpoint) {
        //Deal with the exponent
        if ((sig_mask & val) == sig_mask) {
            val += 0b1000;
            val = val & (0b11111111-sig_mask);
        }
        else {
            val = (val & round_mask) + (0b1 << round);
        }
    }
    //Round down
    else if (sig < breakpoint) {
        val = val & round_mask;
    }
    //Tie-breaking heuristic
    else {
        //If it is an odd number, round up
        if (((val >> (8-round)) & 1) == 1) {
            //Deal with the exponent
            if ((sig_mask & val) == sig_mask) {
                val += 0b1000;
                val = val & (0b11111111-sig_mask);
            }
            else {
                val += 0b1 << (round+1);
            }
            
        }
        //If it is an even number, round down 
        else {
            val = val & round_mask;
        }
    }
    return val;
}