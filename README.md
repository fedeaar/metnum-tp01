## TP1: PageRank	

grupo 18 - Arienti, Vekselman, Barcos


<br>

### Estructura del repo

La entra cuenta los siguientes archivos y carpetas:

- 'catedra' - Los archivos de test provistos por la cátedra.

- 'implementacion' - El código fuente para la solución propuesta, incluye los casos de test.

- 'experimentos' - El material correspondiente a todos los experimentos mencionados en el trabajo. Incluye scripts y archivos resultado. Se omitieron los archivos intermedios, los mismo se pueden regenerar a partir de los scripts.

- el informe.



<br>

### Nota de entorno

La compilación de los ejecutables se realizó por medio de `CMAKE` y `MAKE` en `WSL (windows)`. Recomendamos utilizar las mismas aplicaciones y trabajar en un entorno de linux. Más abajo explicamos cómo. 

Así también, los scripts se pensaron para ser ejecutados por medio de WSL. De compilar para windows ó de ejecutarse directo en linux se deberán modificar las variables globales al comienzo del archivo `./experimentos/utils/IO.py`. En el mismo se detalla cómo. 



<br>

### Cómo crear los archivos ejecutables

Para este procedimiento se asume que trabajaremos en bash. Desde la raiz del repo procederémos de la siguiente forma

1. creamos la carpeta para los ejecutables
    > $ mkdir build
    
2. nos movemos adentro
    > $ cd build

3. creamos el cmake
    > $ cmake ../implementacion

4. creamos los ejecutables
    
    i. El ejecutable principal (el mismo se requerirá para los experimentos)
    > $ make ./pagerank 

    ii. Para correr los tests de la cátedra (con tolerancia máxima 1e-4).
    > $ make ./TESTS-pagerank-alt 

    iii. Para correr otros tests internos
    > $ make ./TESTS-matriz-alt

5. ejecutar

    > $ ./TESTS-pagerank-alt

    > $ ./TESTS-pagerank-matriz

    > $ ./pagerank ../catedra/test_15_segundos.txt 0.9

Notamos que la ejecución de los experimentos requiere que el ejecutable `./pagerank` se encuentre en `./build`.


<br>

### IO ./pagerank

El ejecutable de pagerank permite trabajar con los siguientes parámetros.


Obligatorios (deben estar en orden):

- `*` fuente del archivo de entrada. El mismo debe estar formateado según las pautas del enunciado. No requiere `"`, no se aceptan nombres con espacio. Ejemplo de uso: `../catedra/tests_15_segundos.txt`.

- `*` valor p a utilizar. El mismo debe estar en el intervalo [0, 1). Se testeó el funcionamiento hasta una cota superior de `1 - 1e-6`. No se garantiza que funcione para aproximaciones más cercanas a 1.


Opcionales:

- `-out` carpeta en la que se guardarán los archivos de salida. Por defecto esta es la misma donde se encuentra el ejecutable. Ejemplo de uso: `-out=../experimentos/`.

- `-save_as` nombre con el que se guardarán los archivos de salida. Por defecto, este nombre será el mismo que el del archivo de entrada pero con una extensión distinta acorde al archivo. Para el archivo solución, esta extensión sera `.out`. Ejemplo de uso: `-save_as=resultado`. 

- `-presicion` la presición con la que se guardaran los resultados, en el sentido de la cantidad de digitos decimales después de la coma. Por defecto 15. Ejemplo de uso: `-presicion=8`.

- `-save_m` Flag. Si se pasa éste parámetro, se guardará la matríz utilizada para la resolución del problema en un archivo con la extensión `.matriz`.

- `-time_it` Flag. Si se pasa éste parámetro, se guardará el tiempo de ejecución del algoritmo de pageRank (descontando las operaciones de IO) en un archivo con la extensión `.time`.

- `-v` Flag. Verbose. Si se pasa éste parámetro, se imprimirá en la consola información durante la ejecución del programa.