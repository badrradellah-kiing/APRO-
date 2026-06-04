/* tokenizer naif : pas de borne sur la boucle. */

#include "helpers.h"

#define SRC_SIZE 16
#define DST_SIZE 8

static char src[SRC_SIZE];
static char dst[DST_SIZE];

int find_token_end(const char *s) {
    int i = 0;
    while (s[i] != ',' && s[i] != '\0') {  /* peut deborder */
        i++;
    }
    return i;
}

void copy_token(const char *s, char *d, int len) {
    for (int i = 0; i < len; i++) {
        d[i] = s[i];   /* peut deborder d */
    }
}

int main(void) {
    for (int k = 0; k < SRC_SIZE; k++) {
        src[k] = (char)nondet_int(0, 127);
    }

    int len = find_token_end(src);
    /*@ assert len >= 0; */
    /*@ assert len <= SRC_SIZE; */

    copy_token(src, dst, len);
    return 0;
}
