/* swap avec contrat complet (separated requis pour eviter l'aliasing) */

/*@ requires \valid(a) && \valid(b);
    requires \separated(a, b);
    assigns *a, *b;
    ensures *a == \old(*b);
    ensures *b == \old(*a);
*/
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void) {
    int x = 10, y = 20;
    swap(&x, &y);
    /*@ assert x == 20; */
    /*@ assert y == 10; */
    return x + y;
}
