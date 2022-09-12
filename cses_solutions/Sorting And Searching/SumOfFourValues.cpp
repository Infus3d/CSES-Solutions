/*
 * Problem link : https://cses.fi/problemset/task/1642
 * 
 * We need to choose 4 indices i < j < u < v with
 * a[i] + a[j] + a[u] + a[v] = x. We can split these 4 into
 * 2 pairs [i, j] and [u, v] and iterate over the [u, v] one to see
 * if we have seen any [i, j] with (a[i] + a[j]) = x - (a[u] + a[v]).
 * 
 * This means that we will have 2 loops first of which iterates through
 * u = 0...n-1, and the second iterates through v = u+1...n-1. At any
 * outer iteration u we will have all sums (a[i] + a[j]) with i < j < u
 * stored in a hashmap (as key) with their indices i and j as a value.
 * Then at any iteration of the inner loop v, we just need to check
 * if the complement x - (a[u] + a[v]) is present in the hashmap. If it
 * is, print out the indices. If not, continue on.
 * 
 * Runtime O(n^2 * log(n)) because map in c++ operates with logarithmic time.
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, x;
  scanf("%d%d", &n, &x);
  
  vector<int> a(n);
  for(int i=0; i<n; i++)
    scanf("%d", &a[i]);
  
  map<int, pair<int, int>> pairMap;
  
  for(int u=0; u<n; u++){
    for(int v=u+1; v<n; v++){
      long long target = x - (a[u] + a[v]);
      if(pairMap.find(target) != pairMap.end()){
        auto [i, j] = pairMap[target];
        
        printf("%d %d ", u+1, v+1);
        printf("%d %d\n", i+1, j+1);
        
        return 0;
      }
    }
    
    for(int v=0; v<u; v++)
      pairMap[a[v] + a[u]] = {v, u};
  }
  
  puts("IMPOSSIBLE");
  
  return 0;
}
