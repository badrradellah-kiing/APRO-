/* difference entre deux pointeurs castes */

#include <stdint.h>

int main(void) {
    int a = 10;
    int b = 20;

    uintptr_t addr_a = (uintptr_t)&a;
    uintptr_t addr_b = (uintptr_t)&b;
    uintptr_t diff = addr_a - addr_b;
    uintptr_t addr_c = addr_b + diff;

    int *q = (int *)addr_c;
    int v = *q;
    /*@ assert v == 10; */
    return v;
}
