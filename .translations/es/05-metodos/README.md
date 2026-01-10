# Métodos

Nuestra función hash implementará la siguiente API:

```c
// hash_table.h
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
```

## Insertar

Para insertar un nuevo par clave-valor, iteramos a través de los índices hasta encontrar una cubeta vacía. Luego insertamos el elemento en esa cubeta e incrementamos el atributo `count` de la tabla hash, para indicar que se ha añadido un nuevo elemento. El atributo `count` de una tabla hash será útil cuando veamos el [redimensionamiento](../06-redimensionamiento/README.md) en la siguiente sección.

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

## Buscar

La búsqueda es similar a la inserción, pero en cada iteración del bucle `while`, verificamos si la clave del elemento coincide con la clave que estamos buscando. Si coincide, devolvemos el valor del elemento. Si el bucle while encuentra una cubeta `NULL`, devolvemos `NULL`, para indicar que no se encontró ningún valor.

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

## Eliminar

Eliminar de una tabla hash con direccionamiento abierto es más complicado que insertar o buscar. El elemento que deseamos eliminar puede ser parte de una cadena de colisiones. Removerlo de la tabla romperá esa cadena, y hará imposible encontrar elementos en la cola de la cadena. Para resolver esto, en lugar de eliminar el elemento, simplemente lo marcamos como eliminado.

Marcamos un elemento como eliminado reemplazándolo con un puntero a un elemento centinela global que representa que una cubeta contiene un elemento eliminado.

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

Después de eliminar, decrementamos el atributo `count` de la tabla hash.

También necesitamos modificar las funciones `ht_insert` y `ht_search` para tener en cuenta los nodos eliminados.

Al buscar, ignoramos y 'saltamos' los nodos eliminados. Al insertar, si encontramos un nodo eliminado, podemos insertar el nuevo nodo en el espacio eliminado.

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

## Actualizar

Nuestra tabla hash actualmente no soporta actualizar el valor de una clave. Si insertamos dos elementos con la misma clave, las claves colisionarán, y el segundo elemento será insertado en la siguiente cubeta disponible. Al buscar la clave, la clave original siempre será encontrada, y no podremos acceder al segundo elemento.

Podemos arreglar esto modificando `ht_insert` para eliminar el elemento anterior e insertar el nuevo elemento en su ubicación.

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

Siguiente sección: [Redimensionamiento de tablas](../06-redimensionamiento/README.md)
[Tabla de contenidos](https://github.com/jamesroutley/write-a-hash-table#contents)
