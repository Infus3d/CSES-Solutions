/*
 * Problem link : https://cses.fi/problemset/task/1085
 * 
 * We can binary-search the answer to check if it's possible to divide
 * the array into less-than-or-equal-to k subarrays with current mid 
 * value (l+r)/2 as the limiting sum of each subarray. Please note that
 * we don't necessarily have to find a way to divide into exactly k subarrays.
 * We're satisfied with any u that less-than-or-equal-to k because we can
 * 'extend' u subarrays into k as doing so will only decrease the sum
 * in the subararys.
 * To check this, we can start from the beginning of the array and include
 * as many elements to the right as limiting sum allows for that iteration
 * of binary search. If taking another element overflows the sum, we start a
 * new subarray. Doing so will give us the minimum number of subarrays each
 * with sum of at most 'limiting-sum'.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int n, k;
vector<int> x;

bool fine(long long sumLimit){
  for(int i=0; i<n; i++)
    if(sumLimit < x[i])
      return false;
  
  long long curSum = 0, p = 0, cnt = 0;
  while(p < n){
    if(curSum + x[p] <= sumLimit)
      curSum += x[p];
    else{
      curSum = x[p];
      cnt++;
    }
    p++;
  }
  
  return (cnt+1 <= k);
}

int main(){
  scanf("%d%d", &n, &k);
  
  long long sum = 0;
  x.resize(n);
  for(int i=0; i<n; i++){
    scanf("%d", &x[i]);
    sum += x[i];
  }
  
  long long l = 0, r = sum;
  while(l+1 < r){
    long long mid = (l + r) / 2;
    if(fine(mid))
      r = mid;
    else
      l = mid;
  }
  printf("%lld\n", r);
  
  return 0;
}
