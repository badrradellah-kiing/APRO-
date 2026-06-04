# Corrigé du TP — Analyse de pointeurs avec EVA

Résultats donnés sous Frama-C 32 Germanium. Les comptes exacts d'alarmes et le
seuil de déclenchement du *garbled mix* peuvent varier d'une version à l'autre
(voir la note de l'exercice 6) ; les conclusions, elles, restent valables.

Depuis `tp/exercices/`, les fichiers qui incluent `helpers.h` se lancent avec
`-cpp-extra-args="-I."`.

---

## Exercice 1

```
frama-c ex1_somme_bornee.c -eva -eva-precision 0      # baseline
frama-c ex1_somme_bornee.c -eva -eva-precision 2      # std
```

- baseline : `s == 45` **Unknown**. Le *widening* sur-approxime la boucle et perd
  la valeur exacte de `s`.
- std : `s == 45` **Valid**. L'`auto-loop-unroll` déroule la boucle (borne
  constante 10), donc EVA calcule `s` exactement sans passer par le widening.

C'est une limite de **précision** : on la corrige avec du budget (axe C), pas en
changeant de méthode.

## Exercice 2

```
frama-c ex2_aliasing.c -eva -eva-precision 2 -cpp-extra-args="-I."
```

- (1) `a == 30` : **Valid**. `p` a une base unique connue (`&a`), donc l'écriture
  `*p = 30` est un *strong update*.
- (2) `a == 99` : **Unknown**. Après le `if` non-déterministe, `q` vaut `&a` ou
  `&b` ; l'écriture `*q = 99` est un *weak update* sur deux bases possibles. Dans
  la branche `q = &b`, `a` reste 10, donc EVA ne peut pas affirmer `a == 99`.

Augmenter la précision n'y change rien : EVA raisonne en *may-alias* (sûr) et ne
fait pas de *must-alias*. Pour lever l'ambiguïté il faudrait rendre certaine la
base de `q`.

## Exercice 3

```
for f in ex3a_cast_trivial ex3b_cast_nondet ex3c_cast_xor ex3d_diff_pointeurs; do
  echo "== $f =="; frama-c $f.c -eva -eva-precision 5 \
    -eva-domains equality,symbolic-locations,octagon,gauges,bitwise \
    -cpp-extra-args="-I." 2>&1 | grep -iE "alarm generated|garbled"
done
```

| Fichier | opération | alarmes | garbled mix ? |
|---------|-----------|---------|---------------|
| ex3a | cast trivial roundtrip | 0 | non |
| ex3b | + offset non-déterministe | oui | **non** |
| ex3c | xor k xor k | oui | oui |
| ex3d | différence de pointeurs | oui | oui |

**Hypothèse attendue.** Le garbled mix ne vient pas du non-déterminisme : ex3b
ajoute un offset non-déterministe, EVA lève une alarme mais **conserve la base**
(pas de garbled mix). Il bascule en garbled mix sur les opérations **non
affines** — XOR, masque de bits, différence de pointeurs — qui cassent le modèle
base + offset. Ce n'est donc pas l'incertitude de la valeur qui pose problème,
mais la nature bit-à-bit / différentielle de l'opération.

## Exercice 4

```
frama-c ex4_malloc_boucle.c -eva -eva-precision 5 \
  -eva-domains equality,symbolic-locations,octagon,gauges,bitwise
```

`*tab[0] == 0` et `*tab[1] == 1` restent **Unknown**, même en max. EVA fusionne
les blocs alloués dans une boucle (sinon le nombre de bases exploserait), donc
`tab[0]` et `tab[1]` désignent une même base abstraite : il ne distingue plus les
cellules. Contrairement à l'exercice 1, ce n'est pas un problème de précision —
plus de budget ne change rien. C'est une limite **structurelle** du modèle
mémoire.

## Exercice 5

```
for f in ex5_00_no_contract ex5_01_requires ex5_02_requires_ensures \
         ex5_03_loop_invariant ex5_04_assigns; do
  echo "== $f =="; frama-c $f.c -eva -eva-precision 2 -cpp-extra-args="-I." \
    2>&1 | grep -E "Assertions"
done
```

| Étape | contrat ajouté | alarmes / valid / unknown |
|-------|----------------|---------------------------|
| 00 | aucun | 0 / 1 / 0 |
| 01 | + requires | 0 / 1 / 0 |
| 02 | + ensures | 0 / 3 / 0 |
| 03 | + loop invariant | **2 / 3 / 1** |
| 04 | + loop assigns | 0 / 3 / 0 |

La progression **n'est pas monotone** : l'étape 03 régresse. Un `loop invariant`
crée ses propres obligations — il faut prouver qu'il est vrai en entrée de boucle
(établissement) puis qu'il le reste à chaque tour (préservation). Sans clause de
cadre, l'analyse ne sait pas quelles variables la boucle laisse intactes, donc
elle ne peut pas démontrer la préservation : d'où les alarmes et l'Unknown.
L'ajout de `loop assigns` (étape 04) lève la régression.

**Leçon.** Invariant de boucle et clause de cadre forment un couple : spécifier
l'un sans l'autre est contre-productif.

## Exercice 6

```
frama-c ex6_allocator.c -eva -eva-precision 5 \
  -eva-domains equality,symbolic-locations,octagon,gauges,bitwise \
  -cpp-extra-args="-I."
```

1. Il reste **3 alarmes `unaligned pointers`**, déclenchées par le cast du
   pointeur rendu en `int *`.
2. La propriété est `(\&arena + top) % alignof(int) == 0`. Elle est vraie à
   l'exécution, et EVA connaît même `top ∈ [16..64]`. Mais c'est une congruence
   universelle, et le domaine de valeurs raisonne sur des ensembles d'adresses,
   pas sur ce type de relation modulo. Aucune précision ne peut combler ce
   manque : c'est une limite d'**expressivité du domaine**.
3. Contrat à compléter dans `ex6_align_wp.c` :
   ```c
   ensures \result % ALIGN == 0;
   ```
   ```
   frama-c ex6_align_wp.c -wp -wp-rte -wp-prover alt-ergo
   ```
   WP décharge toutes les obligations (sur le fichier complet `align_wp.c` du
   projet, on obtient 14/14).
4. **Complémentarité.** EVA calcule automatiquement, sans annotation, une
   sur-approximation des valeurs : il excelle pour la sûreté mémoire. WP prouve
   de façon déductive des propriétés relationnelles ou universelles (ici
   l'alignement) que le treillis d'EVA ne capte pas, mais demande des contrats.
   On utilise EVA pour le gros de l'analyse, WP pour les quelques propriétés qui
   sortent de l'expressivité du domaine.

**Note (sensibilité à la version).** Sous une version antérieure (Frama-C 25
Manganese), `ex6_allocator.c` ne lève **aucune** alarme d'alignement : le
traitement des casts de pointeurs a changé. Le raisonnement reste valable, mais
c'est un bon rappel que tout résultat expérimental d'EVA doit être rattaché à une
version précise.
