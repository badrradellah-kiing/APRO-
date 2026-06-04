/* patterns C que EVA gere bien */

#include "helpers.h"

/* tableau statique + boucle bornee */
int static_array(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = 0;
    /*@ loop invariant 0 <= i <= 10;
        loop invariant sum >= 0;
        loop assigns i, sum;
        loop variant 10 - i;
    */
    for (int i = 0; i < 10; i++) sum += t[i];
    /*@ assert sum == 45; */
    return sum;
}

/* pointeur avec base unique */
int single_base(void) {
    int x = 100;
    int *p = &x;
    *p = *p + 1;
    /*@ assert x == 101; */
    return x;
}

/* structure statique */
struct point { int x; int y; };
int struct_access(void) {
    struct point p = { 3, 4 };
    int d = p.x * p.x + p.y * p.y;
    /*@ assert d == 25; */
    return d;
}

/* garde explicite sur l'entree */
int bounded_input(void) {
    int n = nondet_int(0, 10);
    int r = 0;
    if (n >= 0 && n <= 10) r = n * 2;
    /*@ assert r >= 0 && r <= 20; */
    return r;
}

/* iteration avec invariant */
int loop_with_invariant(void) {
    int s = 0;
    /*@ loop invariant 0 <= i <= 100;
        loop invariant s == i;
        loop assigns i, s;
    */
    for (int i = 0; i < 100; i++) s++;
    /*@ assert s == 100; */
    return s;
}

int main(void) {
    return static_array() + single_base() + struct_access()
         + bounded_input() + loop_with_invariant();
}
