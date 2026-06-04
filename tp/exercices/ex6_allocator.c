/* Bump allocator contractualise. A analyser avec EVA (voir enonce). */
#include "helpers.h"
#define ARENA 64
static char arena[ARENA];
static unsigned top = 0;

/*@ requires size >= 0;
    ensures \result == \null
         || (\result >= (void *)arena && \result <= (void *)(arena + ARENA));
    assigns top; */
void *bump(int size) {
    if (size < 0) return (void *)0;
    if (top + (unsigned)size > ARENA) return (void *)0;
    char *p = arena + top;
    top += (unsigned)size;
    return p;
}

int main(void) {
    int *a = (int *)bump(16);
    if (!a) return -1;
    *a = 42;
    /*@ assert *a == 42; */
    return *a;
}
