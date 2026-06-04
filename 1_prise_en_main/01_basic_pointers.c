/* Premiers essais sur EVA : 6 cas pointeurs du plus simple au plus tordu.
   On regarde ce qu'EVA detecte et ce qu'il rate. */

#include <stdio.h>

/* Cas 1 : pointeur direct */
void cas1_simple(void) {
    int x = 42;
    int *p = &x;
    int y = *p;
    /*@ assert y == 42; */
}

/* Cas 2 : deux pointeurs sur la meme variable */
void cas2_alias(void) {
    int x = 10;
    int *p = &x;
    int *q = &x;
    *p = 20;
    int y = *q;
    /*@ assert y == 20; */
}

/* Cas 3 : pointeur dont la cible depend d'une condition */
void cas3_branche(int c) {
    int x = 1;
    int y = 2;
    int *p;
    if (c) p = &x;
    else   p = &y;
    int z = *p;
    /*@ assert z >= 1 && z <= 2; */
    /*@ assert z == 1; */
}

/* Cas 4 : arithmetique de pointeur sur tableau */
void cas4_array(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = t + 3;
    int v = *p;
    /*@ assert v == 3; */
}

/* Cas 5 : pointeur potentiellement nul */
void cas5_null(int c) {
    int x = 5;
    int *p = c ? &x : (int *)0;
    int y = *p;
    /*@ assert y == 5; */
}

/* Cas 6 : retourner l'adresse d'une variable locale (dangling) */
int *fuite(void) {
    int local = 99;
    return &local;
}

void cas6_dangling(void) {
    int *p = fuite();
    int y = *p;
    /*@ assert y == 99; */
}

int main(void) {
    cas1_simple();
    cas2_alias();
    cas3_branche(1);
    cas4_array();
    cas5_null(1);
    cas6_dangling();
    return 0;
}
