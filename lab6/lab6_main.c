#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "lab6.h"

/*
CONVERSION:

10111010 is negative because its sign bit is 1.

Then, the next 4 bits are exponent, hence the exponent is 0111. This is equivalent to 5. Then, accounting
for the bias, we get 5-7 = -2 is the exponent.

Finally, the significand is 1.010 = 1.25. Therefore, we have in total (-1)(1.25)(2^(-2)) = -0.3125

To represent 3.25 as a quarter-precision floating point, we recognize that the sign bit is going to be
0.

Then, for the significand, we recognize:
3.25 = 2^(1) + 1.25
1.25 = 2^(0) + 0.25
0.25 = 2^(-2)
Therefore, we have that this is 11.01 = 1.101*2^(1). Chopping off the leading 1, we get that the significand
is 101 and the exponent is 0001. Therefore, in total, we have:

3.25 = 0b00001101
*/

int main() {
    uint8_t val = 0b0001110;
    //0b1110, 0: breaks, outputs f
    //0b1111, 2: works.
    //0b1110, 2: works.
    //0b10100, 2: works.
    //0b10111, 1: works.
    //0b10101, 1: works.
    //0b10011, 2: works
    uint8_t mod_val = round_to_even(val, 0);
    printf("%x", mod_val);
    return 0;
}