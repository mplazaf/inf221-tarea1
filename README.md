# Documentación
Nombre: Miguel Plaza
Rol: 202473058-4
Semestre: 2026-2

## Multiplicación de matrices
- Las fuentes de dónde fueron extraidos los algoritmos están en sus archivos cpp.
- Se usa un archivo algorithms.h para importar todos los algoritmos a matrix_multiplication.cpp
- En matrix_multiplication.cpp, al principio hay arreglos definidos que tienen los posibles valores de n,t,d,m. Por ejemplo si desea sacar mediciones sólo hasta matrices de tamaño 256, modifique el arreglo "tamanos", quitándole el 1024.
- En los bucles "for", las mediciones para cada algoritmo están separadas por bloques de código entre {}. Si por ejemplo sólo quiere hacer mediciones para Strassen, comente el bloque de Naive {auto inicio... cout<<"listo naive"}.

### Programa principal
- Compilación: escribir en terminal "make". Use "make clear" para eliminar el ejecutable.
- Ejecución: escribir el comando en terminal "./matrix".
- Al ejecutarse, los resultados serán guardados en data/measurements
### Scripts
- Para ejecutar los archivos de la carpeta scripts, ejecute el comando "python3 nombrearchivo.py"
- Tras ejecutar "python3 matrix_generator.py", los archivos serán guardados en el directorio data/matrix_input
-  Tras ejecutar "python3 plot_generator.py", los archivos serán guardados en el directorio data/matrix_input data/plots

## Ordenamiento de arreglo unidimensional
- Las fuentes de dónde fueron extraidos los algoritmos están en sus archivos cpp.
- Se usa un archivo algorithms.h para importar todos los algoritmos a sorting.cpp
- De igual forma que en matrix_multiplication.cpp, al inicio del archivo hay arreglos con las combinaciones de n,t,d,m.
- Cada medicion también está separada por bloques de código entre {}

### Programa principal
- Compilación: escribir en terminal "make". Use "make clear" para eliminar el ejecutable.
- Ejecución: escribir el comando en terminal "./sorting".
- Al ejecutarse, los resultados serán guardados en data/measurements
-
### Scripts
Lo mismo que para matrix
