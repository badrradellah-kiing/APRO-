/* frama-c -eva cas2_liste_chainee.c
 *  */
#include <__fc_builtin.h>
#include <stdlib.h>

typedef struct node { int v; struct node *next; } node;

void main(void) {
    node *head = (void*)0;
    int n = Frama_C_interval(1, 1000);        

    for (int i = 0; i < n; i++) {
        node *m = malloc(sizeof(node));
        if (!m) break;
        m->v = i;                          
        m->next = head;
        head = m;
    }

    int s = 0;
    for (node *c = head; c; c = c->next)     
        s += c->v;

    Frama_C_show_each_somme(s);             
}
/*Le malloc en boucle crée trop d'objets pour qu'EVA leur donne un nom
 à chacun, alors il les fusionne tous en un seul 
  et à partir de là il ne peut plus les distinguer*/