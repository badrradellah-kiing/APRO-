/* malloc en boucle : EVA fusionne les bases */

#include <stdlib.h>

int main(void) {
    int *p_first = (void*)0;
    int *p_last  = (void*)0;

    for (int i = 0; i < 10; i++) {
        int *p = malloc(sizeof(int));
        if (!p) return -1;
        *p = i;
        if (i == 0) p_first = p;
        if (i == 9) p_last  = p;
    }
    /*@ assert p_first != (void*)0; */
    /*@ assert p_last  != (void*)0; */

    int a = *p_first;
    int b = *p_last;
    /*@ assert a == 0; */
    /*@ assert b == 9; */

    return a + b;
}
