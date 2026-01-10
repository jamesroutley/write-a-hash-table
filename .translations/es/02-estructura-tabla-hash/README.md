# Estructura de la tabla hash

Nuestros pares clave-valor (elementos) se almacenarán cada uno en una `struct`:

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

Nuestra tabla hash almacena un arreglo de punteros a elementos, y algunos detalles sobre su tamaño y qué tan llena está:

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```

## Inicialización y eliminación

Necesitamos definir funciones de inicialización para `ht_item`s. Esta función asigna un bloque de memoria del tamaño de un `ht_item`, y guarda una copia de las cadenas `k` y `v` en el nuevo bloque de memoria. La función está marcada como `static` porque solo será llamada por código interno de la tabla hash.

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

`ht_new` inicializa una nueva tabla hash. `size` define cuántos elementos podemos almacenar. Esto está fijado en 53 por ahora. Expandiremos esto en la sección sobre [redimensionamiento](/06-resizing). Inicializamos el arreglo de elementos con `calloc`, que llena la memoria asignada con bytes `NULL`. Una entrada `NULL` en el arreglo indica que la cubeta está vacía.

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

También necesitamos funciones para eliminar `ht_item`s y `ht_hash_tables`, que liberan (`free`) la memoria que hemos asignado, para no causar [fugas de memoria](https://en.wikipedia.org/wiki/Memory_leak).

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

Hemos escrito código que define una tabla hash, y nos permite crear y destruir una. Aunque no hace mucho en este punto, aún podemos probarlo.

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

Siguiente sección: [Funciones hash](/03-funcion-hash/README.md) 
[Tabla de contenidos](https://github.com/jamesroutley/write-a-hash-table#contents)
