/* ecriture a un index non-deterministe, puis lecture a un autre */

#include "helpers.h"

int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int i = nondet_int(0, 9);
    int j = nondet_int(0, 9);
    t[i] = 100;
    int v = t[j];

    /*@ assert v == 100 || (v >= 0 && v <= 9); */
    /*@ assert v == 100; */
    return v;
}
