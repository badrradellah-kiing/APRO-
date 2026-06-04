/* cast pointeur->entier->arith->pointeur : garbled mix */

#include <stdint.h>
#include "helpers.h"

int main(void) {
    int x = 42;
    int *p = &x;

    uintptr_t addr = (uintptr_t)p;
    addr += (uintptr_t)nondet_int(0, 4);
    int *q = (int *)addr;

    int v = *q;
    /*@ assert v == 42; */
    return v;
}
