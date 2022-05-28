/*
 * Problem link : https://cses.fi/problemset/task/2169
 * Video editorial : https://www.youtube.com/watch?v=ORdmSirqrMs
 * 
 * Video explanation might slightly differ from mine, but the idea
 * should be the same.
 * 
 * This is a harder version of the Nested Ranges Check problem.
 * The only difference is that we need to count the number of the
 * intervals instead of simply checking for existence.
 * 
 * We can take the solution of the easier version and optimize upon it.
 * Since the normal std sets (or multisets) do not allow the index access
 * and order check for an element, we resort to pbds indexed_set.
 * 
 * With indexed_set we can get the [ordered] index of the element we're
 * binary searching. Let's the index of such element u is idx (0 based), then
 * the set contains idx elements smaller than u and (set.size() - idx) elements
 * greater than or equal to u. These values help us count the number of intervals
 * for every j of M[i] on our iteration through the map (either i++ or i--).
 * 
 * Overall runtime O(n*log(n))
 * */
#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
          tree_order_statistics_node_update> indexed_set; //defining our own type

int main(){
  int n; 
  scanf("%d", &n);
  
  vector<pair<int, int>> range(n);
  map<int, vector<int>> M;
  
  for(int i=0; i<n; i++){
    scanf("%d%d", &range[i].first, &range[i].second);
    M[range[i].second].push_back(i);
  }
  
  vector<int> a(n);
  indexed_set setR;
  for(auto i = M.begin(); i != M.end(); i++){
    for(int j : i->second)
      setR.insert({range[j].first, j});
    
    for(int j : i->second)
      a[j] = setR.size() - setR.order_of_key({range[j].first, -1}) - 1;
  }
  
  vector<int> b(n);
  indexed_set setL;
  for(auto i = M.rbegin(); i != M.rend(); i++){ //from reverse-begin to reverse-end
    for(int j : i->second)
      setL.insert({range[j].first, j});
    
    for(int j : i->second)
      b[j] = setL.order_of_key({range[j].first+1, -1}) - 1;
  }
  
  for(int i=0; i<n; i++)
    printf("%d ", a[i]);
  puts("");
  
  for(int i=0; i<n; i++)
    printf("%d ", b[i]);
  puts("");
  
  
  return 0;
}
