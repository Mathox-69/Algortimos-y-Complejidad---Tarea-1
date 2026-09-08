//https://rosettacode.org/wiki/Sorting_algorithms/Patience_sort
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void patienceSort(vector<int> &array) {
    if (array.empty()) {
        return;
    }

    vector<vector<int>> piles;
    vector<int> pile_tops; 

    for (int x : array) {
        auto it = lower_bound(pile_tops.begin(), pile_tops.end(), x);

        if (it == pile_tops.end()) {
            piles.push_back({x});
            pile_tops.push_back(x);
        } else {
            int idx = distance(pile_tops.begin(), it);
            piles[idx].push_back(x);
            pile_tops[idx] = x; 
        }
    }

    using elemento = pair<int, int>;
    priority_queue<elemento, vector<elemento>, greater<elemento>> min_heap;

    for (size_t i = 0; i < piles.size(); i++) {
        min_heap.push({piles[i].back(), static_cast<int>(i)});
        piles[i].pop_back();
    }

    int indice = 0;
    while (!min_heap.empty()) {
        auto [val, pile_indice] = min_heap.top();
        min_heap.pop();
        array[indice++] = val;

        if (!piles[pile_indice].empty()) {
            min_heap.push({piles[pile_indice].back(), pile_indice});
            piles[pile_indice].pop_back();
        }
    }
}