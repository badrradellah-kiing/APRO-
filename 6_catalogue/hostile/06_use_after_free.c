/* use-after-free : on lit a une adresse libree */

#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    if (!p) return -1;
    *p = 42;
    free(p);
    int v = *p;  /* lecture apres free */
    /*@ assert v == 42; */
    return v;
}
