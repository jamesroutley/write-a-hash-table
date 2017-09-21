# Annexe : Gestion de collisions alternative

Il existe deux méthodes principale pour traiter les collisions dans les tables de hashage :

- Le chaînage
- L'adressage ouvert

### Le chaînage

Avec cette methode, chaque valeur de la table de hashage constitue en une liste chainé. Lorsque les éléments entrent en collision, ils sont ajoutés à la liste courrante. Méthodes:

- Insertion: hacher la clé pour obtenir l'indice dans le tableau. S'il n'y a rien, stocker l'objet. S'il y a déjà un élément, ajoutez l'élément à la liste liée.
- Recherche: hasher la clé pour obtenir l'indice dans le tableau. Parcourez la liste chainé en comparant la clé de chaque élément à la clé de recherche. Si la clé est trouvée, renvoyez la valeur, sinon retournez «NULL».
- Supprimer: hacher la clé pour obtenir l'indice dans le tableau. . Parcourez la liste chainé en comparant la clé de chaque élément à la clé de recherche. Si la clé est trouvée, supprimez l'élément de la liste liée. S'il n'y a qu'un seul élément dans la liste liée, mettez un pointeur `NULL`

Cela a l'avantage d'être simple à mettre en œuvre, c'est couteux : Chaque élément doit stocker un pointeur vers l'élément suivant dans la liste ou le pointeur `NULL`. Cela consomme donc de l'espace.

### L'adressage ouvert

L'adressage ouvert vise à le probeme du chainage. Quand des collisions se produisent, l'élément en colision est placé dans un autre indice du tableau.
Il existe 3 méthodes pour calculer l'indice dans du tableau dans lequel stocker la valeur en colision.

#### Le sondage linéaire

Lorsqu'une collision se produit, l'index est incrémenté et l'élément est placé dans le prochain indice disponible dans le tableau. Méthodes:

- Insertion: hacher la clé pour obtenir l'indice dans le tableau. S'il n'y a rien, stocker l'objet. S'il y a déjà un élément, incrémentez l'indice jusqu'à plusieurs fois jusqu'à ce qu'un seau vide soit trouvé et insérez-le.
- Recherche: hasher la clé pour obtenir l'indice dans le tableau, incrementer l'indice jusqu'a ce que la clef de l'element courrant soit egal a la clef de recherche ou a «NULL», retourner la valeur correspondante.
- Supprimer: hasher la clé pour obtenir l'indice dans le tableau, incrementer l'indice jusqu'a ce que la clef de l'element courrant soit egal a la clef de recherche ou a «NULL», supprimer la valeur correspondante. La suppression de cet élément brise la chaîne, il faut doncréinsérer tous les éléments de la chaîne après l'élément supprimé.

Linear probing offers good [cache performance](https://en.wikipedia.org/wiki/Locality_of_reference), but suffers from clustering issues. Putting collided items in the next available bucket can lead to long contiguous stretches of filled buckets, which need to be iterated over when inserting, searching or deleting.

La sondage linéaire offre de bonne [performance de cache](https://en.wikipedia.org/wiki/Locality_of_reference), mais souffre de problèmes de performance. La presence de nombreuse collision peut provoquer de nombreuses iterations lors de l'insertion, la recherche ou la suppression.

#### Le sondage quadratique

Similaire au sondage linéaire, mais au lieu de mettre l'élément en collision dans le prochain indice disponible, on essaye de placer l'element selon la séquence d'indice suivant : i, i + 1, i + 4, i + 9, i + 16 , ... `, où `i` est le hash original de la clé.


- Insertion: hacher la clé pour obtenir l'indice dans le tableau. S'il n'y a rien, stocker l'objet. S'il y a déjà un élément, suivre la séquence de sondage jusqu'à ce qu'un seau vide soit trouvé et insérez-le.
- Recherche: hasher la clé pour obtenir l'indice dans le tableau, suivre la séquence de sondage jusqu'a ce que la clef de l'element courrant soit egal a la clef de recherche ou a «NULL», retourner la valeur correspondante.
- Supprimer: Comme nous ne pouvons pas dire si l'élément que nous supprimons fait partie d'une chaîne de collision, nous ne pouvons donc pas supprimer l'élément. Au lieu de cela, nous le classons simplement comme supprimé.

La sondage quadratique réduit, mais ne supprime pas, les problemes de performances.

#### Le double hachage

Le double hachage vise à résoudre les problèmes des sondages linéaire et quadratique. Pour ce faire, nous utilisons une deuxième fonction hash pour choisir un nouvel indice pour l'élément. C'est la méthode que nous mettons en œuvre dans ce tutoriel.

[Table des matières](/.translations/fr/README.md#contents)
