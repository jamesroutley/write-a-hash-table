# Apéndice: manejo alternativo de colisiones

Hay dos métodos comunes para manejar colisiones en tablas hash:

- Encadenamiento separado
- Direccionamiento abierto

### Encadenamiento separado

Bajo el encadenamiento separado, cada cubeta contiene una lista enlazada. Cuando los elementos colisionan, se añaden a la lista. Métodos:

- Insertar: hashear la clave para obtener el índice de la cubeta. Si no hay nada en esa cubeta, almacenar el elemento ahí. Si ya hay un elemento ahí, añadir el elemento a la lista enlazada.
- Buscar: hashear la clave para obtener el índice de la cubeta. Recorrer la lista enlazada, comparando la clave de cada elemento con la clave de búsqueda. Si se encuentra la clave, devolver el valor, de lo contrario devolver `NULL`.
- Eliminar: hashear la clave para obtener el índice de la cubeta. Recorrer la lista enlazada, comparando la clave de cada elemento con la clave a eliminar. Si se encuentra la clave, remover el elemento de la lista enlazada. Si solo hay un elemento en la lista enlazada, colocar el puntero `NULL` en la cubeta, para indicar que está vacía.

Esto tiene la ventaja de ser simple de implementar, pero es ineficiente en espacio. Cada elemento también debe almacenar un puntero al siguiente elemento en la lista enlazada, o el puntero `NULL` si no hay elementos después de él. Este es espacio desperdiciado en contabilidad, que podría gastarse en almacenar más elementos.

### Direccionamiento abierto

El direccionamiento abierto busca resolver la ineficiencia de espacio del encadenamiento separado. Cuando ocurren colisiones, el elemento colisionado se coloca en alguna otra cubeta de la tabla. La cubeta en la que se coloca el elemento se elige según alguna regla predeterminada, que puede repetirse al buscar el elemento. Hay tres métodos comunes para elegir la cubeta en la que insertar un elemento colisionado.

#### Sondeo lineal

Cuando ocurre una colisión, el índice se incrementa y el elemento se pone en la siguiente cubeta disponible en el arreglo. Métodos:

- Insertar: hashear la clave para encontrar el índice de la cubeta. Si la cubeta está vacía, insertar el elemento ahí. Si no está vacía, incrementar repetidamente el índice hasta encontrar una cubeta vacía, e insertar ahí.
- Buscar: hashear la clave para encontrar el índice de la cubeta. Incrementar repetidamente el índice, comparando la clave de cada elemento con la clave de búsqueda, hasta encontrar una cubeta vacía. Si se encuentra un elemento con una clave coincidente, devolver el valor, de lo contrario devolver `NULL`.
- Eliminar: hashear la clave para encontrar el índice de la cubeta. Incrementar repetidamente el índice, comparando la clave de cada elemento con la clave a eliminar, hasta encontrar una cubeta vacía. Si se encuentra un elemento con una clave coincidente, eliminarlo. Eliminar este elemento rompe la cadena, así que no tenemos más opción que reinsertar todos los elementos en la cadena después del elemento eliminado.

El sondeo lineal ofrece buen [rendimiento de caché](https://es.wikipedia.org/wiki/Cercan%C3%ADa_de_referencias), pero sufre de problemas de agrupamiento. Poner elementos colisionados en la siguiente cubeta disponible puede llevar a largos tramos contiguos de cubetas llenas, que necesitan ser iterados al insertar, buscar o eliminar.

#### Sondeo cuadrático

Similar al sondeo lineal, pero en lugar de poner el elemento colisionado en la siguiente cubeta disponible, intentamos ponerlo en las cubetas cuyos índices siguen la secuencia: `i, i + 1, i + 4, i + 9, i + 16, ...`, donde `i` es el hash original de la clave. Métodos:

- Insertar: hashear la clave para encontrar el índice de la cubeta. Seguir la secuencia de sondeo hasta encontrar una cubeta vacía o eliminada, e insertar el elemento ahí.
- Buscar: hashear la clave para encontrar el índice de la cubeta. Seguir la secuencia de sondeo, comparando la clave de cada elemento con la clave de búsqueda hasta encontrar una cubeta vacía. Si se encuentra una clave coincidente, devolver el valor, de lo contrario devolver `NULL`.
- Eliminar: no podemos saber si el elemento que estamos eliminando es parte de una cadena de colisiones, así que no podemos eliminar el elemento directamente. En su lugar, simplemente lo marcamos como eliminado.

El sondeo cuadrático reduce, pero no elimina, el agrupamiento, y aún ofrece un rendimiento de caché decente.

#### Hash doble

El hash doble busca resolver el problema de agrupamiento. Para hacerlo, usamos una segunda función hash para elegir un nuevo índice para el elemento. Usar una función hash nos da una nueva cubeta, cuyo índice debería estar distribuido uniformemente entre todas las cubetas. Esto elimina el agrupamiento, pero también elimina cualquier mejora de rendimiento de caché por localidad de referencia. El hash doble es un método común de manejo de colisiones en tablas hash de producción, y es el método que implementamos en este tutorial.
