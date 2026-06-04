/* recursion sur structure chainee : EVA decroche */

struct node { int v; struct node *next; };

int sum_rec(struct node *n) {
    if (!n) return 0;
    return n->v + sum_rec(n->next);
}

int main(void) {
    struct node n2 = { 30, 0 };
    struct node n1 = { 20, &n2 };
    struct node n0 = { 10, &n1 };

    int s = sum_rec(&n0);
    /*@ assert s == 60; */
    return s;
}
