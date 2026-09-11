#include "algorithms/naive.h"
#include "algorithms/strassen.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <sys/resource.h>
#include <charconv>
#include <cstdio>
using namespace std;

class Timer {
public:
    Timer() {
        reset();
    }

    void reset() {
        start_point = std::chrono::high_resolution_clock::now();
    }

    double ms() const {
        auto end_point = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end_point - start_point).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_point;
};


bool cargar_matriz(const string &ruta_archivo, vector<vector<int>> &matriz, int n) {
    ifstream archivo(ruta_archivo);
    if (!archivo.is_open()) return false;

    archivo.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close();
    return true;
}

bool guardar_matriz(const string &ruta_archivo, const vector<vector<int>> &matriz, int n) {
    string buffer;
    buffer.reserve(static_cast<size_t>(n) * n * 12); 

    char tmp[12];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto res = std::to_chars(tmp, tmp + sizeof(tmp), matriz[i][j]);
            buffer.append(tmp, res.ptr - tmp);
            if (j < n - 1) buffer.push_back(' ');
        }
        buffer.push_back('\n');
    }

    FILE* f = fopen(ruta_archivo.c_str(), "wb");
    if (!f) {
        cerr << "Error: No se puede abrir/crear el archivo de salida " << ruta_archivo << endl;
        return false;
    }
    fwrite(buffer.data(), 1, buffer.size(), f);
    fclose(f);
    return true;
}


long obtener_memoria_kb(){
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

int main(){
    string base_path = "data/";
    ofstream csv_file(base_path+"measurements/mediciones_matrices.csv");
    if (!csv_file.is_open()) {
        std::cerr << "Error al crear el archivo CSV de mediciones." << std::endl;
        return 1;
    }
    csv_file << "algoritmo,n,tipo,dominio,muestra,tiempo_ms,memoria_kb\n";

    vector<vector<int>> matrix_1;
    vector<vector<int>> matrix_2;
    vector<int> n_valores = {16,64,256,1024};
    //vector<int> n_valores = {16,64,256};
    vector<string> t_valores = {"dispersa", "diagonal", "densa"};
    vector<string> d_valores = {"D0", "D10"};
    vector<string> m_valores = {"a", "b", "c"};

    for(int n : n_valores){
        for(const auto &t : t_valores){
            for(const auto &d : d_valores){
                for(const auto &m : m_valores){
                    string file1 = base_path+"matrix_input/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_1.txt";
                    string file2 = base_path+"matrix_input/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_2.txt";
                    string file_out_naive = base_path+"matrix_output/naive/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_out.txt";
                    string file_out_strassen = base_path+"matrix_output/strassen/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_out.txt";

                    vector<vector<int>> A(n,vector<int>(n,0));
                    vector<vector<int>> B(n,vector<int>(n,0));
                    vector<vector<int>> C(n,vector<int>(n,0));

                    if(!cargar_matriz(file1,A,n) || !cargar_matriz(file2,B,n)){
                        continue;
                    }
                    
                    Timer t1;
                    naive_matrix_multiplication(A,B,C,n);
                    double t_naive = t1.ms();
                    long mem_naive = obtener_memoria_kb();

                    csv_file << "naive," << n << "," 
                                        << t << "," 
                                        << d << "," 
                                        << m << "," 
                                        << t_naive << ","
                                        << mem_naive << "\n";
                    
                    guardar_matriz(file_out_naive,C,n); 

                    Timer t2;
                    strassen_matrix_multiplication(A,B,C,n);
                    double t_strassen = t2.ms();
                    long mem_strassen = obtener_memoria_kb();
                    guardar_matriz(file_out_strassen,C,n);

                    csv_file << "strassen," << n << "," 
                                        << t << "," 
                                        << d << "," 
                                        << m << "," 
                                        << t_strassen << "," 
                                        << mem_strassen << "\n";
                }
            }
        }
    }
    csv_file.close();
    cout << "Mediciones guardadas con exito." << endl;
    return 0;
}
