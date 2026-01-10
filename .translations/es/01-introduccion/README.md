# Introducción

Una tabla hash es una estructura de datos que ofrece una implementación rápida de la [API](#api) de arreglo asociativo. Como la terminología alrededor de las tablas hash puede ser confusa, he añadido un resumen [más abajo](#terminología).

Una tabla hash consiste en un arreglo de 'cubetas' (buckets), cada una de las cuales almacena un par clave-valor. Para localizar la cubeta donde debe almacenarse un par clave-valor, la clave se pasa a través de una función de hash. Esta función devuelve un entero que se usa como índice del par en el arreglo de cubetas. Cuando queremos recuperar un par clave-valor, proporcionamos la clave a la misma función de hash, recibimos su índice y lo usamos para encontrarlo en el arreglo.

La indexación de arreglos tiene complejidad algorítmica `O(1)`, lo que hace que las tablas hash sean rápidas para almacenar y recuperar datos.

Nuestra tabla hash mapeará claves de tipo cadena a valores de tipo cadena, pero los principios dados aquí son aplicables a tablas hash que mapean tipos de clave arbitrarios a tipos de valor arbitrarios. Solo se soportarán cadenas ASCII, ya que soportar unicode no es trivial y está fuera del alcance de este tutorial.

## API

Los arreglos asociativos son una colección de pares clave-valor no ordenados. No se permiten claves duplicadas. Se soportan las siguientes operaciones:

- `search(a, k)`: devuelve el valor `v` asociado con la clave `k` del arreglo asociativo `a`, o `NULL` si la clave no existe.
- `insert(a, k, v)`: almacena el par `k:v` en el arreglo asociativo `a`.
- `delete(a, k)`: elimina el par `k:v` asociado con `k`, o no hace nada si `k` no existe.

## Configuración

Para configurar C en tu computadora, por favor consulta la guía de [Daniel Holden](/orangeduck) en el libro [Build Your Own Lisp](http://www.buildyourownlisp.com/chapter2_installation). Build Your Own Lisp es un gran libro, y recomiendo trabajar con él.

## Estructura del código

El código debe organizarse en la siguiente estructura de directorios.

```
.
├── build
└── src
    ├── hash_table.c
    ├── hash_table.h
    ├── prime.c
    └── prime.h
```

`src` contendrá nuestro código, `build` contendrá nuestros binarios compilados.

## Terminología

Hay muchos nombres que se usan indistintamente. En este artículo, usaremos los siguientes:

- Arreglo asociativo: una estructura de datos abstracta que implementa la [API](#api) descrita anteriormente. También llamado mapa, tabla de símbolos o diccionario.

- Tabla hash: una implementación rápida de la API de arreglo asociativo que hace uso de una función de hash. También llamada mapa hash, mapa, hash o diccionario.

Los arreglos asociativos pueden implementarse con muchas estructuras de datos subyacentes diferentes. Uno (no eficiente) puede implementarse simplemente almacenando elementos en un arreglo, e iterando a través del arreglo cuando se busca. Los arreglos asociativos y las tablas hash a menudo se confunden porque los arreglos asociativos se implementan tan frecuentemente como tablas hash.

Siguiente sección: [Estructura de la tabla hash](../02-estructura-tabla-hash/README.md)
[Tabla de contenidos](https://github.com/jamesroutley/write-a-hash-table#contents)
