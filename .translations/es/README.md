# Escribe una tabla hash en C

Las [tablas hash](https://en.wikipedia.org/wiki/Hash_table) son una de las estructuras de datos más útiles. Su inserción, búsqueda y eliminación rápidas y escalables las hacen relevantes para una gran cantidad de problemas de ciencias de la computación.

En este tutorial, implementamos una tabla hash con [direccionamiento abierto](https://en.wikipedia.org/wiki/Open_addressing) y [hash doble](https://en.wikipedia.org/wiki/Double_hashing) en C. Al trabajar con este tutorial, obtendrás:

- Comprensión de cómo funciona una estructura de datos fundamental por debajo
- Conocimiento más profundo de cuándo usar tablas hash, cuándo no usarlas, y cómo pueden fallar
- Exposición a nuevo código en C

C es un gran lenguaje para escribir una tabla hash porque:

- El lenguaje no viene con una incluida
- Es un lenguaje de bajo nivel, por lo que obtienes una exposición más profunda a cómo funcionan las cosas a nivel de máquina

Este tutorial asume cierta familiaridad con programación y sintaxis de C. El código en sí es relativamente sencillo, y la mayoría de los problemas deberían ser resolubles con una búsqueda web. Si encuentras más problemas, por favor abre un [Issue](https://github.com/jamesroutley/write-a-hash-table/issues) en GitHub.

La implementación completa tiene alrededor de 200 líneas de código, y debería tomar aproximadamente una o dos horas para completar.

## Contenidos

1. [Introducción](/01-introduccion/README.md)
2. [Estructura de la tabla hash](/02-estructura-tabla-hash/README.md)
3. [Funciones hash](/03-funcion-hash/README.md)
4. [Manejo de colisiones](/04-manejo-colisiones/README.md)
5. [Métodos de la tabla hash](/05-metodos/README.md)
6. [Redimensionamiento de tablas](/06-redimensionamiento/README.md)
7. [Apéndice: manejo alternativo de colisiones](/07-apendice/README.md)

## Créditos

Este tutorial fue escrito por [James Routley](https://twitter.com/james_routley), quien escribe en su blog en [routley.io](https://routley.io).
