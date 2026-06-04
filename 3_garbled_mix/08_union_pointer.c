/* type punning via union */

#include <stdint.h>

union ptr_int {
    int *p;
    uintptr_t addr;
};

int main(void) {
    int x = 42;
    union ptr_int u;
    u.p = &x;

    uintptr_t copy = u.addr;
    u.addr = copy;

    int *q = u.p;
    int v = *q;
    /*@ assert v == 42; */
    return v;
}
