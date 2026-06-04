/* overflow signe sur l'addition */

#include "helpers.h"

int main(void) {
    int a = nondet_int(1000000000, 2000000000);
    int b = nondet_int(1000000000, 2000000000);
    int s = a + b;
    /*@ assert s > 0; */
    return s;
}
