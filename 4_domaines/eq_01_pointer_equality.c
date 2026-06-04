/* test domaine equality : EVA suit-il p == q apres copies/branches ? */

#include "helpers.h"

int main(void) {
    int x = 10;
    int *p = &x;
    int *q = p;

    *q = 20;
    int v = x;
    /*@ assert v == 20; */

    int c = nondet_int(0, 1);
    int *r = c ? p : q;

    *r = 30;
    int w = x;
    /*@ assert w == 30; */

    return v + w;
}
