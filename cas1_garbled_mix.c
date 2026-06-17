/* 
 * ------------------------------------------------------------
 * Une adresse, pour EVA, est un couple (base, offset) -- PAS un
 * nombre. Des qu'on fait un calcul qui exige la valeur numerique
 * de l'adresse (ici un modulo), EVA produit un "garbled mix" :
 * une valeur inconnue et contaminante. Resultat : il ne peut plus
 * borner l'indice et leve de FAUSSES alarmes hors-bornes.
 *
 * Le code est SUR : idx = adresse % 16 est toujours dans [0,15].
 * frama-c -eva cas1_garbled_mix.c
 */
#include <__fc_builtin.h>
int x;
int t[16];

void main(void) {
    int *p = &x;
    unsigned long a = (unsigned long)p;   
    Frama_C_show_each_apres_cast(a);    

    unsigned long g = a % 16;            
    Frama_C_show_each_apres_hash(g);     

    int idx = (int)g;                    
    t[idx] = 1;                          
}
/* eva pour les adresses travaille avec base + offset  */