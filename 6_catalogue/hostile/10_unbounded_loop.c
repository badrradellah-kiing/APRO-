/* boucle non bornee statiquement : widening detruit la precision */

#include "helpers.h"

int main(void) {
    int n = nondet_int(0, 10000);
    int s = 0;
    int i = 0;
    while (i < n) {
        s = s + 1;
        i = i + 1;
    }
    /*@ assert s == n; */
    /*@ assert s >= 0 && s <= 10000; */
    return s;
}
