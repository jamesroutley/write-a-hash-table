# Fonction de hachage

Dans cette section, nous allons écrire notre propre fonction de hachage.

Cette fonction devra :

- Prendre une chaine de charactères en paramètre et retourner un nombre entre `0` et `m` où `m` est la taille de notre tableau d'éléments. Ce nombre servira d'index dans le tableau.
- Renvoyer une distribution uniforme d'indexes pour un ensemble de paramètres d'entrées. Si notre fonction de hachage est inégalement répartie, cela entraînera un taux plus élevé de [collisions](#Données pathologiques). Les collisions réduisent l'efficacité de notre table de hachage.

## Algorithme

Nous utiliserons une fonction de hachage de chaîne générique, exprimée en pseudo code de la manière suivante :

```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```

Cette fonction a deux étape:

1. Convertir la chaîne en un entier large
2. Réduire la taille de l'entier en prenant le reste (modulo la taille du tableau).

La variable `a` doit être un nombre premier supérieur à la taille de l'alphabet utilisé. Nous effectuons nos opérations sur des chaînes ASCII, qui ont une taille d'alphabet de 128.
`char_code` est une fonction qui renvoie un entier qui représente le caractère (ASCII) passé en entrée.

Essayons la fonction de hachage sur les données suivantes:

```
hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
hash = 5
```

Changer la valeur de `a` nous donne une fonction de hachage différente.

```
hash("cat", 163, 53) = 3
```

## Implementation

```c
// hash_table.c
static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}
```

## Données pathologiques

Une fonction de hachage idéale renverrait toujours une distribution uniforme de résultats. Cependant, pour toute fonction de hachage, il existe un ensemble d'entrées «pathologiques», qui aboutit à la même valeur. Pour trouver ces entrées, appliquez la fonction sur un large ensemble d'entrées. Toutes les entrées differentes qui retournent un même résultat forment un ensemble pathologique.

L'existence d'ensembles d'entrées pathologiques signifie qu'il n'existe pas de fonctions de hachage parfaites pour toutes les entrées. Le mieux que nous puissions faire est de créer une fonction qui fonctionne bien pour le jeu de données attendu.

Les entrées pathologiques constituent également un problème de sécurité. Si un utilisateur malveillant remplit une table de hachage avec des données pathologiques, les recherches sur les clefs collisionées prendront beaucoup plus de temps (`O(n)`) que la normale (`O(1)`).
Cela peut être utilisé comme une attaque de déni de service contre les systèmes qui se basent sur des tables de hachage (DNS, web services).

Prochaine section: [Traitement des collisions](../04-collisions)

[Table des matières](/.translations/fr/README.md#contents)
