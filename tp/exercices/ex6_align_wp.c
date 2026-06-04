/* A completer puis prouver avec WP (question 6.3). */
#define ALIGN 8

/*@ requires 0 <= n <= 1000;
    assigns \nothing;
    ensures \result >= n;
    // TODO 6.3 : ajouter l'ensures d'alignement que EVA ne sait pas prouver
*/
unsigned align_up(unsigned n) {
    return ((n + ALIGN - 1) / ALIGN) * ALIGN;
}
