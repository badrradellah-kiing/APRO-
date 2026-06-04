#include <stdlib.h>
int main(void) {
    int *tab[4];
    for (int i = 0; i < 4; i++) {
        tab[i] = malloc(sizeof(int));
        if (tab[i]) *tab[i] = i;
    }
    if (tab[0] && tab[1]) {
        /*@ assert *tab[0] == 0; */
        /*@ assert *tab[1] == 1; */
    }
    return 0;
}
