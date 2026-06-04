/* patterns C que EVA gere mal */

#include <stdint.h>
#include <stdlib.h>
#include "helpers.h"

/* cast pointeur <-> entier avec arithmetique */
int pointer_cast(void) {
    int x = 42;
    int *p = &x;
    uintptr_t addr = (uintptr_t)p;
    addr += (uintptr_t)nondet_int(0, 4);
    int *q = (int *)addr;
    return *q;
}

/* malloc en boucle : fusion des bases */
int malloc_in_loop(void) {
    int *first = 0, *last = 0;
    for (int i = 0; i < 10; i++) {
        int *p = malloc(sizeof(int));
        if (!p) return -1;
        *p = i;
        if (i == 0) first = p;
        if (i == 9) last = p;
    }
    return (first ? *first : -1) + (last ? *last : -1);
}

/* recursion sur liste chainee */
struct node { int v; struct node *next; };
int recursive_sum(struct node *n) {
    if (!n) return 0;
    return n->v + recursive_sum(n->next);
}

/* pointeur sur fonction */
typedef int (*fn_t)(int);
int times_two(int x) { return x * 2; }
int times_three(int x) { return x * 3; }

int function_pointer(void) {
    fn_t f = nondet_int(0, 1) ? times_two : times_three;
    return f(5);
}

/* offset non-borne par contrat */
int unbounded_offset(int *base, int offset) {
    return base[offset];
}

int main(void) {
    int a = pointer_cast();
    int b = malloc_in_loop();

    struct node n2 = { 30, 0 };
    struct node n1 = { 20, &n2 };
    struct node n0 = { 10, &n1 };
    int c = recursive_sum(&n0);

    int d = function_pointer();

    int arr[5] = {1, 2, 3, 4, 5};
    int e = unbounded_offset(arr, nondet_int(0, 10));

    return a + b + c + d + e;
}
