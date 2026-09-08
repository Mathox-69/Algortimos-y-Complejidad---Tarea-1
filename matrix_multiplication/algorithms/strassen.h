#ifndef STRASSEN_H
#define STRASSEN_H
#include <vector>
using namespace std;


void strassen_matrix_multiplication(const vector<vector<int>>&A,const vector<vector<int>>&B, vector<vector<int>>&C,int n);

#endif