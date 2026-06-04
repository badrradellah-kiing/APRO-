/* cast + addition d'une constante puis soustraction (neutre algebrique) */

#include <stdint.h>

int main(void) {
    int x = 42;
    int *p = &x;
    uintptr_t addr = (uintptr_t)p;
    addr = addr + 4;
    addr = addr - 4;
    int *q = (int *)addr;
    int v = *q;
    /*@ assert v == 42; */
    return v;
}
