# Complement WP — preuve de l'alignement

EVA constate que `top` reste aligne sur 8, mais ne le **prouve** pas : la
propriete `\result % ALIGN == 0` est universelle et sort de ce que le domaine
de valeurs sait exprimer. Sur `allocator_safe.c`, ca se traduit par 3 alarmes
`unaligned pointers` qui subsistent meme en configuration MAX.

WP, lui, raisonne de maniere deductive (modulo) et decharge ces obligations.

- `align_wp.c` — demonstrateur minimal : `align_up` + assertion d'alignement.
  Sous Germanium 32, WP prouve la totalite des obligations (14/14).
- `allocator_wp.c` — version specifiee du bump allocator (invariant
  `top % ALIGN == 0` propage de proche en proche).

```bash
make align        # frama-c align_wp.c -wp -wp-rte -wp-prover alt-ergo
make allocator
```

C'est l'illustration concrete de la complementarite EVA / WP : EVA pour la
sur-approximation automatique de valeurs, WP pour les proprietes relationnelles
ou universelles que le treillis ne capture pas.
