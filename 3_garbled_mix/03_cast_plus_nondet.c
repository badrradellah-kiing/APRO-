/* cast + offset non-deterministe : pattern canonique du garbled mix */

#include <stdint.h>
#include "helpers.h"

int main(void) {
    int x = 42;
    int *p = &x;
    uintptr_t addr = (uintptr_t)p;
    int delta = nondet_int(0, 16);
    addr = addr + (uintptr_t)delta;
    int *q = (int *)addr;
    int v = *q;
    /*@ assert v == 42; */
    return v;
}
