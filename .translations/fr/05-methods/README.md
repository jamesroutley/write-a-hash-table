# Méthodes de la table de Hachage

Notre table de hachage implémentera l'API suivante:

```c
// hash_table.h
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
```

## Insertion

Pour insérer une nouvelle paire clé-valeur, nous calculons l'index associé à la clef. Si l'index est déja utilisé dans le tableau, on itère jusqu'à ce que l'on trouve un emplacement disponible.

L'attribut `count` sera utile lorsque nous regarderons le [redimensionnement](../06-resizing) dans la section suivante.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}
```

## Search

La recherche est similaire à l'insertion, mais à chaque itération de la boucle `while`, nous vérifions si la clef de l'élément correspond à la clef que nous recherchons.

Si c'est le cas, nous renvoyons la valeur de l'objet. Si la boucle while rencontre une valeur «NULL», nous renvoyons «NULL», pour indiquer qu'aucune valeur n'a été trouvée.

```c
// hash_table.c
char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    return NULL;
}
```

## Delete

La suppression est plus compliquée que l'insertion ou la recherche. L'élément que nous souhaitons supprimer peut faire partie d'une chaîne de collision. L'enlever de la table va rompre cette chaîne et rendra impossible la recherche d'éléments. Pour résoudre ce problème, au lieu de supprimer l'élément, on le marque simplement comme supprimé.

Nous marquons un élément comme supprimé en le remplaçant par un pointeur vers un élément global qui représente un élément supprimé.

```c
// hash_table.c
static ht_item HT_DELETED_ITEM = {NULL, NULL};


void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}
```

Après la suppression, nous décrémentons l'attribut `count` de la table de hachage.

Nous devons également modifier les fonctions `ht_insert` et `ht_search` pour prendre en compte les nœuds supprimés.

Lors de la recherche, nous ignorons et «sautons» les nœuds supprimés. Lors de l'insertion, si nous atteignons un noeud supprimé, nous pouvons insérer le nouveau nœud dans l'emplacement supprimé.


```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // ...
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        // ...
    }
    // ...
}


char* ht_search(ht_hash_table* ht, const char* key) {
    // ...
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        // ...
    }
    // ...
}
```

## Mise à jour

Notre table de hachage ne supporte actuellement pas la mise à jour de la valeur d'une clé. Si nous insérons deux éléments avec la même clé, les clés entreront en collision et le deuxième élément sera inséré dans le prochain indice disponible. Lorsque l'on recherchera la clé, la clé d'origine sera toujours trouvée, et nous ne pourrons pas accéder au deuxième élément.

Nous pouvons corriger celà en modifiant `ht_insert` pour faire en sorte de supprimer l'élément précédent et insérer le nouvel élément à son emplacement.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // ...
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        // ...
    }
    // ...
}
```

Prochaine section: [Redimensionnement de la table de Hachage](../06-resizing)

[Table des matières](/.translations/fr/README.md#contents)
