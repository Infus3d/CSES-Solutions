/*
 * Problem link : https://cses.fi/problemset/task/1141
 * 
 * We can maintain two pointers that start with l = 0 and r = 0,
 * such that the range x[l, r-1] contains distinct numbers. 
 * We also keep track of visited numbers with a hashtable ('map'). 
 * ------> Whenever x[r] is not visited, we inlcude r in our 
 *         current interval: r++ and mark the number x[r] as visited
 *         in hashtable.
 * ------> Whenever x[r] is visited, we realize that r can not
 *         further increase unless the eariler occurence of the
 *         number x[r] has been excluded by l: l++ and unmark/unvisit
 *         x[l] as it is not within our current interval anymore.
 * 
 * To get the answer, it is enough to maximize the current answer with
 * r-i everytime we're done increasing r.
 * Runtime O(n * logn) where logn is the cost of inserting into 'map'
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; 
  scanf("%d", &n);
  
  vector<int> x(n);
  for(int i=0; i<n; i++)
    scanf("%d", &x[i]);
  
  map<int, int> count;
  int r = 0, ans = 0;
  
  for(int i=0; i<n; i++){
    while(r < n && count[x[r]] == 0){
      count[x[r]]++;
      r++;
    }
    ans = max(ans, r-i);
    count[x[i]]--;
  }
  printf("%d\n", ans);
  
  return 0;
}
