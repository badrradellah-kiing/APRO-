# Phase 3.1 — Caractérisation du garbled mix

## But scientifique

Identifier précisément les opérations qui font basculer EVA en `garbled mix` (perte totale d'information sur la base mémoire pointée).

## Méthodologie

Huit micro-programmes minimaux (~15 lignes chacun) testant chacun **une seule opération** entre un cast pointeur→entier et le cast inverse. Le principe : isoler les facteurs.

| # | Opération testée |
|---|---------------|
| 01 | aucune (baseline) |
| 02 | `+4` puis `-4` (neutre arithmétique) |
| 03 | `+ nondet_int(0,16)` |
| 04 | `^ 0xDEAD` deux fois |
| 05 | `& ~3` (alignement) |
| 06 | différence de deux pointeurs |
| 07 | arithmétique pointeur SANS cast |
| 08 | accès via `union` |

## Comment tester

```bash
cd ce dossier
chmod +x bench_3_1.sh
make bench
```

Produit `bench_3_1_results.md` avec 24 analyses (8 × 3 configs) et une colonne supplémentaire `garbled-mix?` qui détecte explicitement le mot-clé dans les sorties.

## Lien avec Phase 1.3

Cette étape généralise systématiquement le cas 06 de la Phase 1.3 (qui testait un seul pattern). Phase 3.1 cartographie le territoire complet.
