// https://stackoverflow.com/questions/7198121/quicksort-and-hoare-partition
// Con el cambio que el pivote es aleatorio para que el caso promedio sea de O(nlog(n))

#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
using namespace std;

int particion(vector<int> &array, int start, int end) {
    int random_index = start + rand() % (end - start + 1);
    int pivot = array[random_index];
    
    int i = start - 1;
    int j = end + 1;
    while (true) {
        do { i++; } while (array[i] < pivot);
        do { j--; } while (array[j] > pivot);
        if (i >= j) return j;
        swap(array[i], array[j]);
    }
}

void quickSort(vector<int> &array, int start, int end) {
    if (start >= end) return;
    int pi = particion(array, start, end);
    quickSort(array, start, pi);    
    quickSort(array, pi + 1, end);
}