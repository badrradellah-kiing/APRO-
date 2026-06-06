# C.1 — slevel (sensibilité aux chemins)

`-eva-slevel N` = nombre d'états gardés séparés par point de programme avant
fusion. Plus haut = plus précis, mais plus coûteux.

- `paths.c` : la relation `x == y` n'est prouvée que si EVA garde assez d'états
  (perdue à la fusion). La précision monte avec le slevel puis plafonne.
- `cost_branches.c` : 16 branchements → jusqu'à 2^16 états. La précision ne bouge
  pas, mais le **coût explose** (jusqu'au timeout).

```bash
make bench   # -> bench_slevel_results.md
```

Enseignement : le slevel achète de la précision jusqu'à un seuil, au-delà il ne
fait que brûler du temps. Le bon réglage est le plus petit qui suffit.
