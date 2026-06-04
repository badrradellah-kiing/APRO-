/* alignement par AND : pattern courant en embarque */

#include <stdint.h>

int main(void) {
    int x = 42;
    int *p = &x;
    uintptr_t addr = (uintptr_t)p;
    addr = addr & ~((uintptr_t)3);
    int *q = (int *)addr;
    int v = *q;
    /*@ assert v == 42; */
    return v;
}
