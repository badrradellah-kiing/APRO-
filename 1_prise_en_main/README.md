# 1 — Prise en main

Deux choses ici :

- `check_eva.sh` vérifie l'installation de Frama-C et la disponibilité des
  domaines (equality, symbolic-locations, gauges, octagon, bitwise).
- `01_basic_pointers.c` : six cas pointeurs simples pour étalonner l'analyse.
- `02_*.c` … `07_*.c` : six **programmes de stress** qui introduisent du
  non-déterminisme pour pousser EVA dans ses retranchements.

`helpers.h` (le `nondet_int` contractualisé) vit ici et est réutilisé par tout
le projet via `-I../1_prise_en_main`.

```bash
bash check_eva.sh     # vérifie l'environnement
make bench            # lance les 6 programmes en TP/STD/MAX -> bench_results.md
```
