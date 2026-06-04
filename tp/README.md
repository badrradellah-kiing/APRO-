# TP complémentaire — Analyse de pointeurs avec Frama-C / EVA

Proposition d'exercices pour prolonger le TP d'interprétation abstraite de l'UE
Analyse de programmes (objectif 4 du sujet de TER). Construit à partir des
programmes du projet, le TP fait parcourir la frontière d'EVA : ce qu'il prouve,
où il décroche, et la distinction entre limites de précision et limites
d'expressivité (avec un dernier exercice sur le complément WP).

```
tp/
├── enonce.md          énoncé des 6 exercices (à distribuer)
├── corrige.md         corrigé : commandes, résultats attendus, explications
└── exercices/         fichiers .c de départ
```

## Progression

1. Précision et déroulage de boucle
2. Strong update et may-alias
3. Caractérisation du garbled mix
4. Une limite structurelle (fusion des bases malloc)
5. Contrats ACSL : invariant et frame
6. Mur d'expressivité et complément WP (alignement)

## Prérequis

Frama-C ≥ 27 (testé sous 32 Germanium). Pour l'exercice 6, le greffon WP et un
prouveur (Alt-Ergo via why3).
