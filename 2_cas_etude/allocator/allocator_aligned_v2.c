/* Version alignee, v2 : alignement calcule par arithmetique entiere
   (division/multiplication) au lieu d'un masque bit-a-bit.
   EVA prouve mal le masque `& ~7`, mais raisonne bien sur `/` et `*`.
   On ajoute aussi une assertion explicite sur l'alignement de top. */

#include "helpers.h"

#define ARENA_SIZE 64
#define ALIGN 8

static char arena[ARENA_SIZE] __attribute__((aligned(ALIGN)));
static unsigned top = 0;

/*@ requires 0 <= n <= ARENA_SIZE;
    ensures \result >= n;
    ensures \result % ALIGN == 0;
    ensures n <= \result < n + ALIGN;
    assigns \nothing;
*/
static unsigned align_up(unsigned n) {
    return ((n + ALIGN - 1) / ALIGN) * ALIGN;
}

/*@ requires size >= 0;
    ensures \result == \null
         || (\result >= (void *)arena
             && \result <= (void *)(arena + ARENA_SIZE));
    assigns top;
*/
void *bump_alloc_aligned(int size) {
    if (size < 0) return (void *)0;
    if ((unsigned)size > ARENA_SIZE) return (void *)0;

    unsigned asize = align_up((unsigned)size);
    /*@ assert asize % ALIGN == 0; */
    /*@ assert top % ALIGN == 0; */

    if (top + asize > ARENA_SIZE) return (void *)0;

    char *p = arena + top;
    top = top + asize;
    /*@ assert top % ALIGN == 0; */
    return p;
}

int main(void) {
    int *a = (int *)bump_alloc_aligned(sizeof(int));
    if (!a) return -1;
    /*@ assert \valid(a); */
    *a = 42;
    int va = *a;
    /*@ assert va == 42; */

    int sz = nondet_int(1, 40);
    char *b = (char *)bump_alloc_aligned(sz);
    if (b) {
        b[0] = 'x';
        char vb = b[0];
        /*@ assert vb == 'x'; */
    }

    return va;
}