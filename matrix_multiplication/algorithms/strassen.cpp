// https://github.com/dmonaldo/strassen-matrix-multiplication/blob/master/main.cpp
// https://shivathudi.github.io/jekyll/update/2017/06/15/matr-mult.html

#include <vector>
using namespace std;

void suma(const vector<vector<int>>&A,const vector<vector<int>>&B,vector<vector<int>>&C,int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            C[i][j] = A[i][j]+B[i][j];
        }
    }
}

void resta(const vector<vector<int>>&A,const vector<vector<int>>&B,vector<vector<int>>&C,int n){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            C[i][j] = A[i][j]-B[i][j];
        }
    }
}

void recursive_strassen_matrix_multiplication(const vector<vector<int>>&A,const vector<vector<int>>&B, vector<vector<int>>&C,int n){
    if(n==1){
        C[0][0]=A[0][0]*B[0][0];
        return;
    }else{
        int new_n = n/2;
        
        vector<int> vector_interno(new_n, 0);

         vector<vector<int>> A11(new_n, vector_interno),
         A12(new_n, vector_interno),
         A21(new_n, vector_interno),
         A22(new_n, vector_interno),

         B11(new_n, vector_interno),
         B12(new_n, vector_interno),
         B21(new_n, vector_interno),
         B22(new_n, vector_interno),

         C11(new_n, vector_interno),
         C12(new_n, vector_interno),
         C21(new_n, vector_interno),
         C22(new_n, vector_interno),

         S1(new_n, vector_interno),
         S2(new_n, vector_interno),
         S3(new_n, vector_interno),
         S4(new_n, vector_interno),
         S5(new_n, vector_interno),
         S6(new_n, vector_interno),
         S7(new_n, vector_interno),
         S8(new_n, vector_interno),
         S9(new_n, vector_interno),
         S10(new_n, vector_interno),
        
         P1(new_n, vector_interno),
         P2(new_n, vector_interno),
         P3(new_n, vector_interno),
         P4(new_n, vector_interno),
         P5(new_n, vector_interno),
         P6(new_n, vector_interno),
         P7(new_n, vector_interno),

         temp_A(new_n, vector_interno),
         temp_B(new_n, vector_interno);

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
        // suma: S_n = {A||B}_{i,j} + {A||B}_{i,j}
        // resta: S_n = {A||B}_{i,j} - {A||B}_{i,j}
        resta(B12,B22,S1,new_n);
        suma(A11,A12,S2,new_n);
        suma(A21,A22,S3,new_n);
        resta(B21,B11,S4,new_n);
        suma(A11,A22,S5,new_n);
        suma(B11,B22,S6,new_n);
        resta(A12,A22,S7,new_n);
        suma(B21,B22,S8,new_n);
        resta(A11,A21,S9,new_n);
        suma(B11,B12,S10,new_n);

        recursive_strassen_matrix_multiplication(A11,S1,P1,new_n);
        recursive_strassen_matrix_multiplication(S2,B22,P2,new_n);
        recursive_strassen_matrix_multiplication(S3,B11,P3,new_n);
        recursive_strassen_matrix_multiplication(A22,S4,P4,new_n);
        recursive_strassen_matrix_multiplication(S5,S6,P5,new_n);
        recursive_strassen_matrix_multiplication(S7,S8,P6,new_n);
        recursive_strassen_matrix_multiplication(S9,S10,P7,new_n);

        // C11 = P5 + P4 - P2 + P6
        suma(P5,P4,temp_A,new_n);
        resta(temp_A,P2,temp_B,new_n);
        suma(temp_B,P6,C11,new_n);
        // C12 = P1 + P2
        suma(P1,P2,C12,new_n);
        // C21 = P3 + P4
        suma(P3,P4,C21,new_n);
        // C22 = P5 + P1 + - P3 - P7
        suma(P5,P1,temp_A,new_n);
        resta(temp_A,P3,temp_B,new_n);
        resta(temp_B,P7,C22,new_n);

        for(int i = 0; i<new_n; i++){
            for(int j = 0; j<new_n; j++){
                C[i][j]=C11[i][j];
                C[i][j+new_n]=C12[i][j];
                C[i+new_n][j]=C21[i][j];
                C[i+new_n][j+new_n]=C22[i][j];
            }
        }
    }
}

void strassen_matrix_multiplication(const vector<vector<int>>&A,const vector<vector<int>>&B, vector<vector<int>>&C,int n){
    recursive_strassen_matrix_multiplication(A,B,C,n);
}