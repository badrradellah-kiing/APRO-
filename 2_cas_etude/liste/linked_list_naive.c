/* operations sur liste chainee sans checks. */

#include "helpers.h"

struct node {
    int val;
    struct node *next;
};

static struct node N2 = { 30, (void *)0 };
static struct node N1 = { 20, &N2 };
static struct node N0 = { 10, &N1 };

void insert_after_naive(struct node *prev, struct node *new_node) {
    new_node->next = prev->next;
    prev->next = new_node;
}

int get_at_naive(struct node *head, int idx) {
    struct node *cur = head;
    for (int i = 0; i < idx; i++) {
        cur = cur->next;
    }
    return cur->val;
}

int main(void) {
    int idx = nondet_int(0, 5);
    int v = get_at_naive(&N0, idx);
    /*@ assert v == 10 || v == 20 || v == 30; */

    struct node new_node = { 99, (void *)0 };
    int branch = nondet_int(0, 1);
    struct node *prev = branch ? &N0 : (void *)0;
    insert_after_naive(prev, &new_node);

    return v;
}
