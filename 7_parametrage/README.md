# 7 — Paramétrage et précision (axe C)

Étude systématique des paramètres d'EVA (slevel, déroulage, widening) et de leur
impact sur la **précision** et sur le **coût** (temps d'analyse). C'est la dimension
nouvelle par rapport à l'axe B, qui ne mesurait que la précision.

| Sous-étude | Question |
|------------|----------|
| `c1_slevel/`     | que coûte / rapporte la sensibilité aux chemins ? |
| `c2_unrolling/`  | quand le déroulage de boucle prouve-t-il, et à quel prix ? |
| `c3_widening/`   | quel paramètre contre vraiment la perte due au widening ? |
| `c4_compromis/`  | le compromis précision/coût, et retour sur la limite de la 3.2 |

Chaque sous-étude a son `Makefile` (`make bench`) et produit une table de
résultats. Les programmes incluent `helpers.h` via `-I../../1_prise_en_main`.

**Note méthodo** : le coût est mesuré en temps réel (`date`), donc machine- et
version-dépendant. Sur de très petits programmes le temps est dans le bruit
(~0,2 s de démarrage) ; les programmes de coût (`cost_branches`, etc.) sont
volontairement conçus pour faire apparaître la courbe. Tous les chiffres sont
indicatifs ; c'est la *forme* (seuil, plateau, explosion) qui est le résultat.

**Lien avec l'axe B** : la sous-étude C.4 rejoue les programmes relationnels de
la 3.2 et montre qu'aucun réglage ne débloque l'octogone — la limite de la 3.2
n'est donc pas un manque de précision.
