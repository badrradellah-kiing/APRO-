/* parcours d'une liste chainee statique a 3 noeuds */

struct node {
    int val;
    struct node *next;
};

int main(void) {
    struct node n2 = { 2, (void*)0 };
    struct node n1 = { 1, &n2 };
    struct node n0 = { 0, &n1 };

    struct node *p = &n0;
    int sum = 0;
    while (p != (void*)0) {
        sum += p->val;
        p = p->next;
    }
    /*@ assert sum == 3; */
    return sum;
}
