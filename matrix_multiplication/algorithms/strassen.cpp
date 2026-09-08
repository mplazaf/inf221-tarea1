// CPP program to implement Strassen’s Matrix
// sacado de: gemini ai
#include <bits/stdc++.h>
#include "algorithms.h"
#include <iostream>
#include <vector>

using namespace std;

// Helper function to add two matrices
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Helper function to subtract two matrices
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B, int size) {
    vector<vector<int>> C(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}
// Strassen's Algorithm
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, int n) {
    // Base case: If matrix is 1x1
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2; // Size of submatrices

    // Initialize submatrices
    vector<vector<int>> a11(k, vector<int>(k)), a12(k, vector<int>(k)), a21(k, vector<int>(k)), a22(k, vector<int>(k));
    vector<vector<int>> b11(k, vector<int>(k)), b12(k, vector<int>(k)), b21(k, vector<int>(k)), b22(k, vector<int>(k));

    // Divide matrices into 4 quadrants
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
        }
    }

    // Calculate P1 to P7 intermediate products
    auto p1 = strassen(add(a11, a22, k), add(b11, b22, k), k);
    auto p2 = strassen(add(a21, a22, k), b11, k);
    auto p3 = strassen(a11, subtract(b12, b22, k), k);
    auto p4 = strassen(a22, subtract(b21, b11, k), k);
    auto p5 = strassen(add(a11, a12, k), b22, k);
    auto p6 = strassen(subtract(a21, a11, k), add(b11, b12, k), k);
    auto p7 = strassen(subtract(a12, a22, k), add(b21, b22, k), k);
    // Calculate resulting quadrants C11, C12, C21, C22
    auto c11 = add(subtract(add(p1, p4, k), p5, k), p7, k);
    auto c12 = add(p3, p5, k);
    auto c21 = add(p2, p4, k);
    auto c22 = add(subtract(add(p1, p3, k), p2, k), p6, k);
    // Combine quadrants into a single result matrix C
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = c11[i][j];
            C[i][j + k] = c12[i][j];
            C[i + k][j] = c21[i][j];
            C[i + k][j + k] = c22[i][j];
        }
    }
    return C;
}
