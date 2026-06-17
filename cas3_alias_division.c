/* 
 * ------------------------------------------------------------
 * p pointe vers x OU y : EVA ne sait pas lequel (cible d'ecriture
 * IMPRECISE). L'ecriture *p=0 est donc un WEAK UPDATE : il met les
 * DEUX a {0;1} sans rien ecraser. Comme son domaine est NON
 * relationnel, il garde le produit cartesien {0;1}x{0;1} et ne peut
 * pas exclure (x=0, y=0) -- pourtant impossible en vrai. Du coup il
 * croit que x+y peut valoir 0 et leve une FAUSSE division par zero.

 * Lancer :  frama-c -eva cas3_alias_division.c
*/
#include <__fc_builtin.h>

int x = 1, y = 1;

void main(void) {
    int *p = Frama_C_interval(0, 1) ? &x : &y;  
    *p = 0;                                     

    Frama_C_show_each_apres(x, y);               

    int z = 100 / (x + y);                       
    Frama_C_show_each_resultat(z);
}
/* 1 er problem c le weak update car on aura [ 0 ; 1 ]
2 eme le produit cartesien des valeurs de x et y */
