/* division avec garde explicite : EVA elimine la division par zero */

#include "helpers.h"

int safe_divide(int a, int b) {
    if (b == 0) return -1;
    return a / b;
}

int main(void) {
    int a = nondet_int(0, 1000);
    int b = nondet_int(0, 10);     /* b peut valoir 0 : la garde est exercee */
    int r = safe_divide(a, b);
    /*@ assert r >= -1; */         /* r vaut -1 (b==0) ou a/b >= 0 */
    return r;
}
