/*
 * Problem link : https://cses.fi/problemset/task/2168
 * Video editorial : https://www.youtube.com/watch?v=upDipax6xDU
 * 
 * Video explanation might slightly differ from mine, but the idea
 * should be the same.
 * 
 * There are probably ways of solving this with smaller constant
 * [though it'll still be O(n*log(n))] than the solution below,
 * but I chose to do so to keep it cleaner.
 * 
 * Let's first focus on the 1st line of the output a[] where a[i]
 * is 1 if [l[i], r[i]] contains another interval and 0 otherwise.
 * Assume that the intervals are stored in hashmap M with their r[i]
 * value as keys. For example:
 * 4
 * 1 6
 * 2 4
 * 4 8
 * 3 6
 * 
 * Map M (hashmap) will contain the intervals like below:
 * M[4] : 2
 * M[6] : 1, 4
 * M[8] : 3
 * 
 * (Interval j refers to the interval with index j -> l[j], r[j])
 * 
 * Now let's process the map entries from smallest to largest(from 4
 * to 8 in the example). By doing so, at each i we guarantee that the
 * intervals we've seen before have their r[i] at most i. Imagine we
 * store the l[j]'s of all intervals j in M[0...i] in a set S (sorted set).
 * We process every interval j at M[i] one-by-one:
 * Now since we are guaranteed that any l[k]'s in S will have its corresponding
 * r[k] <= i (i == l[j] here), we only need to check if there is any element k in S with
 * l[j] <= l[k] meaning if there is any element/interval we've seen before (that for sure
 * has its right end <= our current right end r[j]) that has its left end >= our current
 * left end l[j]. We can find this using binary search in sets and if there is such an
 * element then a[j] = 1 (0 otherwise);
 * 
 * 
 * The 2nd line of the output b[] where b[i] is 1 if [l[i], r[i]] is contained in any interval
 * is also calculated using the analogous approach as a[].
 * This time we need to iterate through the map M from highest to lowest and keep track of intervals
 * covered on the way. Let's say that we are at interval index j of M[i]:
 * If any of the intervals k we've seen before have their left end <= our current left end l[j] then
 * the answer b[j] = 1 and 0 otherwise. We can again find this using binary search on the 'left-end'
 * of the intervals we've encountered so far that are stored in a set.
 * 
 * Overall runtime O(n*log(n))
 * */

#include "bits/stdc++.h"

using namespace std;

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
  set<pair<int, int>> setR;
  for(auto i = M.begin(); i != M.end(); i++){
    for(int j : i->second)
      setR.insert({range[j].first, j});
    
    for(int j : i->second){
      setR.erase({range[j].first, j}); //momentarily remove interval itself, to avoid counting itself
      
      if(setR.lower_bound({range[j].first, -1}) != setR.end())
        a[j] = 1;
      
      setR.insert({range[j].first, j});
    }
  }
  
  vector<int> b(n);
  set<pair<int, int>> setL;
  for(auto i = M.rbegin(); i != M.rend(); i++){ //from reverse-begin to reverse-end
    for(int j : i->second)
      setL.insert({range[j].first, j});
    
    for(int j : i->second){
      setL.erase({range[j].first, j}); //we momentarily remove the interval itself
      
      if(!setL.empty() && setL.lower_bound({range[j].first+1, -1}) != setL.begin())
        b[j] = 1;
      
      setL.insert({range[j].first, j});
    }
  }
  
  for(int i=0; i<n; i++)
    printf("%d ", a[i]);
  puts("");
  
  for(int i=0; i<n; i++)
    printf("%d ", b[i]);
  puts("");
  
  
  return 0;
}
