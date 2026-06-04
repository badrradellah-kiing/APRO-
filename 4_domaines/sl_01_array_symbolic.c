/* test domaine symbolic-locations : meme indice deux fois -> meme valeur */

#include "helpers.h"

int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int i = nondet_int(0, 9);
    int a = t[i];
    int b = t[i];
    /*@ assert a == b; */

    t[i] = 99;
    int c = t[i];
    /*@ assert c == 99; */

    return a + b + c;
}
