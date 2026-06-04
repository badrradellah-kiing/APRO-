/* malloc en boucle : EVA fusionne toutes les bases creees */

#include <stdlib.h>

int main(void) {
    int *p_first = 0;
    int *p_last = 0;

    for (int i = 0; i < 10; i++) {
        int *p = malloc(sizeof(int));
        if (!p) return -1;
        *p = i;
        if (i == 0) p_first = p;
        if (i == 9) p_last = p;
    }

    int a = p_first ? *p_first : -1;
    int b = p_last  ? *p_last  : -1;
    /*@ assert a == 0; */
    /*@ assert b == 9; */
    return a + b;
}
