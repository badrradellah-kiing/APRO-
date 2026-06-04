/* somme recursive vs iterative bornee : on compare ce qu'EVA prouve. */

struct node {
    int val;
    struct node *next;
};

static struct node N2 = { 30, (void *)0 };
static struct node N1 = { 20, &N2 };
static struct node N0 = { 10, &N1 };

/*@ assigns \nothing; */
int sum_rec(struct node *head) {
    if (!head) return 0;
    return head->val + sum_rec(head->next);
}

/*@ assigns \nothing; */
int sum_iter(struct node *head, int max_depth) {
    int s = 0;
    struct node *cur = head;
    /*@ loop invariant 0 <= i <= max_depth;
        loop assigns i, s, cur;
        loop variant max_depth - i;
    */
    for (int i = 0; i < max_depth && cur != (void *)0; i++) {
        s += cur->val;
        cur = cur->next;
    }
    return s;
}

int main(void) {
    int s_rec = sum_rec(&N0);
    int s_iter = sum_iter(&N0, 10);

    /*@ assert s_rec == 60; */
    /*@ assert s_iter == 60; */
    /*@ assert s_rec == s_iter; */

    return s_iter;
}
