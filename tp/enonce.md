# TP complémentaire — Analyse de pointeurs avec Frama-C / EVA

Ce TP prolonge le TP d'interprétation abstraite de l'UE Analyse de programmes.
Il explore l'analyse de pointeurs avec EVA : ce qu'elle prouve, où elle décroche,
et pourquoi. Le fil conducteur est la distinction entre deux types d'échec —
ceux qu'on corrige avec plus de précision, et ceux où le domaine ne peut tout
simplement pas exprimer la propriété.

**Prérequis** : Frama-C ≥ 27 (testé sous 32 Germanium), le greffon WP + un
prouveur (Alt-Ergo) pour l'exercice 6.

**Rappel des trois configurations** utilisées dans tout le TP :

| Config | Commande |
|--------|----------|
| baseline | `frama-c FICHIER.c -eva -eva-precision 0` |
| std      | `frama-c FICHIER.c -eva -eva-precision 2 -eva-domains equality,symbolic-locations` |
| max      | `frama-c FICHIER.c -eva -eva-precision 5 -eva-domains equality,symbolic-locations,octagon,gauges,bitwise` |

Pour les fichiers qui incluent `helpers.h`, ajouter
`-cpp-extra-args="-I."` depuis le dossier `exercices/`.

Lire le résumé d'analyse (`Assertions ... valid ... unknown`) et les lignes
`[eva:alarm]` en fin de sortie.

---

## Exercice 1 — Précision et déroulage de boucle (`ex1_somme_bornee.c`)

1. Analysez le fichier en configuration **baseline**. Quel est le statut de
   l'assertion `s == 45` ?
2. Relancez en **std**. Le statut change-t-il ? Expliquez ce que fait le
   paramètre `auto-loop-unroll` et pourquoi il évite ici le *widening*.
3. Selon vous, ce passage de Unknown à Valid est-il une question de précision ou
   d'expressivité du domaine ? Justifiez.

## Exercice 2 — Strong update et may-alias (`ex2_aliasing.c`)

1. Analysez le fichier. Quel est le statut de l'assertion (1) ? de l'assertion (2) ?
2. Pourquoi EVA prouve-t-il (1) mais pas (2) ? Reliez votre réponse aux notions de
   *strong update* et de *may-alias*.
3. Aucune augmentation de précision ne change le statut de (2). Pourquoi ? Quelle
   information manque à EVA, et comment la lui fournir (sans modifier la logique) ?

## Exercice 3 — Caractérisation du *garbled mix* (`ex3a` … `ex3d`)

Chaque fichier insère **une seule** opération entre un cast pointeur→entier et le
cast retour.

1. Analysez les quatre fichiers en configuration **max**. Pour chacun, relevez le
   nombre d'alarmes et indiquez si la sortie d'EVA contient le terme
   `garbled mix`.
2. Remplissez le tableau :

   | Fichier | opération | alarmes | garbled mix ? |
   |---------|-----------|---------|---------------|
   | ex3a | cast trivial | | |
   | ex3b | + nondet | | |
   | ex3c | xor k xor k | | |
   | ex3d | diff. pointeurs | | |

3. À partir de ces résultats, formulez une hypothèse : **quel type d'opération**
   fait basculer EVA en garbled mix ? Le non-déterminisme suffit-il ?

## Exercice 4 — Une limite structurelle (`ex4_malloc_boucle.c`)

1. Analysez en **max**. Les assertions `*tab[0] == 0` et `*tab[1] == 1`
   sont-elles prouvées ?
2. Augmenter la précision ne change rien. Expliquez pourquoi, en parlant de la
   **fusion des bases** allouées dans une boucle.
3. En quoi cette limite diffère-t-elle de celle de l'exercice 1 ?

## Exercice 5 — Contrats ACSL : invariant et frame (`ex5_00` … `ex5_04`)

Les cinq fichiers enrichissent progressivement le contrat d'une fonction
(aucun contrat → requires → ensures → loop invariant → loop assigns).

1. Analysez les cinq fichiers dans l'ordre. Relevez pour chacun le couple
   (alarmes, valid/unknown).
2. La progression est-elle monotone (les Unknown baissent-ils à chaque étape) ?
   Identifiez l'étape où l'analyse **régresse**.
3. Expliquez cette régression : quelles obligations un `loop invariant`
   introduit-il, et pourquoi ne peut-on pas les tenir sans clause de cadre
   (`loop assigns`) ? Quelle leçon pratique en tirez-vous sur l'écriture des
   contrats de boucle ?

## Exercice 6 — Mur d'expressivité et complément WP (`ex6_*.c`)

1. Analysez `ex6_allocator.c` en **max**. Combien d'alarmes restent ? De quel type
   sont-elles (lire les lignes `[eva:alarm]`) ?
2. Cette propriété est vraie à l'exécution et EVA connaît même l'intervalle de
   `top`. Pourquoi ne la prouve-t-il pas, quelle que soit la précision ?
3. Dans `ex6_align_wp.c`, complétez le contrat de `align_up` avec l'`ensures`
   d'alignement manquant, puis prouvez-le :
   ```
   frama-c ex6_align_wp.c -wp -wp-rte -wp-prover alt-ergo
   ```
   Toutes les obligations sont-elles déchargées ?
4. Concluez : pourquoi EVA et WP sont-ils complémentaires plutôt que concurrents ?
