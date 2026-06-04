/* ecriture via p, lecture via q : q peut etre alias de p */

#include "helpers.h"

int main(void) {
    int x = 0, y = 0;

    int *p = &x;
    int c = nondet_int(0, 1);
    int *q = c ? &x : &y;

    *p = 5;
    int vx = x;
    int vy = y;
    int vq = *q;

    /*@ assert vx == 5; */
    /*@ assert vy == 0; */
    /*@ assert vq == 0 || vq == 5; */
    /*@ assert vq == 5; */

    return vx + vy + vq;
}
