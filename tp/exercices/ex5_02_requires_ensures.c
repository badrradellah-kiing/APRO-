/* requires + ensures */

#include "helpers.h"

/*@ requires \valid(t + (0 .. n-1));
    requires n >= 1 && n <= 5;
    requires \forall integer k; 0 <= k < n ==> 1 <= t[k] <= 5;
    ensures \result >= 1;
*/
int sum_array(int *t, int n) {
    int s = 0;
    /*@ loop invariant 0 <= i <= n;
        loop invariant s >= 0;
        loop assigns i, s;
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) s += t[i];
    return s;
}

int main(void) {
    int arr[5] = {1, 2, 3, 4, 5};
    int n = nondet_int(1, 5);
    int s = sum_array(arr, n);
    /*@ assert s >= 1; */
    return s;
}
