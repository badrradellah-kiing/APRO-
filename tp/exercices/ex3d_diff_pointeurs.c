#include <stdint.h>
int main(void) {
    int a = 10, b = 20;
    uintptr_t pa = (uintptr_t)&a;
    uintptr_t pb = (uintptr_t)&b;
    uintptr_t pc = pb + (pa - pb);        /* difference de pointeurs */
    int *q = (int *)pc;
    int v = *q;
    /*@ assert v == 10; */
    return v;
}
