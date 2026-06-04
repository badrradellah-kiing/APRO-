/* baseline : cast aller-retour sans arithmetique */

#include <stdint.h>

int main(void) {
    int x = 42;
    int *p = &x;
    uintptr_t addr = (uintptr_t)p;
    int *q = (int *)addr;
    int v = *q;
    /*@ assert v == 42; */
    return v;
}
