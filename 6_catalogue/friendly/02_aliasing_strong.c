/* aliasing simple : EVA suit l'ecriture via les deux pointeurs */

int main(void) {
    int x = 0;
    int *p = &x;
    int *q = &x;

    *p = 42;
    int v = *q;
    /*@ assert v == 42; */

    *q = 100;
    int w = *p;
    /*@ assert w == 100; */
    return v + w;
}
