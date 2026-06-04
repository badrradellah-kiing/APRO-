/* fonction completement specifiee : l'appelant peut conclure sans la re-analyser */

/*@ requires \valid(t + (0 .. n-1));
    requires n >= 1 && n <= 100;
    requires \forall integer k; 0 <= k < n ==> 0 <= t[k] <= 1000;
    ensures \result >= 0;
    ensures \result <= n * 1000;
    assigns \nothing;
*/
int sum_bounded(int *t, int n) {
    int s = 0;
    /*@ loop invariant 0 <= i <= n;
        loop invariant 0 <= s <= i * 1000;
        loop assigns i, s;
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) {
        s += t[i];
    }
    return s;
}

int main(void) {
    int t[5] = {10, 20, 30, 40, 50};
    int s = sum_bounded(t, 5);
    /*@ assert s >= 0; */
    /*@ assert s <= 5000; */
    return s;
}
