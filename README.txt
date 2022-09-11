## TP1: PageRank	

grupo 18 - Arienti, Vekselman, Barcos


### Estructura del repo

- catedra: Los archivos de test provistos para el TP
- implementacion: El código fuente para la solución propuesta, incluye los tests
- experimentos: El material correspondiente a todos los experimentos. Incluye scripts y archivos resultado
- el informe


### Crear el ejecutable:

1. crear una carpeta para los archivos
### Crear el ejecutable para la experimentacion:

desde la raiz del repo:

// nos movemos a ./experimentos
> cd ./experimentos
 
// creamos la carpeta del ejecutable
> mkdir build
    
// entramos
> cd build

// abrimos bash (si en windows)
> bash

// creamos el cmake
$ cmake ../../implementacion

// creamos el ejecutable	
$ make ./pagerank
