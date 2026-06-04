/* fonction max specifiee : l'appelant exploite l'ensures */

#include "helpers.h"

/*@ ensures \result >= a && \result >= b;
    ensures \result == a || \result == b;
    assigns \nothing;
*/
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main(void) {
    int a = nondet_int(0, 100);
    int b = nondet_int(0, 100);
    int m = max(a, b);
    /*@ assert m >= a; */
    /*@ assert m >= b; */
    /*@ assert m == a || m == b; */
    return m;
}
