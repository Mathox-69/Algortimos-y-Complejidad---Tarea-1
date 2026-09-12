# Documentación

## Estudiante
Matías Vallejos Mella

202404586-5
## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices
Algortimos: Naive, Strassen
### Programa principal
matrix_mutiplication.cpp
#### Referencias
* Naive: [link](https://github.com/Mathox-69/Algortimos-y-Complejidad---Tarea-1.git)
* Strassen: [link 1](https://github.com/dmonaldo/strassen-matrix-multiplication/blob/master/main.cpp) y [link 2](https://shivathudi.github.io/jekyll/update/2017/06/15/matr-mult.html)
### Scripts
plot_generator.py, matrix_generator.py

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort.

### Programa principal
sorting.cpp
#### Referencias
* quickSort: [link](https://stackoverflow.com/questions/7198121/quicksort-and-hoare-partition). Con el cambio de que el pivote es aleatorio para que el caso promedio sea de O(nlog(n))
* mergeSort: [link](https://medium.com/@omkareshwarhalli/merge-sort-in-c-code-with-explanation-e20a7988e1c1). Tiene un cambio en la implementacipon, en el uso de un array temporal para minimizar el impacto en el rendimiento que supodnria reservar memoria durante cada llamada recursiva.
* patienceSort: [link](https://rosettacode.org/wiki/Sorting_algorithms/Patience_sort)

### Scripts
plot_generator.py, array_generator.py

## Makefile

Para ejecutar el Makefile respectivo para multiplicación de matrices y de ordenamiento de arreglo unidemensional, se debe ejecutar `make run` en las carpetas `code/matrix_multiplication` y `code/sorting`. Además se ejecutaran el script `plot_generator.py` después de la compilacion y ejecución de los programas principal respectivo.

Para la limpieza de archivos se debe ejecutar `make clean`, que eliminara todos los objetos, outputs, csv y plots generados al usar `make run`. Tambien eliminara los inputs de los arreglos y matrices, por lo que antes de iniciar un `make run` despues de un `make clean`, se debe ejecutar los scripts respectivos de generación para que funcione correctamente.



## Consideración

La ejecución de matrix_multipliation.cpp puede llegar a demorar unos 20 minustos aproximadamente, para rebajar el tiempo de espera significtivamente, en el propio archivo en el apartado de los valores que puede tomar n, se puede quitar el valor de 1024. Haciendo eso, el tiempo de ejecución total baja a unos 40 segundos aproximadamente. Los resultados siguen siendo consistentes en caso de que se opte por quitar o dejar el valor de 1024.

De todas formas el informe esta pensado para la multiplicación de matrices de hasta 1024x1024.
