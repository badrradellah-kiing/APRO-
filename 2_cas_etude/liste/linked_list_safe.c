/* operations sur liste chainee avec checks et borne max. */

#include "helpers.h"

#define MAX_LIST_LEN 10

struct node {
    int val;
    struct node *next;
};

static struct node N2 = { 30, (void *)0 };
static struct node N1 = { 20, &N2 };
static struct node N0 = { 10, &N1 };

/*@ requires \valid_read(head) || head == \null;
    requires idx >= 0;
    assigns \nothing;
*/
int get_at_safe(struct node *head, int idx) {
    struct node *cur = head;
    int i = 0;
    /*@ loop invariant 0 <= i <= MAX_LIST_LEN;
        loop assigns i, cur;
        loop variant MAX_LIST_LEN - i;
    */
    while (cur && i < idx && i < MAX_LIST_LEN) {
        cur = cur->next;
        i++;
    }
    if (!cur) return -1;
    return cur->val;
}

/*@ requires \valid(prev) || prev == \null;
    requires \valid(new_node);
*/
void insert_after_safe(struct node *prev, struct node *new_node) {
    if (!prev) return;
    new_node->next = prev->next;
    prev->next = new_node;
}

int main(void) {
    int idx = nondet_int(0, 5);
    int v = get_at_safe(&N0, idx);
    /*@ assert v == -1 || v == 10 || v == 20 || v == 30; */

    struct node new_node = { 99, (void *)0 };
    int branch = nondet_int(0, 1);
    struct node *prev = branch ? &N0 : (void *)0;
    insert_after_safe(prev, &new_node);

    return v;
}
