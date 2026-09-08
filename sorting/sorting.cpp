#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "algorithms/algorithms.h"
#include <sys/resource.h>
using namespace std;
using namespace std::chrono;

vector<int> sacarArreglo(const string& ruta){
    vector<int> arreglo;
    ifstream archivo(ruta);
    if (!archivo.is_open()){
        cout << "Error al abrir: " << ruta << endl;
        return arreglo; 
    }
    int numero;
    while (archivo >> numero){
        arreglo.push_back(numero);    
    }
    archivo.close();
    return arreglo;
}

void guardarArreglo(const string& ruta, const vector<int>& arr){
    ofstream archivo(ruta);

    for (int i : arr){
        archivo << i << " ";
    }
    archivo.close();
}  

vector<int> tamanos = {10, 1000, 100000}; //10 000 000
vector<string> tipos = {"ascendente","descendente","aleatorio"};
vector<string> dominios = {"D1","D7"};
vector<char> muestras ={'a','b','c'};


const string rutaOut = "data/array_output/10_aleatorio_D1_a_out.txt";

long long memoriaMaximaKB(){
    struct rusage uso;
    getrusage(RUSAGE_SELF, &uso);
    return uso.ru_maxrss; 
}

int main(){
  ofstream archivoMerge("data/measurements/mergesort.csv");
  ofstream archivoQuick("data/measurements/quicksort.csv");
  ofstream archivoPatience("data/measurements/patiencesort.csv");
  ofstream archivoSort("data/measurements/sort.csv");

  for (int n : tamanos){
    for (const string& tipo : tipos){
      for (const string& dominio : dominios){
        for (char muestra : muestras){

          string nombreArchivoIn =to_string(n) + "_" +tipo + "_" +dominio + "_" +string(1, muestra) +".txt";
          string nombreArchivoOut = to_string(n) + "_" +tipo + "_" +dominio + "_" +string(1, muestra) +"_out.txt"; 
          string rutaInput ="data/array_input/" + nombreArchivoIn;
          const string rutaOut  ="data/array_output/"+nombreArchivoOut;
          vector<int> arr =sacarArreglo(rutaInput);
          /*
          {
            vector<int> copia = arr;
            auto inicio = high_resolution_clock::now();

            mergeSort(copia,0,copia.size()-1);
            auto fin = high_resolution_clock::now();

            long long tiempo = duration_cast<microseconds>(fin - inicio).count();
            long long memoria =memoriaMaximaKB();

            guardarArreglo(rutaOut, copia);

            archivoMerge << n << "," << tipo << "," << dominio << "," << muestra << "," 
            << tiempo << "," << memoria << "\n";
          
          }
          */
          {
            vector<int> copia = arr;
            auto inicio = high_resolution_clock::now();

            quickSort(copia,0,copia.size() - 1);
            auto fin = high_resolution_clock::now();
            
            long long tiempo =duration_cast<microseconds>(fin - inicio).count();

            long long memoria = memoriaMaximaKB();

            guardarArreglo(rutaOut, copia);

            archivoQuick << n << "," << tipo << ","<< dominio << "," << muestra << ","
                            << tiempo << "," << memoria << "\n";
          }
          /*
          {
            vector<int> copia = arr;
            auto inicio =high_resolution_clock::now();

            patienceSorting(copia);

            auto fin = high_resolution_clock::now();

            long long tiempo = duration_cast<microseconds>(fin - inicio).count();

            long long memoria = memoriaMaximaKB();
            
            guardarArreglo(rutaOut, copia);

            archivoPatience
                << n << "," << tipo << ","<< dominio << "," << muestra << ","
                << tiempo << "," << memoria << "\n";
          }
          {
            vector<int> copia = arr;
            auto inicio = high_resolution_clock::now();

            sortArray(copia);
            auto fin =high_resolution_clock::now();

            long long tiempo = duration_cast<microseconds>(fin - inicio).count();

            long long memoria = memoriaMaximaKB();

            guardarArreglo(rutaOut, copia);

            archivoSort << n << ","
                << tipo << "," << dominio << "," << muestra << ","
                << tiempo << "," << memoria << "\n";
          }
          */
        }
      }
    }
  }

  archivoMerge.close();
  archivoQuick.close();
  archivoPatience.close();
  archivoSort.close();
  return 0;
}
