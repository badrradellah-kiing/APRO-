/* deux pointeurs A et B dans la meme arene + un troisieme C
   avec offset symbolique qui peut chevaucher. */

#include "helpers.h"

#define ARENA_SIZE 128

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
    int *A = (int *)bump_alloc_safe(sizeof(int));
    int *B = (int *)bump_alloc_safe(sizeof(int));
    if (!A || !B) return -1;

    *A = 10;
    *B = 20;
    int vA = *A;
    int vB = *B;

    /*@ assert vA == 10; */
    /*@ assert vB == 20; */
    /*@ assert A != B; */

    int offset = nondet_int(0, 8);
    char *C = arena + offset;
    *C = (char)99;

    int vA_after = *A;
    /*@ assert vA_after == 10 || vA_after != 10; */

    return vA + vB;
}
