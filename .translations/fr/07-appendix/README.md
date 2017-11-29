# Annexe : Gestion alternative de collisions

Il existe deux méthodes principales pour traiter les collisions dans les tables de hachage :

- Le chaînage
- L'adressage ouvert

### Le chaînage

Avec cette méthode, chaque valeur de la table de hachage constitue une liste chainée. Lorsque les éléments entrent en collision, ils sont ajoutés à la liste courante. Méthodes:

- Insertion: hacher la clé pour obtenir l'indice dans le tableau. S'il n'y a rien, stocker l'objet. S'il y a déjà un élément, ajouter l'élément à la liste liée.
- Recherche: hacher la clé pour obtenir l'indice dans le tableau. Parcourir la liste chainée en comparant la clé de chaque élément à la clé de recherche. Si la clé est trouvée, renvoyer la valeur, sinon retourner «NULL».
- Supprimer: hacher la clé pour obtenir l'indice dans le tableau. Parcourir la liste chainée en comparant la clé de chaque élément à la clé de recherche. Si la clé est trouvée, supprimer l'élément de la liste liée. S'il n'y a qu'un seul élément dans la liste liée, mettre un pointeur `NULL`

Cela a l'avantage d'être simple à mettre en œuvre, mais c'est couteux : Chaque élément doit stocker un pointeur vers l'élément suivant dans la liste ou vers le pointeur `NULL`. Cela consomme donc de l'espace.

### L'adressage ouvert

L'adressage ouvert vise à résoudre le problème de consommation d'espace du chainage. Quand des collisions se produisent, l'élément en collision est placé dans un autre indice du tableau.
Il existe 3 méthodes pour calculer l'indice du tableau dans lequel stocker la valeur en collision.

#### Le sondage linéaire

Lorsqu'une collision se produit, l'index est incrémenté et l'élément est placé dans le prochain indice disponible dans le tableau. Méthodes:

- Insertion: hacher la clé pour obtenir l'indice dans le tableau. S'il n'y a rien, stocker l'objet. S'il y a déjà un élément, incrémenter l'indice plusieurs fois jusqu'au prochain emplacement vide et y insérer l'élément.
- Recherche: hacher la clé pour obtenir l'indice dans le tableau, incrementer l'indice jusqu'à ce que la clef de l'élément courant soit égal à la clef de recherche ou à «NULL». Retourner la valeur correspondante.
- Supprimer: hacher la clé pour obtenir l'indice dans le tableau, incrementer l'indice jusqu'à ce que la clef de l'élément courant soit égal a la clef de recherche ou a «NULL». Supprimer la valeur correspondante. La suppression de cet élément brise la chaîne, il faut donc réinsérer tous les éléments de la chaîne après l'élément supprimé.

Le sondage linéaire offre de bonnes [performances de cache](https://en.wikipedia.org/wiki/Locality_of_reference), mais souffre de problèmes de performance d'aggrégation des données (clustering). La présence de nombreuses collisions peut provoquer de nombreuses itérations lors de l'insertion, la recherche ou la suppression.

#### Le sondage quadratique

Similaire au sondage linéaire, mais au lieu de mettre l'élément en collision dans le prochain indice disponible, on essaye de placer l'élément selon la séquence d'indices suivants : i, i + 1, i + 4, i + 9, i + 16 , ... `, où `i` est le hach original de la clé.

- Insertion: hacher la clé pour obtenir l'indice dans le tableau. S'il n'y a rien, stocker l'objet. S'il y a déjà un élément, suivre la séquence de sondage jusqu'à ce qu'un emplacement vide soit trouvé et y insérer l'élément.
- Recherche: hacher la clé pour obtenir l'indice dans le tableau, suivre la séquence de sondage jusqu'à ce que la clef de l'élément courant soit égale à la clef de recherche ou à «NULL», retourner la valeur correspondante.
- Supprimer: Comme nous ne pouvons pas dire si l'élément que nous supprimons fait partie d'une chaîne de collisions, nous ne pouvons donc pas supprimer l'élément. Au lieu de cela, nous le classons simplement comme supprimé.

Le sondage quadratique réduit, mais ne supprime pas, les problèmes de performance.

#### Le double hachage

Le double hachage vise à résoudre les problèmes des sondages linéaire et quadratique. Pour le mettre en place, nous utilisons une deuxième fonction hach pour choisir un nouvel indice pour l'élément. C'est la méthode que nous mettons en œuvre dans ce tutoriel.

[Table des matières](/.translations/fr/README.md#contents)
