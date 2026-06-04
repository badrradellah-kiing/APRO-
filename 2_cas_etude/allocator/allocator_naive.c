/* Bump allocator sans aucun garde-fou : bugs intentionnels. */

#include "helpers.h"

#define ARENA_SIZE 64

static char arena[ARENA_SIZE];
static unsigned top = 0;

void *bump_alloc(int size) {
    char *p = arena + top;
    top = top + size;   /* pas de check : peut deborder */
    return p;
}

int main(void) {
    int *a = (int *)bump_alloc(16);
    /*@ assert \valid(a); */
    *a = 42;
    int va = *a;
    /*@ assert va == 42; */

    int sz = nondet_int(1, 100);   /* peut etre > ARENA_SIZE */
    char *b = (char *)bump_alloc(sz);
    b[0] = 'x';
    char vb = b[0];
    /*@ assert vb == 'x'; */

    int neg = nondet_int(-10, 10); /* taille negative */
    char *c = (char *)bump_alloc(neg);
    (void)c;

    return va;
}
