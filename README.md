# TER M1 FSI — Analyse statique avec Frama-C/EVA (axe B)

Travail d'Étude et de Recherche, M1 Informatique parcours **Fiabilité et
Sécurité Informatique**, Aix-Marseille Université.

**Étudiants** : Youssef Azizi, Badr Radellah
**Encadrants** : Benjamin Monmège, Léo Henry
**Axe** : B — analyse de pointeurs et d'aliasing (+ extension axe C : paramétrage)

---

## But du projet

Cartographier ce que l'analyse de valeurs d'EVA prouve et ce qu'elle ne prouve
pas sur les pointeurs en C. Le fil conducteur : EVA échoue de deux façons.

- **Limites de précision** : un Unknown dû au widening, qui disparaît avec plus
  de précision (slevel, déroulage de boucle).
- **Murs d'expressivité** : une propriété que le domaine ne peut pas représenter,
  qu'aucune précision ne corrigera. Exemple : l'alignement mémoire, que WP prouve
  en quelques secondes là où EVA laisse des alarmes même au maximum.

## Organisation

Les dossiers sont numérotés dans l'ordre de lecture, et nommés par **ce qu'ils
démontrent** :

| Dossier | Contenu |
|---------|---------|
| `1_prise_en_main/` | vérif environnement, cas pointeurs simples, programmes de stress (et `helpers.h`) |
| `2_cas_etude/` | allocator, parser, liste — chacun en *naive* / *safe* / *aliased* (+ `allocator/preuve_wp/`) |
| `3_garbled_mix/` | dans quelles conditions EVA perd la base d'un pointeur |
| `4_domaines/` | quel domaine abstrait débloque quelle propriété |
| `5_contrats_acsl/` | effet de chaque clause de contrat ACSL |
| `6_catalogue/` | synthèse `friendly/` (EVA prouve) vs `hostile/` (EVA décroche) |
| `7_parametrage/` | **axe C** : étude des paramètres slevel / unrolling / widening (précision vs coût) |
| `tp/` | TP complémentaire : énoncé, corrigé, exercices |

`run_tests.sh` relance tout et agrège les résultats dans `RESULTS.md`. Chaque
dossier a son `README.md`. Le rapport (PDF + LaTeX) est rendu à part.

## Lancer

```bash
chmod +x run_tests.sh && ./run_tests.sh      
```

Vue rapide marche / décroche :

```bash
cd 6_catalogue/friendly && make all
cd ../hostile           && make all
```

## Conventions

Trois configurations par programme : `TP` (`-eva-precision 0`),
`STD` (`-eva-precision 2` + equality,symbolic-locations),
`MAX` (`-eva-precision 5` + tous les domaines). Tous les chiffres sont sous
**Frama-C 32 Germanium** ; le comportement sur l'alignement dépend de la version,
donc les logs portent la version.

## Prérequis

Frama-C ≥ 27 (testé sous 32 Germanium) ; le greffon **WP** + Alt-Ergo (via why3)
pour `2_cas_etude/allocator/preuve_wp/` et l'exercice 6 du TP ; gcc, make, bash, awk.

```bash
sudo apt install frama-c
```

## État

Tout est terminé (phases 1–3, complément WP prouvé 14/14, catalogues, TP).
Plusieurs résultats infirment nos hypothèses de départ (garbled mix dû aux
opérations bit-à-bit et non au non-déterminisme ; domaines relationnels qui ne
s'activent pas en `4_domaines/`) — c'est documenté tel quel.

Perspectives : comprendre l'inactivité de l'octogone (lien axe C), comparer à
`gcc -fanalyzer` / clang static analyzer, documenter la sensibilité à la version.
