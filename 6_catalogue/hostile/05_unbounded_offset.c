/* offset non borne par contrat : EVA suppose le pire */

#include "helpers.h"

int access(int *base, int offset) {
    return base[offset];
}

int main(void) {
    int t[5] = {1, 2, 3, 4, 5};
    int idx = nondet_int(0, 100);
    int v = access(t, idx);
    /*@ assert v >= 1 && v <= 5; */
    return v;
}
