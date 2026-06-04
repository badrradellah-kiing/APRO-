/* Allocateur bump entierement specifie pour WP.
   But : prouver deductivement ce que EVA ne fait que constater,
   en particulier l'invariant d'alignement de top.
   Analyse : frama-c allocator_wp.c -wp -wp-rte */

#define ARENA_SIZE 64
#define ALIGN 8

static char arena[ARENA_SIZE] __attribute__((aligned(ALIGN)));
static unsigned top = 0;   /* invariant : multiple de ALIGN */

/*@ requires 0 <= n <= ARENA_SIZE;
    assigns \nothing;
    ensures \result >= n;
    ensures \result % ALIGN == 0;
    ensures \result <= n + ALIGN - 1;
*/
static unsigned align_up(unsigned n)
{
    return ((n + ALIGN - 1) / ALIGN) * ALIGN;
}

/*@ requires top % ALIGN == 0;
    requires top <= ARENA_SIZE;
    requires 0 <= size <= ARENA_SIZE;
    assigns top;
    ensures top % ALIGN == 0;
    ensures top <= ARENA_SIZE;
    ensures \result == 0 || (top <= ARENA_SIZE && \old(top) <= top);
*/
static int bump_offset(int size)
{
    unsigned asize = align_up((unsigned)size);
    /*@ assert asize % ALIGN == 0; */

    if (top + asize > ARENA_SIZE)
        return -1;

    unsigned old = top;
    top = top + asize;
    /*@ assert top % ALIGN == 0; */
    return (int)old;
}

/*@ requires top % ALIGN == 0;
    requires top <= ARENA_SIZE;
    assigns top;
*/
int main(void)
{
    int off1 = bump_offset(4);
    /*@ assert off1 == -1 || off1 % ALIGN == 0; */

    int off2 = bump_offset(20);
    /*@ assert off2 == -1 || off2 % ALIGN == 0; */

    return 0;
}
