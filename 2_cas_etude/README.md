# Phase 2 — Cas d'etude

3 cas typiques en C systeme, chacun en 3 versions :

- **naive** : bugs intentionnels, EVA doit alarmer
- **safe** : version avec contrats ACSL, EVA doit tout valider
- **aliased/ambiguous** : zone grise

```bash
chmod +x bench_phase2.sh
make bench
```

Produit `bench_results_phase2.md` (27 analyses).
