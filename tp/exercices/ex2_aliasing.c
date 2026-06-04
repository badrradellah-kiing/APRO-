#include "helpers.h"

int main(void) {
    int a = 10, b = 20;

    int *p = &a;
    *p = 30;
    /*@ assert a == 30; */        /* (1) */

    int *q;
    if (nondet_any()) q = &a; else q = &b;
    *q = 99;
    /*@ assert a == 99; */        /* (2) */

    return a;
}
