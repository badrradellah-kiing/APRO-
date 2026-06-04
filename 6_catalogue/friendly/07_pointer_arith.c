/* arithmetique de pointeur sur tableau, offsets constants */

int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p = t + 3;
    int *q = p + 2;
    int v = *p + *q;
    /*@ assert *p == 3; */
    /*@ assert *q == 5; */
    /*@ assert v == 8; */
    return v;
}
