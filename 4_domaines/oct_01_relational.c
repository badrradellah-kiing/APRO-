/* test domaine octagon : relation x - y = constante */

#include "helpers.h"

int main(void) {
    int x = nondet_int(0, 100);
    int y = x + 5;

    /*@ assert y - x == 5; */
    /*@ assert y > x; */
    /*@ assert y >= x + 5; */
    /*@ assert y <= x + 5; */

    int i = 0;
    /*@ loop invariant 0 <= i <= 10;
        loop invariant y - x == 5;
        loop assigns i, x, y;
    */
    while (i < 10) {
        x++;
        y++;
        i++;
    }
    /*@ assert y - x == 5; */

    return y - x;
}
