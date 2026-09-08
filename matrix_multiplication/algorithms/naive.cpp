// https://cplusplus.algorithmexamples.com/web/Mathematical/Matrix%20Multiplication.html

#include <vector>
using namespace std;

void naive_matrix_multiplication(const vector<vector<int>>&A, const vector<vector<int>>&B, vector<vector<int>>&C, int n) {
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            int factor = A[i][k];
            for(int j = 0; j < n; j++) {
                C[i][j] += factor * B[k][j];
            }
        }
    }
}