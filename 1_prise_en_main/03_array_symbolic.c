/* acces tableau avec indice symbolique */

#include "helpers.h"

int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int i = nondet_int(0, 9);
    int v = t[i];
    /*@ assert v >= 0 && v <= 9; */
    /*@ assert v == i; */

    int j = nondet_int(0, 9);
    t[j] = 42;
    int w = t[0];
    /*@ assert w == 0 || w == 42; */

    return 0;
}
