/* Version avec checks et contrats ACSL. */

#include "helpers.h"

#define ARENA_SIZE 64

static char arena[ARENA_SIZE];
static unsigned top = 0;

/*@ requires size >= 0;
    ensures \result == \null
         || (\result >= (void *)arena
             && \result <= (void *)(arena + ARENA_SIZE));
    assigns top;
*/
void *bump_alloc_safe(int size) {
    if (size < 0) return (void *)0;
    if (top + (unsigned)size > ARENA_SIZE) return (void *)0;

    char *p = arena + top;
    top = top + (unsigned)size;
    return p;
}

int main(void) {
    int *a = (int *)bump_alloc_safe(16);
    if (!a) return -1;
    /*@ assert \valid(a); */
    *a = 42;
    int va = *a;
    /*@ assert va == 42; */

    int sz = nondet_int(1, 100);
    char *b = (char *)bump_alloc_safe(sz);
    if (b) {
        b[0] = 'x';
        char vb = b[0];
        /*@ assert vb == 'x'; */
    }

    return va;
}
