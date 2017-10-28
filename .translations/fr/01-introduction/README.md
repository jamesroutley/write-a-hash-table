# Introduction

Une table de hachage est une structure de données qui offre une implémentation rapide des [tableaux associatifs](#api).

Comme la terminologie autour des tables de hachage peut être source de confusion, j'ai ajouté des définitions [ci-dessous](#terminologie).

Une table de hachage consiste en un tableau d'élements, dont chacun stocke une paire de clef-valeur.
Pour localiser ou stocker une paire, la clef est passée à une fonction de hachage.

Cette fonction renvoie un entier qui est utilisé comme index de la paire dans le tableau d'éléments.

Ainsi, pour récupérer une paire de clef-valeur, il faut fournir la clé à la fonction de hachage et utiliser la valeur renvoyée comme index dans le tableau.

L'indexation de tableau a une complexité algorithmique `O(1)`, rendant les tables de hachage rapides à stocker et à retrouver des données.

La table de hachage que nous implémenterons utilisera comme clef et comme valeur des chaines de charactères mais le principe général est applicable avec n'importe quel type de clef et de valeur.
Seules les chaînes ASCII seront prises en charge car prendre en charge l'Unicode est non trivial et hors sujet vis-à-vis de ce tutoriel.

## API

Un [tableau associatif](https://fr.wikipedia.org/wiki/Tableau_associatif) est une collection de paires de clefs-valeurs non ordonnées.
Chaque clef doit etre unique. Les opérations suivantes sont prises en charge:

- `search(a, k)`: renvoie la valeur `v` associée à la clef `k` du tableau  associatif `a`, ou `NULL` si la clef n'existe pas.
- `insert(a, k, v)`: stocke la paire `k:v` dans le tableau associatif `a`.
- `delete(a, k)`: supprime la paire `k:v` associée à la clef `k` si `k` existe, ne fait rien si `k` n''existe pas.

## Installation

Pour installer C sur votre ordinateur, consultez le guide de [Daniel Holden's](@orangeduck) : [Build Your Own Lisp](http://www.buildyourownlisp.com/chapter2_installation).

Build Your Own Lisp est un excellent livre, qu'au passage je recommande.

## Structure du code

L'arborescence du code sera la suivante :

```
.
├── build
└── src
    ├── hash_table.c
    ├── hash_table.h
    ├── prime.c
    └── prime.h
```

Le dossier `src` contiendra le code, `build` contiendra nos fichiers binaires compilés.

## Terminologie

Beaucoup de noms peuvent etre utilisés dans différents contextes.
Dans cet article, nous suivrons la terminologie suivante :

- Tableau associatif : une structure de données abstraite qui implémente l'[API](#api) décrite ci-dessus.
  Aussi appelé dictionnaire ou table d'association.
- Table de hachage : une implémentation possible de l'[API](#api) des tableaux associatifs. Utilise une fonction de hachage. Aussi appelée hach ou dictionnaire.

Les tableaux associatifs peuvent être implémentés de nombreuses manières.
Voici deux implémentations efficaces : la [table de hachage](https://fr.wikipedia.org/wiki/Table_de_hachage) et [l'arbre équilibré](https://fr.wikipedia.org/wiki/Arbre_%C3%A9quilibr%C3%A9).

Une implémentation (non performante) peut être réalisée en stockant simplement des éléments dans un tableau puis en itérant à travers le tableau lors de la recherche.

Les tableaux associatifs sont souvent implémentés comme des tables de hachage, ce qui entraine des confusions.

Section suivante: [Structure d'une table de hachage](../02-hash-table)

[Table des matières](/.translations/fr/README.md#contents)
