
//Fuente: Gemini AI , implementación optimizada porque otras implementaciones se iban a o(n²), específicamente:
// https://www.geeksforgeeks.org/dsa/patience-sorting/ -> muy lenta

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "algorithms.h"

using namespace std;

void patienceSorting(vector<int>& arr) {
    vector<vector<int>> piles;
    
    for (int x : arr) {
        // Find the first pile whose top element is >= x
        auto it = lower_bound(piles.begin(), piles.end(), x, [](const vector<int>& pile, int val) {
            return pile.back() < val;
        });
        
        if (it == piles.end()) {
            piles.push_back({x});
        } else {
            it->push_back(x);
        }
    }
    
   auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first; // Min-heap
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
    
    vector<int> pileIndices(piles.size(), 0);
    for (size_t i = 0; i < piles.size(); ++i) {
        minHeap.push({piles[i].back(), i});
    }
    
    arr.clear();
    while (!minHeap.empty()) {
        auto [val, pileIdx] = minHeap.top();
        minHeap.pop();
        
        arr.push_back(val);
        
        piles[pileIdx].pop_back();
        
        if (!piles[pileIdx].empty()) {
            minHeap.push({piles[pileIdx].back(), pileIdx});
        }
    }
}


