/* tableau statique + boucle bornee : EVA prouve tout */

int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = 0;
    /*@ loop invariant 0 <= i <= 10;
        loop invariant sum >= 0;
        loop assigns i, sum;
        loop variant 10 - i;
    */
    for (int i = 0; i < 10; i++) {
        sum += t[i];
    }
    /*@ assert sum == 45; */
    return sum;
}
