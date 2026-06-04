/* fonction sans aucun contrat ACSL : baseline */

#include "helpers.h"

int sum_array(int *t, int n) {
    int s = 0;
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
