#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "lab5.h"

/*

CONVERTING BASES


Add the fucking calculations


209 = 0b11010001
0b10110001 = 177
0b1001101 = 0x4d
0x5a6d = 0b0101101001101101

*/

int main() {

    //(0,0): works
    //(0,32): works
    //(31,32): works
    //(30,32): works
    //(32,32): works
    //(26,32): works
    //(25,32): works
    uint32_t test = make_mask(25, 32);
    uint32_t val = 0x00010001;

    //0xFFFFFFF: works
    //0x0000000: works
    //0x00010001: works
    uint32_t test2 = add_halves(val);
    uint32_t sum1 = 0x80000000;
    uint32_t sum2 = 0x80000001;
    uint32_t upper;
    uint32_t lower;

    //(0xFFFFFFFF,0xFFFFFFFF): works
    //(0x00000000,0x00000000): works
    //(0x80000000,0x80000000): works
    //(0x80000000,0x80000001): works
    add_with_overflow(sum1, sum2, &upper, &lower);
    printf("%u\n", test);
    printf("%u\n", test2);
    printf("%u\n", upper);
    printf("%u\n", lower);
    return 0;
}