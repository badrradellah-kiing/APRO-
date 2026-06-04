/* chaine de pointeurs avec branches non-deterministes */

#include "helpers.h"

int main(void) {
    int x = 1, y = 2;
    int *a = nondet_int(0, 1) ? &x : &y;
    int **b = &a;
    int *c = *b;

    int v = *c;
    /*@ assert v == 1; */
    /*@ assert v == 1 || v == 2; */
    return v;
}
