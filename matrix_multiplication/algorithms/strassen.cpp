// https://github.com/dmonaldo/strassen-matrix-multiplication/blob/master/main.cpp
// https://shivathudi.github.io/jekyll/update/2017/06/15/matr-mult.html

#include <vector>
using namespace std;

void suma(const vector<vector<int>>&A,const vector<vector<int>>&B,vector<vector<int>>&resultado,int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            resultado[i][j] = A[i][j]+B[i][j];
        }
    }
}

void resta(const vector<vector<int>>&A,const vector<vector<int>>&B,vector<vector<int>>&resultado,int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            resultado[i][j] = A[i][j]-B[i][j];
        }
    }
}

void strassen_matrix_multiplication(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    if(n<=1){
        C[0][0]=A[0][0]*B[0][0];
        return;
    }else{
        int new_n = n/2;
        
        vector<int> vector_interno(new_n, 0);

         vector<vector<int>> A11(new_n, vector_interno), A12(new_n, vector_interno),
                            A21(new_n, vector_interno), A22(new_n, vector_interno),
                            B11(new_n, vector_interno), B12(new_n, vector_interno),
                            B21(new_n, vector_interno), B22(new_n, vector_interno);

         // Dividir las matrices en 4 sub-matrices
        for(int i = 0; i<new_n; i++){
            for(int j = 0; j<new_n; j++){
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+new_n];
                A21[i][j] = A[i+new_n][j];
                A22[i][j] = A[i+new_n][j+new_n];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j+new_n];
                B21[i][j] = B[i+new_n][j];
                B22[i][j] = B[i+new_n][j+new_n];
            }
        }

    // Crear solo dos matrices temporales reciclables
        vector<vector<int>> tempA(new_n, vector<int>(new_n, 0));
        vector<vector<int>> tempB(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m1(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m2(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m3(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m4(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m5(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m6(new_n, vector<int>(new_n, 0));
        vector<vector<int>> m7(new_n, vector<int>(new_n, 0));

        // 3. Llamadas recursivas pasando el destino (mX) por referencia
        suma(A11, A22, tempA, new_n);
        suma(B11, B22, tempB, new_n);
        strassen_matrix_multiplication(tempA, tempB, m1, new_n);

        suma(A21, A22, tempA, new_n);
        strassen_matrix_multiplication(tempA, B11, m2, new_n);

        resta(B12, B22, tempB, new_n);
        strassen_matrix_multiplication(A11, tempB, m3, new_n);

        resta(B21, B11, tempB, new_n);
        strassen_matrix_multiplication(A22, tempB, m4, new_n);

        suma(A11, A12, tempA, new_n);
        strassen_matrix_multiplication(tempA, B22, m5, new_n);

        resta(A21, A11, tempA, new_n);
        suma(B11, B12, tempB, new_n);
        strassen_matrix_multiplication(tempA, tempB, m6, new_n);

        resta(A12, A22, tempA, new_n);
        suma(B21, B22, tempB, new_n);
        strassen_matrix_multiplication(tempA, tempB, m7, new_n);

        vector<vector<int>> C(n, vector<int>(n));
        for (int i = 0; i < new_n; i++) {
            for (int j = 0; j < new_n; j++) {
                C[i][j]                   = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];
                C[i][j + new_n]         = m3[i][j] + m5[i][j];
                C[i + new_n][j]         = m2[i][j] + m4[i][j];
                C[i + new_n][j + new_n] = m1[i][j] - m2[i][j] + m3[i][j] + m6[i][j];
            }
        }
    }
}
