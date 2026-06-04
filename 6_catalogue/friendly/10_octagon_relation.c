/* relation x - y = constante : le domaine octagon prouve tout */

#include "helpers.h"

int main(void) {
    int x = nondet_int(0, 100);
    int y = x + 10;

    /*@ assert y > x; */
    /*@ assert y - x == 10; */
    /*@ assert y >= 10; */

    int z = y - 5;
    /*@ assert z == x + 5; */
    /*@ assert z > x; */
    return z;
}
