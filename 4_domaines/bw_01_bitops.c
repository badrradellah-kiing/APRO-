/* test domaine bitwise : raisonnement sur bits individuels */

#include "helpers.h"

int main(void) {
    unsigned int x = (unsigned)nondet_int(0, 65535);

    unsigned int y = x & 0xFF00;
    unsigned int z = y & 0xFF;
    /*@ assert z == 0; */

    unsigned int w = x | 0x000F;
    unsigned int low = w & 0x000F;
    /*@ assert low == 0x000F; */

    return (int)(z + low);
}
