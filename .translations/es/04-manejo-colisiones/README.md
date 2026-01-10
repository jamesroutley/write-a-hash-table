## Manejo de colisiones

Las funciones hash mapean un número infinitamente grande de entradas a un número finito de salidas. Diferentes claves de entrada mapearán al mismo índice del arreglo, causando colisiones de cubetas. Las tablas hash deben implementar algún método para manejar las colisiones.

Nuestra tabla hash manejará las colisiones usando una técnica llamada direccionamiento abierto con hash doble. El hash doble hace uso de dos funciones hash para calcular el índice donde un elemento debe almacenarse después de `i` colisiones.

Para una visión general de otros tipos de resolución de colisiones, consulta el [apéndice](/07-appendix).

## Hash doble

El índice que debe usarse después de `i` colisiones está dado por:

```
index = hash_a(string) + i * hash_b(string) % num_buckets
```

Vemos que si no han ocurrido colisiones, `i = 0`, entonces el índice es simplemente `hash_a` de la cadena. Si ocurre una colisión, el índice es modificado por `hash_b`.

Es posible que `hash_b` devuelva 0, reduciendo el segundo término a 0. Esto causará que la tabla hash intente insertar el elemento en la misma cubeta una y otra vez. Podemos mitigar esto añadiendo 1 al resultado del segundo hash, asegurándonos de que nunca sea 0.

```
index = (hash_a(string) + i * (hash_b(string) + 1)) % num_buckets
```

## Implementación

```c
// hash_table.c
static int ht_get_hash(
    const char* s, const int num_buckets, const int attempt
) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
```

Siguiente sección: [Métodos de la tabla hash](../05-metodos/README.md)
[Tabla de contenidos](https://github.com/jamesroutley/write-a-hash-table#contents)
