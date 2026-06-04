/* tokenization in-place : le buffer source est aussi destination. */

#include "helpers.h"

#define BUF_SIZE 16

static char buf[BUF_SIZE];

/*@ requires \valid(s + (0 .. max-1));
    requires max >= 0;
    ensures 0 <= \result <= max;
    assigns s[0 .. max-1];
*/
int tokenize_inplace(char *s, int max) {
    int i = 0;
    /*@ loop invariant 0 <= i <= max;
        loop assigns i, s[0 .. max-1];
        loop variant max - i;
    */
    while (i < max && s[i] != ',') {
        i++;
    }
    if (i < max) {
        s[i] = '\0';
    }
    return i;
}

int main(void) {
    for (int k = 0; k < BUF_SIZE; k++) {
        buf[k] = (char)nondet_int(1, 127);
    }

    int pos = nondet_int(0, BUF_SIZE - 1);
    buf[pos] = ',';

    int len = tokenize_inplace(buf, BUF_SIZE);
    /*@ assert 0 <= len <= BUF_SIZE; */

    if (len < BUF_SIZE) {
        char c = buf[len];
        /*@ assert c == 0; */
    }

    return len;
}
