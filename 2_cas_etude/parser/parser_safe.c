/* tokenizer avec contrats ACSL et clamp avant copie. */

#include "helpers.h"

#define SRC_SIZE 16
#define DST_SIZE 8

static char src[SRC_SIZE];
static char dst[DST_SIZE];

/*@ requires \valid_read(s + (0 .. max-1));
    requires max >= 0;
    ensures 0 <= \result <= max;
    assigns \nothing;
*/
int find_token_end_safe(const char *s, int max) {
    int i = 0;
    /*@ loop invariant 0 <= i <= max;
        loop assigns i;
        loop variant max - i;
    */
    while (i < max && s[i] != ',' && s[i] != '\0') {
        i++;
    }
    return i;
}

/*@ requires \valid_read(s + (0 .. n-1));
    requires \valid(d + (0 .. n-1));
    requires n >= 0;
    assigns d[0 .. n-1];
*/
void copy_token_safe(const char *s, char *d, int n) {
    /*@ loop invariant 0 <= i <= n;
        loop assigns i, d[0 .. n-1];
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main(void) {
    for (int k = 0; k < SRC_SIZE; k++) {
        src[k] = (char)nondet_int(0, 127);
    }

    int len = find_token_end_safe(src, SRC_SIZE);
    /*@ assert 0 <= len <= SRC_SIZE; */

    int clamped = (len < DST_SIZE) ? len : DST_SIZE;
    /*@ assert 0 <= clamped <= DST_SIZE; */

    copy_token_safe(src, dst, clamped);
    return 0;
}
