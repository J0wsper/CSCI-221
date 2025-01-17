#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "homework5.h"

/*

CONVERTING BASES

To convert 97 to binary, we can recognize:
97 = 64 + 33 (2^6)
33 = 32 + 1 (2^5)
1 = 1 + 0 (2^0)

Therefore, 97 = 0b1100001

To convert 0b1000110 to decimal, we recognize:

0b1000110 = 0(2^0) + 1(2^1) + 1(2^2) + 0(2^3) + 0(2^4) + 0(2^5) + 1(2^6)

Summing these all together, we get 2+4+64 = 70

To convert 0b0100101011001111 into hexadecimal, we break it up into 4-bit chunks:

0b0100101011001111 = 0100 1010 1100 1111

These in turn correspond to particular hexadecimal digits:

0100 = 4

1010 = a

1100 = c

1111 = f

Therefore, in total, our 0b0100101011001111 = 0x4acf

To convert 0x18d3 into binary, we can again split it up into 4-bit chunks:

0x1 = 0b0001

0x8 = 0b1000

0xd = 0b1101

0x3 = 0b0011

Therefore, in total, we have 0x18d3 = 0b0001100011010011

REPRESENTATION

The maximum value that can be represented by a 41-bit unsigned integer is 2^41 - 1.
Meanwhile, the minimum value that can be represented is 0.

The maximum value that can be represented using a 41-bit signed integer is 2^40 - 1.
The minimum value is (-1)(2^40).

The maximum value that can be represented using a 9-bit unsigned integer is 2^9 - 1.
The minimum value that can be represented is 0.

The maximum value that can be represented using a 9-bit signed integer is 2^8-1.
The minimum value that can be repsetened is (-1)(2^8)

*/


int main() {
    uint32_t result_upper = 0;
    uint32_t result_lower = 0;
    //(0x1,0x2): works
    //(0x2,0x2): works
    //(0x0,0x1): works
    //(0x0,0xFFFFFFFF): works
    //(0x2,0xFFFFFFFF): works
    //(0x10,0xFFFFFFFF): works
    //(0x10000000,0xFFFFFFFF): works
    //(0xFFFFFFFF,0xFFFFFFFF): works
    //(0xFFFFFFFF,0xFFFFFFFE): works
    //(0xCA,0xFFFFFFFF): works
    multiply_overflow(0xFFFFFFFF, 0xFFFFFFFF, &result_upper, &result_lower);
    printf("%x\n", result_upper);
    printf("%x\n", result_lower);
    return 0;
}