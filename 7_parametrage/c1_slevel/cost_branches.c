#include "helpers.h"
/* 16 branchements independants : avec un slevel eleve EVA garde
   jusqu a 2^16 etats -> le cout explose. Mesure du compromis precision/cout. */
int main(void) {
    int t = 0;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    if (nondet_any()) t += 1; else t += 2;
    /*@ assert 16 <= t && t <= 32; */
    return t;
}
