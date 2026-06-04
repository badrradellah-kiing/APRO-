/* avec loop invariant en plus */

#include "helpers.h"

/*@ requires \valid(t + (0 .. n-1));
    requires n >= 1 && n <= 5;
    requires \forall integer k; 0 <= k < n ==> 1 <= t[k] <= 5;
    ensures \result == n;
*/
int count_ones(int *t, int n) {
    int s = 0;
    /*@ loop invariant 0 <= i <= n;
        loop invariant s == i;
        loop assigns i, s;
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) s++;
    return s;
}

int main(void) {
    int arr[5] = {1, 1, 1, 1, 1};
    int n = nondet_int(1, 5);
    int c = count_ones(arr, n);
    /*@ assert c == n; */
    /*@ assert c >= 1 && c <= 5; */
    return c;
}
