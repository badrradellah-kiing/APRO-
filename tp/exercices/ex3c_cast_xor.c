#include <stdint.h>
int main(void) {
    int x = 42;
    uintptr_t a = (uintptr_t)&x;
    a = a ^ 0xF0 ^ 0xF0;                  /* xor k xor k */
    int *p = (int *)a;
    int v = *p;
    /*@ assert v == 42; */
    return v;
}
