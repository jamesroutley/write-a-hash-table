# Redimensionnement de la table de Hachage

Pour le moment, notre table de hachage a une taille fixe. Plus on insère d'éléments, plus la table se remplit et cela génère les problèmes suivants :

1. La performance de la table de hachage diminue avec des taux élevés de collisions
2. La table ne peut que stocker un nombre fixe d'éléments. Si nous essayons de stocker plus que cela, la fonction d'insertion échouera.

Pour pallier à cela, nous pouvons augmenter la taille du tableau de l'article quand il est trop rempli. Nous enregistrons le nombre d'éléments stockés dans la table de hachage grace à l'attribut `count` de la table. Sur chaque insertion et suppression, nous calculons la «charge» du tableau (nombre d'éléments/nombre total d'éléments). Si ce ratio est supérieur ou inférieur à certaines valeurs, nous redimensionnons le tableau :

- Si le ratio est > 0.7, on l'agrandit
- Si le ratio est < 0.1, on le diminue

Pour redimensionner, nous créons une nouvelle table de hachage ou l'on insère tous les éléments non supprimés.

Notre nouvelle taille doit être un nombre premier correspondant à peu près à deux fois (aggrandissement) ou à la moitié de la taille actuelle (réduction).
Trouver la nouvelle taille de tableau n'est pas trivial. Pour ce faire nous :
    * Stockons une taille de base (commencons par 50)
    * Définissons la taille réelle comme le premier nombre premier plus grand que la taille de base.
    * Doublons la taille de base et trouvons le premier nombre premier plus grand (pour redimensionner vers le bas, on réduit la taille de moitié et trouvons le premier plus grand)


Il faut maintenant une méthode pour trouver le prochain nombre premier suivant un nombre donné en paramètre. Nous utiliserons la force brute en vérifiant un par un tous les nombres qui le suivent.

Nous implementons cela dans deux nouveaux fichiers, `prime.h` et `prime.c`.


```c
// prime.h
int is_prime(const int x);
int next_prime(int x);
```

```c
// prime.c

#include <math.h>

#include "prime.h"


/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int is_prime(const int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if ((x % 2) == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}


/*
 * Return the next prime after x, or x if x is prime
 */
int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
```

Nous devons ensuite mettre à jour notre fonction `ht_new` pour pouvoir créer une table de hachage d'une taille donnée. Pour cela, nous allons créer une nouvelle fonction, `ht_new_sized`.
La fonction `ht_new` ne sera plus qu'un appel à `ht_new_sized` avec une taille de départ fixe.

```c
// hash_table.c
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}


ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}
```

On a maintenant toutes les parties dont nous avons besoin pour écrire notre fonction de redimensionnement :

1. Celle-ci doit vérifier que nous n'essayons pas de réduire la taille de la table de hachage en dessous de son minimum.
2. Nous initialisons ensuite une nouvelle table de hachage avec la taille souhaitée.
3. Tous les éléments non `NULL` et non supprimés sont insérés dans la nouvelle table de hachage.
4. Nous mettons à jour les attributs de la nouvelle table de hachage avec les valeurs de l'ancienne table avant de la détruire.

```c
// hash_table.c
static void ht_resize(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}
```

Pour simplifier le redimensionnement, nous définissons deux fonctions pour redimensionner vers le haut et vers le bas :

```c
// hash_table.c
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
```

Pour effectuer le redimensionnement, nous vérifions le ratio de la table sur l'insertion et la suppression. En fonction de S'il est au-dessus ou au-dessous des limites prédéfinies de 0,7 et 0,1, nous redimensionnons vers le haut ou vers le bas.

Pour éviter de faire des calculs en nombre flottant, nous multiplions le nombre par 100, et vérifions s'il est supérieur ou inférieur à 70 ou 10.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    // ...
}


void ht_delete(ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    // ...
}
```

Prochaine section: [Annexe : Gestion alternative de collisions](../07-appendix)

[Table des matières](/.translations/fr/README.md#contents)
