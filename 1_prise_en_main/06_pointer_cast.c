/* cast pointeur->entier->pointeur avec offset non-deterministe */

#include <stdint.h>
#include "helpers.h"

int main(void) {
    int x = 42;
    int y = 99;  /* anti-optim */
    int *p = &x;

    uintptr_t addr = (uintptr_t)p;
    int offset = nondet_int(-4, 4);
    addr = addr + (uintptr_t)offset;

    int *q = (int *)addr;
    int v = *q;
    /*@ assert v == 42; */

    return v + y;
}
