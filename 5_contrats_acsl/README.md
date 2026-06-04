# Phase 3.4 — Étude des contrats ACSL

## But scientifique

Mesurer l'apport **incrémental** de chaque type de contrat ACSL sur la précision d'EVA. Question fondamentale : *quel contrat coûte le moins cher à écrire pour le plus grand gain en précision ?*

## Méthodologie

5 versions de la **même fonction**, avec des contrats ACSL de plus en plus riches :

| # | Contrats ajoutés |
|---|-----------------|
| 00 | Aucun (baseline) |
| 01 | `requires` (préconditions) |
| 02 | `requires` + `ensures` (postconditions) |
| 03 | `loop invariant` (en plus) |
| 04 | `assigns` (en plus) |

## Comment tester

```bash
cd ce dossier
chmod +x bench_3_4.sh
make bench
```

Produit `bench_3_4_results.md` avec un tableau montrant la progression valid / unknown au fil des contrats.

## Résultat attendu (et findings pour le rapport)

On devrait voir une **chute monotone des Unknown** :

```
acsl_00 :  ... Unknown plusieurs
acsl_01 :  ... Unknown reduit
acsl_02 :  ... Unknown encore reduit (gros saut)
acsl_03 :  ... Unknown quasi nul
acsl_04 :  ... Unknown = 0
```

Le **gros saut** se fait typiquement entre 01 et 02 (l'ajout d'un `ensures`), car c'est ce qui permet à l'appelant de conclure sans re-analyser.

Ces résultats alimenteront la section "Recommandations pour le code C vérifiable" du rapport final.
