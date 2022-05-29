/*
 * Problem link : https://cses.fi/problemset/task/1620
 * 
 * This problem can be solved with binary-search.
 * We binary-search over the answer, which is the minimum time needed
 * to make [at least] t total products.
 * We start with l = 0 and r = 1e18 and everytime we check the mid by
 * calculating the number of products that are possible with 'mid' amount
 * of time. If that number is greater than t, then r = mid (we can still go
 * lower). But if the number is lower than t, then l = mid as there is no way
 * we'll be able to make more with less than 'mid' amount of time.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int n, t;
vector<int> k;

bool fine(long long x){
  long long sum = 0;
  for(int i=0; i<n; i++){
    sum += x / k[i];
    if(sum >= t)
      return true;
  }
  return false;
}

int main(){
  scanf("%d%d", &n, &t);
  k.resize(n);
  for(int i=0; i<n; i++)
    scanf("%d", &k[i]);
  
  long long l = 0, r = 1e18;
  while(l + 1 < r){
    long long mid = (l + r) / 2;
    if(fine(mid) == true)
      r = mid;
    else
      l = mid;
  }
  printf("%lld\n", r);
  
  return 0;
}
