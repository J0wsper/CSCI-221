#ifndef _LAB6_H_
#define _LAB6_H_

typedef enum encoding {
    normal,
    subnormal,
    special
} encoding;

encoding encoding_type(uint8_t);

uint8_t round_to_even(uint8_t, int);

#endif