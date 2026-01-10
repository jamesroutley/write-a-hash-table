# Función hash

En esta sección, escribiremos nuestra función hash.

La función hash que elijamos debe:

- Tomar una cadena como entrada y devolver un número entre `0` y `m`, la longitud deseada de nuestro arreglo de cubetas.
- Devolver una distribución uniforme de índices de cubetas para un conjunto promedio de entradas. Si nuestra función hash está distribuida de manera desigual, pondrá más elementos en algunas cubetas que en otras. Esto llevará a una mayor tasa de [colisiones](#datos-patológicos). Las colisiones reducen la eficiencia de nuestra tabla hash.

## Algoritmo

Haremos uso de una función hash de cadenas genérica, expresada a continuación en pseudocódigo.

```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```

Esta función hash tiene dos pasos:

1. Convertir la cadena a un entero grande
2. Reducir el tamaño del entero a un rango fijo tomando su resto `mod` `m`

La variable `a` debe ser un número primo mayor que el tamaño del alfabeto. Estamos hasheando cadenas ASCII, que tiene un tamaño de alfabeto de 128, así que deberíamos elegir un primo mayor que ese.

`char_code` es una función que devuelve un entero que representa el carácter. Usaremos códigos de caracteres ASCII para esto.

Probemos la función hash:

```
hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
hash = 5
```

Cambiar el valor de `a` nos da una función hash diferente.

```
hash("cat", 163, 53) = 3
```

## Implementación

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

## Datos patológicos

Una función hash ideal siempre devolvería una distribución uniforme. Sin embargo, para cualquier función hash, existe un conjunto 'patológico' de entradas, que todas hashean al mismo valor. Para encontrar este conjunto de entradas, ejecuta un conjunto grande de entradas a través de la función. Todas las entradas que hashean a una cubeta particular forman un conjunto patológico.

La existencia de conjuntos de entrada patológicos significa que no hay funciones hash perfectas para todas las entradas. Lo mejor que podemos hacer es crear una función que funcione bien para el conjunto de datos esperado.

Las entradas patológicas también representan un problema de seguridad. Si una tabla hash es alimentada con un conjunto de claves que colisionan por algún usuario malicioso, entonces las búsquedas de esas claves tomarán mucho más tiempo (`O(n)`) de lo normal (`O(1)`). Esto puede usarse como un ataque de denegación de servicio contra sistemas que están sustentados por tablas hash, como DNS y ciertos servicios web.

Siguiente sección: [Manejo de colisiones](/04-manejo-colisiones/README.md)
[Tabla de contenidos](https://github.com/jamesroutley/write-a-hash-table#contents)
