/* may-alias avec une entree non-deterministe */

#include "helpers.h"

int main(void) {
    int x = 1, y = 2;
    int c = nondet_int(0, 1);
    int *p = c ? &x : &y;
    int z = *p;
    /*@ assert z >= 1 && z <= 2; */
    /*@ assert z == 1; */
    return z;
}
