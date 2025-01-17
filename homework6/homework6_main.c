#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "homework6.h"

int main() {
    uint8_t test1 = 0b1001111;
    uint8_t test2 = 0b1010011;
    //ADD_QUARTER WORKS!!!! YIPPEE!!!
    uint8_t result1 = add_quarter(test1,test2);
    //IT LIVES
    uint8_t result2 = multiply_quarter(test1,test2);
    printf("%x\n", result1);
    printf("%x\n", result2);
    return 0;
}