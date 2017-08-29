# Structure d'une table de hachage

Nos paires de valeurs-clés (éléments) seront chacune stockées dans une `struct`:

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

Notre table de hashage stocke un tableau de pointeurs sur des éléments et des détails sur sa taille et sa totalité :

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```

## Initialisation et suppression

Nous devons définir les fonctions d'initialisation pour cette structure.

La fonction suivante attribue un morceau de mémoire à la taille d'un `ht_item` et enregistre une copie des chaînes `k` et `v` dans le nouveau morceau de mémoire. La fonction est marquée comme «statique» car elle ne sera appelée que par code interne à la table de hachage.

```c
// hash_table.c
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}
```

La fonction `ht_new`, quand à elle, initialise une nouvelle table de hachage avec une valeur `size` qui correspond au nombre d'élement que nous pouvons stocker (53 pour l'instant). Nous étendrons ceci dans la section sur [redimensionnement](/06-redimensionnement).

Nous initialisons le tableau d'éléments avec `calloc`, qui remplit la mémoire allouée avec les octets `NULL`. Une entrée «NULL» dans le tableau indique que l'élement est vide.

```c
// hash_table.c
ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}
```

Nous avons également besoin de fonctions pour supprimer des `ht_item`s et des `ht_hash_tables`. Ces fonctions liberent la mémoire que nous avons allouée, donc nous ne causons pas de [fuites de mémoire](https://fr.wikipedia.org/wiki/Fuite_de_m%C3%A9moire).

```c
// hash_table.c
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}


void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}
```

Nous avons écrit un code qui définit une table de hash. Nous pouvons en instancier et détruire une.
Même si cela ne fait pas grand chose à ce stade, nous pouvons l'essayer :

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

Next section: [Fonction de hachage](../03-hashing)

[Table des matières](/.translations/fr/README.md#contents)
