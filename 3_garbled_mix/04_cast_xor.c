/* xor + xor inverse = neutre. Mais EVA suit-il ? */

#include <stdint.h>

int main(void) {
    int x = 42;
    int *p = &x;
    uintptr_t addr = (uintptr_t)p;
    addr = addr ^ 0xDEAD;
    addr = addr ^ 0xDEAD;
    int *q = (int *)addr;
    int v = *q;
    /*@ assert v == 42; */
    return v;
}
