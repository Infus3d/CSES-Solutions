/*
 * Problem link : https://cses.fi/problemset/task/1641
 * 
 * This is a little harder version of the Sum of Two Values problem.
 * Here we have n <= 5000 that allows for quadratic runtime solutions.
 * We can choose an index to be the 1st of the three values and try
 * to find other two values that sum up to x-a[chosen_index].
 * We can choose the 1st value at n different indices and find other 
 * two in O(n) time.
 * 
 * So overall runtime is O(n^2)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, x;
  scanf("%d%d", &n, &x);
  
  vector<pair<int, int>> a(n);
  for(int i=0; i<n; i++){
    scanf("%d", &a[i].first);
    a[i].second = i+1;
  }
  sort(a.begin(), a.end());
  
  for(int k=0; k<n; k++){
    int l = 0, r = n-1, aim = x-a[k].first;
    while(l < k && k < r){
      int cur = a[l].first + a[r].first;
      if(cur < aim)
        l++;
      else if(cur > aim)
        r--;
      else{
        printf("%d %d %d\n", a[l].second, a[k].second, a[r].second);
        return 0;
      }
    }
  }
  puts("IMPOSSIBLE");
  
  return 0;
}
