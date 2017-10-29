# Structure d'une table de hachage

Nos paires de clé-valeur (éléments) seront stockées chacune dans une `struct`:

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

Notre table de hachage stocke un tableau de pointeurs sur éléments et des détails sur sa taille et son contenu :

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```

## Initialisation et suppression

Nous devons définir les fonctions d'initialisation pour la structure `ht_item`.

La fonction suivante alloue une partie de la mémoire à la taille d'un `ht_item` et enregistre une copie des chaînes `k` et `v` dans ce bout de mémoire. La fonction est marquée comme «statique» car elle ne sera appelée que par du code interne à la table de hachage.

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

La fonction `ht_new`, quand à elle, initialise une nouvelle table de hachage avec une valeur `size` qui correspond au nombre d'éléments que nous pouvons stocker (53 actuellement). Nous étendrons ceci dans la section sur le [redimensionnement](/06-redimensionnement).

Nous initialisons le tableau d'éléments avec la fonction `calloc`, qui remplit la mémoire allouée avec les octets `NULL`. Une entrée «NULL» dans le tableau indique que l'élément est vide.

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

Nous avons également besoin de fonctions pour supprimer des `ht_item`s et des `ht_hash_tables`. Ces fonctions libèrent la mémoire que nous avons allouée, donc nous ne causons pas de [fuites de mémoire](https://fr.wikipedia.org/wiki/Fuite_de_m%C3%A9moire).

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

Nous avons écrit du code qui définit une table de hachage. Nous pouvons maintenant en instancier et détruire une.
Même si cela ne fait pas grand chose à ce stade, nous pouvons tout de même l'essayer :

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

Section suivante: [Fonction de hachage](../03-hashing)

[Table des matières](/.translations/fr/README.md#contents)
