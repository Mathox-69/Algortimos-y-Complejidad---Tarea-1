// https://medium.com/@omkareshwarhalli/merge-sort-in-c-code-with-explanation-e20a7988e1c1
// Tiene un cambio en la implementacipon, en el uso de un array temporal para minimizar el impacto en el rendimiento 
// que supodnria reservar memoria durante cada llamada recursiva.

#include <vector>
using namespace std;

void merge(vector<int> &array, vector<int> &temp, int start, int mid, int end) {
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end) {
        if (array[i] <= array[j]) temp[k++] = array[i++];
        else temp[k++] = array[j++];
    }
    while (i <= mid) temp[k++] = array[i++];
    while (j <= end) temp[k++] = array[j++];
    for (i = start; i <= end; i++) array[i] = temp[i];
}

void mergeSort_recursivo(vector<int> &array, vector<int> &temp, int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSort_recursivo(array, temp, start, mid);
    mergeSort_recursivo(array, temp, mid + 1, end);
    merge(array, temp, start, mid, end);
}

void mergeSort(vector<int> &array) {
    vector<int> temp(array.size());
    mergeSort_recursivo(array, temp, 0, array.size() - 1);
}
