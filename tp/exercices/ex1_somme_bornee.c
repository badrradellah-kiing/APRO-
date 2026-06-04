/* Somme d'un tableau statique borne. */
int main(void) {
    int t[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int s = 0;
    for (int i = 0; i < 10; i++) {
        s += t[i];
    }
    /*@ assert s == 45; */
    return s;
}
