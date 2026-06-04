/* arithmetique de pointeur sans cast (EVA reste-t-il precis ?) */

#include "helpers.h"

int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int delta = nondet_int(0, 16);
    int *p = t + delta;
    int v = *p;
    /*@ assert v >= 0 && v <= 9; */
    return v;
}
