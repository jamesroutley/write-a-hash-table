# Introduction

Une table de hachage est une structure de données qui offre implémentation rapide des [tableaux associatifs](#api).

Comme la terminologie autour des tables de hachage peut être source de confusion, j'ai ajouté des définitions [ci-dessous](#Terminologie).

Une table de hachage consiste en un tableau de 'buckets' qui stockent chacun une paire de clef-valeur.
Pour localiser ou stocker une paire dans le 'bucket', la clef est transformé par une fonction de hachage.

Cette fonction renvoie un entier qui est utilisé comme index dans le tableau de 'bucket'.

Pour récupérer une paire de clef-valeur, il faut fournir la clé à la même fonction de hachage et utiliser la valeur renvoyé comme index dans le tableau de 'bucket'.

L'indexation de tableaux a une complexité algorithmique `O(1)`, rendant les tables de hachage rapide à stocker et récupérer des données.

La table de hachage que nous implémenterons utilisera comme clef et valeur des chaines de charactères mais le principe général est applicable avec n'importe quel type de clef et de valeur.
Seules les chaînes ASCII seront prises en charge car prendre en charge l'Unicode est non trivial.

## API

Un [tableau associatif](https://fr.wikipedia.org/wiki/Tableau_associatif) est une une collection de paires de clefs-valeurs non ordonnées.
Chaque clef doit etre unique. Les opérations suivantes sont prises en charge:

- `search(a, k)`: renvoie la valeur `v` associée à la clef `k` du tableau  associatif `a`, ou `NULL` si la clef n'existe pas.
- `insert(a, k, v)`: stocke la paire `k:v` dans le tableau associatif `a`.
- `delete(a, k)`: supprime la paire `k:v` associée à la clef `k` si `k` existe

## Installation

Pour installer C sur votre ordinateur, consulter le guide de [Daniel Holden's](@orangeduck) : [Build Your OwnLisp](http://www.buildyourownlisp.com/chapter2_installation).

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

`src` contiendra le code, `build` contiendra nos binaires compilés.

## Terminology

Dans cet article, nous suivrons la terminologie suivante :

- Tableau associatif : une structure de données abstraite qui implémente l'[API](#api) décrite ci-dessus.
  Aussi appelé dictionnaire ou table d'association.
- Table de hachage : une implémentation possible de l'[API](#api) des tableaux associatifs. Utilise une fonction de hachage. Aussi appelé hash ou dictionnaire.

Les tableaux associatifs peuvent être implémentés de nombreuses manières.
Deux implémentations efficaces : la [table de hachage](https://fr.wikipedia.org/wiki/Table_de_hachage) et [l'arbre équilibré](https://fr.wikipedia.org/wiki/Arbre_%C3%A9quilibr%C3%A9).

Une implémentation (non performante) peut être réalisé en stockant simplement des éléments dans un tableau puis en itérant à travers le tableau lors de la recherche.

La plupart du temps les tableaux associatifs sont implémenté comme table de hachage ce qui entraine des confusions.

Next section: [Structure d'une table de hachage](/02-hash-table)

[Table des matières](.translations/fr/README.md#contents)
