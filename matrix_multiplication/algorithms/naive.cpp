#include "algorithms.h"
#include <vector>
using namespace std;

// sacado de:
// https://github.com/Dev-XYS/Algorithms/blob/master/Matrix-Multiplication(Naive).cpp
// modificado para recibir cualquier matriz.

vector<vector<int>> matrix_multiplication(const vector<vector<int>>& A,const vector<vector<int>>& B){
  int m = A.size();
  int p = A[0].size();
  int n = B[0].size();
  vector<vector<int>> R(m, vector<int>(n, 0));

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < p; k++) {
        R[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return R;
}
