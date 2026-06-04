# Phase 3.2 — Comparaison fine des domaines abstraits

## But scientifique

Identifier précisément **quel domaine fait quoi** : quand le mot "domaines avancés" recouvre 5 outils différents, on veut savoir lequel sert dans quel contexte.

## Méthodologie

5 programmes ciblés, chacun conçu pour exercer **un seul domaine** :

| Programme | Domaine ciblé |
|-----------|---------------|
| `eq_01_pointer_equality.c` | equality |
| `sl_01_array_symbolic.c` | symbolic-locations |
| `oct_01_relational.c` | octagon |
| `ga_01_loop_relations.c` | gauges |
| `bw_01_bitops.c` | bitwise |

Chaque programme est analysé sous **6 configurations** (1 sans domaine avancé + 5 avec un seul domaine actif chacune) = **30 analyses au total**.

## Comment tester

```bash
cd ce dossier
chmod +x bench_3_2.sh
make bench
```

Produit `bench_3_2_results.md` avec une matrice programme × domaine, format `alarmes/valid/unknown`.

## Lecture attendue

Sur la diagonale (programme `eq_01` avec domaine `equality`, etc.) on doit voir une **chute des unknown**. Hors diagonale, peu de changement.

Si un domaine non-ciblé apporte un bénéfice : c'est un **effet de bord positif** à documenter (matériau pour le rapport).
