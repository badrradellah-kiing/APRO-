/* test domaine gauges : relations lineaires avec compteur de boucle */

int main(void) {
    int s = 0;
    int n = 100;

    /*@ loop invariant 0 <= i <= n;
        loop invariant s == 3 * i;
        loop assigns i, s;
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) {
        s += 3;
    }
    /*@ assert s == 300; */

    int a = 0, b = 0;
    /*@ loop invariant 0 <= i <= 10;
        loop invariant a == i;
        loop invariant b == 2 * i;
        loop assigns i, a, b;
    */
    for (int i = 0; i < 10; i++) {
        a++;
        b += 2;
    }
    /*@ assert b == 2 * a; */

    return s + a + b;
}
