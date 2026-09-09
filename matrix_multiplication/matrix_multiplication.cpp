#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "algorithms/algorithms.h"
#include <chrono>
#include <sys/resource.h>
using namespace std;

vector<int> tamanos = {16, 64, 256,1024}; //  1024
vector<string> tipos = {"dispersa", "diagonal","densa"};
vector<string> dominios = {"D0","D10"};
vector<char> muestras ={'a','b','c'};


vector<vector<int>> sacarMatriz(const string& ruta, int n){
  vector<vector<int>> matriz(n, vector<int>(n));
  ifstream archivo(ruta);

  if (!archivo.is_open()){
      cout << "Error al abrir: " << ruta << endl;
      return {};
  }
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        archivo >> matriz[i][j];
    }
  }
  archivo.close();
  return matriz;
}

void guardarMatriz(const string& ruta, const vector<vector<int>>& matriz){
  ofstream archivo(ruta);
  if (!archivo.is_open()) {
      cout << "Error al abrir: " << ruta << endl;
      return;
  }
  int i, j;
  for (i=0; i<matriz.size(); i++){
    for(j=0; j<matriz[i].size(); j++){
      archivo << matriz[i][j] << " ";
    }
    archivo << "\n";
  }
}
long long memoriaMaximaKB(){
    struct rusage uso;
    getrusage(RUSAGE_SELF, &uso);
    return uso.ru_maxrss; 
}

int main() {
  ofstream archivoNaive("data/measurements/naive.csv");
  ofstream archivoStrassen("data/measurements/strassen.csv");
  for (int n: tamanos){
    for (const string& tipo : tipos){
      for (const string& dominio : dominios){
        for (char muestra : muestras){
          string nombreArchivoIn1 =to_string(n) + "_" +tipo + "_" +dominio + "_" +string(1, muestra) +"_1.txt";
          string nombreArchivoIn2 =to_string(n) + "_" +tipo + "_" +dominio + "_" +string(1, muestra) +"_2.txt";
          string nombreArchivoOut = to_string(n) + "_" +tipo + "_" +dominio + "_" +string(1, muestra) +"_out.txt"; 
          string rutaInput1 ="data/matrix_input/" + nombreArchivoIn1;
          string rutaInput2 ="data/matrix_input/" + nombreArchivoIn2;
          string rutaOut  ="data/matrix_output/"+nombreArchivoOut;

          vector<vector<int>> matrix1 = sacarMatriz(rutaInput1, n);
          vector<vector<int>> matrix2 = sacarMatriz(rutaInput2, n);

          {
            auto inicio = chrono::high_resolution_clock::now();

            vector<vector<int>> out = matrix_multiplication(matrix1, matrix2);

            auto fin = chrono::high_resolution_clock::now();
            long long tiempo = chrono::duration_cast<chrono::microseconds>(fin-inicio).count();
            long long memoria = memoriaMaximaKB();
            guardarMatriz(rutaOut, out);

            archivoNaive << n << "," << tipo << "," << dominio << "," << muestra << "," 
            << tiempo << "," << memoria << "\n";
            cout << "listo naive "<< n <<endl;
          }

          {
            auto inicio = chrono::high_resolution_clock::now();

            vector<vector<int>> out = strassen(matrix1, matrix2, n);

            auto fin = chrono::high_resolution_clock::now();
            long long tiempo = chrono::duration_cast<chrono::microseconds>(fin-inicio).count();
            long long memoria = memoriaMaximaKB();
            guardarMatriz(rutaOut, out);

            archivoStrassen << n << "," << tipo << "," << dominio << "," << muestra << "," 
            << tiempo << "," << memoria << "\n";
            cout<<"listo " << n << endl;
          }
        }
      }
    }
  }
  return 0;
}
