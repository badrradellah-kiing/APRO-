#include <stdint.h>
#include "helpers.h"
int main(void) {
    int x = 42;
    uintptr_t a = (uintptr_t)&x;
    int delta = nondet_int(0, 16);
    a = a + (uintptr_t)delta;             /* offset non-deterministe */
    int *p = (int *)a;
    int v = *p;
    /*@ assert v == 42; */
    return v;
}
