# Redimensionamiento

Actualmente, nuestra tabla hash tiene un número fijo de cubetas. A medida que se insertan más elementos, la tabla comienza a llenarse. Esto es problemático por dos razones:

1. El rendimiento de la tabla hash disminuye con altas tasas de colisiones
2. Nuestra tabla hash solo puede almacenar un número fijo de elementos. Si intentamos almacenar más que eso, la función de inserción fallará.

Para mitigar esto, podemos aumentar el tamaño del arreglo de elementos cuando se llena demasiado. Almacenamos el número de elementos guardados en la tabla hash en el atributo `count` de la tabla. En cada inserción y eliminación, calculamos la 'carga' de la tabla, o la proporción de cubetas llenas respecto al total de cubetas. Si sube o baja de ciertos valores, redimensionamos el arreglo hacia arriba o hacia abajo.

Redimensionaremos:

- hacia arriba, si la carga > 0.7
- hacia abajo, si la carga < 0.1

Para redimensionar, creamos una nueva tabla hash aproximadamente el doble o la mitad del tamaño de la actual, e insertamos todos los elementos no eliminados en ella.

El tamaño de nuestro nuevo arreglo debe ser un número primo aproximadamente el doble o la mitad del tamaño actual. Encontrar el nuevo tamaño del arreglo no es trivial. Para hacerlo, almacenamos un tamaño base, que queremos que tenga el arreglo, y luego definimos el tamaño real como el primer primo mayor que el tamaño base. Para redimensionar hacia arriba, duplicamos el tamaño base, y encontramos el primer primo mayor, y para redimensionar hacia abajo, dividimos el tamaño a la mitad y encontramos el siguiente primo mayor.

Nuestros tamaños base comienzan en 50.

Usamos un método de fuerza bruta para encontrar el siguiente primo, verificando si cada número sucesivo es primo. Aunque la fuerza bruta suena alarmante, el número de valores que realmente tenemos que verificar es bajo, y el tiempo que toma es superado por el tiempo dedicado a re-hashear cada elemento en la tabla.

Primero, definamos una función para encontrar el siguiente primo. Haremos esto en dos nuevos archivos, `prime.h` y `prime.c`.

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
 * Devuelve si x es primo o no
 *
 * Retorna:
 *   1  - primo
 *   0  - no primo
 *   -1 - indefinido (es decir, x < 2)
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
 * Devuelve el siguiente primo después de x, o x si x es primo
 */
int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
```

A continuación, necesitamos actualizar nuestra función `ht_new` para soportar la creación de tablas hash de un cierto tamaño. Para hacer esto, crearemos una nueva función, `ht_new_sized`. Cambiamos `ht_new` para llamar a `ht_new_sized` con el tamaño inicial predeterminado.

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

Ahora tenemos todas las partes que necesitamos para escribir nuestra función de redimensionamiento.

En nuestra función de redimensionamiento, verificamos para asegurarnos de que no estamos intentando reducir el tamaño de la tabla hash por debajo de su mínimo. Luego inicializamos una nueva tabla hash con el tamaño deseado. Todos los elementos que no son `NULL` ni eliminados se insertan en la nueva tabla hash. Después intercambiamos los atributos de las tablas hash nueva y antigua antes de eliminar la antigua.

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

    // Para eliminar new_ht, le damos el size e items de ht 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}
```

Para simplificar el redimensionamiento, definimos dos pequeñas funciones para redimensionar hacia arriba y hacia abajo.

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

Para realizar el redimensionamiento, verificamos la carga de la tabla hash en las inserciones y eliminaciones. Si está por encima o por debajo de los límites predefinidos de 0.7 y 0.1, redimensionamos hacia arriba o hacia abajo respectivamente.

Para evitar hacer matemáticas de punto flotante, multiplicamos el conteo por 100, y verificamos si está por encima o por debajo de 70 o 10.

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

Siguiente sección: [Apéndice](/07-apendice/README.md)
[Tabla de contenidos](https://github.com/jamesroutley/write-a-hash-table#contents)
