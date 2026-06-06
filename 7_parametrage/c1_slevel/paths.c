#include "helpers.h"
/* x et y prennent la meme valeur dans chaque branche, mais la RELATION
   x == y est perdue quand EVA fusionne les etats (slevel insuffisant).
   Avec assez d'etats separes, la relation est prouvee. */
int main(void) {
    int c = nondet_int(0, 3);
    int x, y;
    if      (c == 0) { x = 10; y = 10; }
    else if (c == 1) { x = 20; y = 20; }
    else if (c == 2) { x = 30; y = 30; }
    else             { x = 40; y = 40; }
    /*@ assert x == y; */
    return x + y;
}
