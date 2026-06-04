/* init de tableau avec invariant ACSL fort */

int main(void) {
    int t[5];

    /*@ loop invariant 0 <= i <= 5;
        loop invariant \forall integer k; 0 <= k < i ==> t[k] == k * 2;
        loop assigns i, t[0..4];
        loop variant 5 - i;
    */
    for (int i = 0; i < 5; i++) {
        t[i] = i * 2;
    }

    /*@ assert t[0] == 0; */
    /*@ assert t[2] == 4; */
    /*@ assert t[4] == 8; */
    return t[0] + t[2] + t[4];
}
