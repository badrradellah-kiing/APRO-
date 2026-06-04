/* double-free : on libere deux fois le meme pointeur */

#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    if (!p) return -1;
    *p = 42;
    free(p);
    free(p);  /* double free */
    return 0;
}
