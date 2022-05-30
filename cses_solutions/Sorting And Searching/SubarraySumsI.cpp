/*
 * Problem link : https://cses.fi/problemset/task/1660
 * 
 * We can maintain 2 pointers l = 0 and r = 0 that both start
 * from the beginning and advance as follows:
 * ----> if the sum[l...r] < x then we need more so we increase r.
 * ----> if the sum[l...r] > x then we need less so we increase l.
 * ----> if the sum[l...r] == x then we found the subarray so we increase
 *       the answer.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, x;
  scanf("%d%d", &n, &x);
  
  vector<int> a(n);
  for(int i=0; i<n; i++)
    scanf("%d", &a[i]);
  
  int r = 0, curSum = 0, ans = 0;
  for(int l=0; l<n; l++){
    while(r < n && (curSum + a[r]) <= x){
      curSum += a[r];
      r++;
    }
    
    ans += (curSum == x ? 1 : 0);
    curSum -= a[l];
  }
  printf("%d\n", ans);
  
  return 0;
}
