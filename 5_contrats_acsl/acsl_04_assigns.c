/* avec assigns pour limiter les effets de bord */

static int global = 100;

/*@ requires \valid(p);
    assigns *p;
    ensures *p == 42;
*/
void set_to_42(int *p) {
    *p = 42;
}

int main(void) {
    int x = 0;
    int y = 999;

    set_to_42(&x);

    /*@ assert x == 42; */
    /*@ assert y == 999; */
    /*@ assert global == 100; */

    return x + y;
}
