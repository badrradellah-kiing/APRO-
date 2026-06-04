/* pointeur sur fonction : EVA doit unir les effets de toutes les cibles */

#include "helpers.h"

typedef int (*fn_t)(int);

int times_two(int x)   { return x * 2; }
int times_three(int x) { return x * 3; }
int plus_one(int x)    { return x + 1; }

int main(void) {
    int c = nondet_int(0, 2);
    fn_t f;
    if (c == 0) f = times_two;
    else if (c == 1) f = times_three;
    else f = plus_one;

    int r = f(5);
    /*@ assert r == 10 || r == 15 || r == 6; */
    return r;
}
