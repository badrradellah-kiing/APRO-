/* Version avec checks ET alignement force.
   Corrige les 3 alarmes "unaligned pointer" relevees sur allocator_safe.c :
   un bump allocator base sur char[] ne garantit pas que les pointeurs
   rendus soient alignes pour un int. On aligne donc l'arene et l'offset. */

#include "helpers.h"

#define ARENA_SIZE 64
#define ALIGN 8   /* alignement maximal raisonnable (int, pointeurs) */

/* arene alignee sur ALIGN octets */
static char arena[ARENA_SIZE] __attribute__((aligned(ALIGN)));
static unsigned top = 0;

/* arrondit n au multiple de ALIGN superieur */
/*@ requires n >= 0;
    ensures \result >= n;
    ensures \result % ALIGN == 0;
    assigns \nothing;
*/
static unsigned align_up(unsigned n) {
    return (n + (ALIGN - 1)) & ~((unsigned)(ALIGN - 1));
}

/*@ requires size >= 0;
    ensures \result == \null
         || (\result >= (void *)arena
             && \result <= (void *)(arena + ARENA_SIZE));
    assigns top;
*/
void *bump_alloc_aligned(int size) {
    if (size < 0) return (void *)0;

    unsigned asize = align_up((unsigned)size);
    if (top + asize > ARENA_SIZE) return (void *)0;

    char *p = arena + top;   /* top est toujours multiple de ALIGN */
    top = top + asize;
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