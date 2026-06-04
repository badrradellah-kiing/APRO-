/* boucle a bornes constantes, auto-loop-unroll deroule tout */

struct node {
    int val;
    struct node *next;
};

int main(void) {
    struct node n4 = { 4, 0 };
    struct node n3 = { 3, &n4 };
    struct node n2 = { 2, &n3 };
    struct node n1 = { 1, &n2 };
    struct node n0 = { 0, &n1 };

    struct node *p = &n0;
    int sum = 0;
    while (p) {
        sum += p->val;
        p = p->next;
    }
    /*@ assert sum == 10; */
    return sum;
}
