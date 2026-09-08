#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <cstdio>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

typedef long long lld ;

vector<vector<int>> matrix_multiplication(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, int n);
#endif 
