# Phase 3.3 — Catalogue de patterns EVA-friendly / EVA-hostile

## But

Documenter les patterns de code C qui sont **bien gérés** par EVA, vs ceux qui le mettent **en échec**. Document de référence pour quiconque veut écrire du code C vérifiable par interprétation abstraite.

---

## ✅ Patterns EVA-friendly

Ces patterns sont reconnus précisément par EVA et permettent une vérification fluide.

### F1 — Tableaux à taille statique avec boucles bornées
```c
int t[10] = {0, 1, ..., 9};
for (int i = 0; i < 10; i++) { sum += t[i]; }
```
**Pourquoi ça marche** : `auto-loop-unroll` déroule la boucle quand elle est bornée par une constante. Les accès `t[i]` sont entièrement résolus.

### F2 — Pointeurs avec base unique connue
```c
int x = 100;
int *p = &x;
*p = *p + 1;
```
**Pourquoi ça marche** : `p` a une seule base mémoire (`&x`), donc strong update à chaque écriture.

### F3 — Structures statiques avec accès direct
```c
struct point p = { .x = 3, .y = 4 };
int d = p.x * p.x + p.y * p.y;
```
**Pourquoi ça marche** : EVA modélise précisément les champs de structure, l'arithmétique sur des constantes est évaluée.

### F4 — Conditions sur des bornes déjà prouvées
```c
if (n >= 0 && n <= 10) { result = n * 2; }
```
**Pourquoi ça marche** : EVA propage l'information de la garde dans le corps du `if`, donc `result ∈ [0, 20]`.

### F5 — Itération avec invariant ACSL explicite
```c
/*@ loop invariant 0 <= i <= 100;
    loop invariant s == i; */
for (int i = 0; i < 100; i++) { s = s + 1; }
```
**Pourquoi ça marche** : EVA utilise l'invariant comme aide à la convergence, le widening est domestiqué.

---

## ❌ Patterns EVA-hostile

Ces patterns mettent EVA en échec, même avec tous les domaines avancés activés.

### H1 — Cast pointeur ↔ entier avec arithmétique
```c
uintptr_t addr = (uintptr_t)p;
addr = addr + nondet_value;
int *q = (int *)addr;       // garbled mix
```
**Pourquoi ça casse** : la représentation entière de `p` n'est plus reliable à une base mémoire après arithmétique non-déterministe.

**Remède** : éviter le cast, utiliser de l'arithmétique de pointeur directement (`p + offset` reste interprétable).

### H2 — Allocation dynamique en boucle
```c
for (int i = 0; i < N; i++) { p[i] = malloc(...); }
```
**Pourquoi ça casse** : EVA fusionne toutes les bases `malloc` créées en boucle pour éviter une explosion combinatoire. Les cellules individuelles ne sont plus distinguables.

**Remède** : utiliser un tableau statique si la taille max est connue, ou des "pools" de mémoire pré-allouée.

### H3 — Structure récursive avec parcours récursif
```c
int sum(struct node *n) {
    if (!n) return 0;
    return n->v + sum(n->next);
}
```
**Pourquoi ça casse** : la récursion sur structure chaînée nécessite un raisonnement inductif que l'interprétation abstraite ne fait pas naturellement.

**Remède** : itérer avec une borne explicite (cf. F1).

### H4 — Pointeur sur fonction
```c
fn_t f = condition ? times_two : times_three;
return f(5);
```
**Pourquoi ça casse** : l'appel via pointeur force EVA à analyser toutes les cibles possibles et à fusionner leurs effets.

**Remède** : remplacer par un `switch` explicite si possible.

### H5 — Pointeur sur tableau avec offset non-borné par contrat
```c
int access(int *base, int offset) { return base[offset]; }  // sans contrat
```
**Pourquoi ça casse** : sans contrat ACSL sur `offset`, EVA suppose le pire (`INT_MIN..INT_MAX`).

**Remède** : ajouter un contrat `/*@ requires 0 <= offset < N; */`.

---

## Comment vérifier ce catalogue

```bash
cd 
make all
```

Les patterns `friendly` doivent produire **0 ou très peu d'alarmes**, et les patterns `hostile` doivent produire **beaucoup d'alarmes** quelle que soit la configuration.

Ce catalogue sera intégré tel quel dans le rapport final (section "Recommandations pratiques").
