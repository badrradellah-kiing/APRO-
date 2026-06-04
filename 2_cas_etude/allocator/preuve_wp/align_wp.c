/* align_up : arrondi au multiple de ALIGN superieur.
   EVA calcule la bonne valeur mais ne prouve pas la postcondition
   universelle  \result % ALIGN == 0 ; WP la demontre.
   Analyse : frama-c align_wp.c -wp -wp-rte */

#define ALIGN 8

/* version arithmetique (div/mul) plutot que masque : le raisonnement
   modulaire passe mieux pour WP */
/*@ requires 0 <= n <= 1000;
    assigns \nothing;
    ensures \result >= n;
    ensures \result % ALIGN == 0;
    ensures \result < n + ALIGN;
*/
unsigned align_up(unsigned n)
{
    return ((n + ALIGN - 1) / ALIGN) * ALIGN;
}

/*@ requires 0 <= n <= 1000;
    assigns \nothing;
    ensures \result % ALIGN == 0;
*/
unsigned check_aligned(unsigned n)
{
    unsigned a = align_up(n);
    /*@ assert a % ALIGN == 0; */
    return a;
}
