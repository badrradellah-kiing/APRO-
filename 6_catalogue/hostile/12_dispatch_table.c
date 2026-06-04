/* dispatch via tableau de pointeurs sur fonctions */

#include "helpers.h"

int op_add(int x, int y) { return x + y; }
int op_sub(int x, int y) { return x - y; }
int op_mul(int x, int y) { return x * y; }

typedef int (*op_t)(int, int);
static op_t ops[3] = { op_add, op_sub, op_mul };

int main(void) {
    int k = nondet_int(0, 2);
    int r = ops[k](6, 2);
    /*@ assert r == 8 || r == 4 || r == 12; */
    /*@ assert r >= 4 && r <= 12; */
    return r;
}
