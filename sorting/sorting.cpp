#include "algorithms/sort.h"
#include "algorithms/mergesort.h"
#include "algorithms/quicksort.h"
#include "algorithms/patiencesort.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <sys/resource.h>
#include <charconv>
#include <cstdio>
using namespace std;

bool cargar_array(const string &ruta_archivo, vector<int> &array, int n) {
    ifstream archivo(ruta_archivo);
    archivo.tie(NULL);
    ios_base::sync_with_stdio(false);

    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo " << ruta_archivo << endl;
        return false;
    }

    array.resize(n);

    for (int i = 0; i < n; i++) {
        archivo >> array[i];
    }

    archivo.close();
    return true;
}



bool guardar_array(const string &ruta_archivo, const vector<int> &array, int n) {
    string buffer;
    buffer.reserve(static_cast<size_t>(n) * 12); 

    char tmp[12];
    for (int i = 0; i < n; i++) {
        auto res = std::to_chars(tmp, tmp + sizeof(tmp), array[i]);
        buffer.append(tmp, res.ptr - tmp);
        if (i < n - 1) buffer.push_back(' ');
    }
    buffer.push_back('\n');

    FILE* f = fopen(ruta_archivo.c_str(), "wb");
    if (!f) {
        cerr << "Error: No se puede abrir/crear el archivo de salida " << ruta_archivo << endl;
        return false;
    }
    fwrite(buffer.data(), 1, buffer.size(), f);
    fclose(f);
    return true;
}

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

long obtener_memoria_kb(){
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

int main(){
    srand(time(NULL));
    string base_path = "data/";
    ofstream csv_file(base_path+"measurements/mediciones_sorting.csv");
    if (!csv_file.is_open()) {
        std::cerr << "Error al crear el archivo CSV de mediciones." << std::endl;
        return 1;
    }
    csv_file << "algoritmo,n,tipo,dominio,muestra,tiempo_ms,memoria_kb\n";

    vector<int> array_original;
    vector<int> n_valores = {10,1000,100000,10000000};
    vector<string> t_valores = {"ascendente", "descendente", "aleatorio"};
    vector<string> d_valores = {"D1", "D7"};
    vector<string> m_valores = {"a", "b", "c"};

    srand(42);

    for(int n : n_valores){
        for(const auto &t : t_valores){
            for(const auto &d : d_valores){
                for(const auto &m : m_valores){
                    string file = base_path+"array_input/"+to_string(n)+"_"+t+"_"+d+"_"+m+".txt";
                    string file_out_Sort = base_path+"array_output/sort/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_out.txt";
                    string file_out_mergeSort = base_path+"array_output/mergesort/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_out.txt";
                    string file_out_quickSort = base_path+"array_output/quicksort/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_out.txt";
                    string file_out_patienceSort = base_path+"array_output/patiencesort/"+to_string(n)+"_"+t+"_"+d+"_"+m+"_out.txt";

                    

                    if(!cargar_array(file,array_original,n)){
                        continue;
                    }
                    
                    vector<int> array = array_original;

                    Timer t1;
                    sortArray(array);
                    double t_Sort = t1.ms();
                    long mem_Sort = obtener_memoria_kb();

                    csv_file << "Sort," << n << "," 
                                        << t << "," 
                                        << d << "," 
                                        << m << "," 
                                        << t_Sort << ","
                                        << mem_Sort << "\n";
                    
                    guardar_array(file_out_Sort,array,n);
                    array = array_original;

                    Timer t2;
                    mergeSort(array);
                    double t_mergeSort = t2.ms();
                    long mem_mergeSort = obtener_memoria_kb();

                    csv_file << "mergeSort," << n << "," 
                                        << t << "," 
                                        << d << "," 
                                        << m << "," 
                                        << t_mergeSort << ","
                                        << mem_mergeSort << "\n";
                    
                    guardar_array(file_out_mergeSort,array,n);
                    array = array_original;

                    Timer t3;
                    quickSort(array,0,n-1);
                    double t_quickSort = t3.ms();
                    long mem_quickSort= obtener_memoria_kb();

                    csv_file << "quickSort," << n << "," 
                                        << t << "," 
                                        << d << "," 
                                        << m << "," 
                                        << t_quickSort << ","
                                        << mem_quickSort << "\n";
                    
                    guardar_array(file_out_quickSort,array,n);
                    array = array_original;

                    Timer t4;
                    patienceSort(array);
                    double t_patienceSort = t4.ms();
                    long mem_patienceSort = obtener_memoria_kb();

                    csv_file << "patienceSort," << n << "," 
                                        << t << "," 
                                        << d << "," 
                                        << m << "," 
                                        << t_patienceSort << ","
                                        << mem_patienceSort << "\n";
                    
                    guardar_array(file_out_patienceSort,array,n);
                }
            }
        }
    }
    csv_file.close();
    cout << "Mediciones guardadas con exito." << endl;
    return 0;
}