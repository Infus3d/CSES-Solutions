/*
 * Problem link : https://cses.fi/problemset/task/2185
 * 
 * The problem becomes easy when we consider the inclusion-exclusion principle. The following
 * video tutorial explains the solution nicely:
 * https://www.youtube.com/watch?v=2UEYCzKXh1s
 * 
 * Runtime O(2^k * k)
 * */
#include "bits/stdc++.h"
 
using namespace std;
 
int main(){
  long long n, k;
  scanf("%lld%lld", &n, &k);
  vector<long long> primes(k);
  for(int i=0; i<k; i++)
    scanf("%lld", &primes[i]);
  
  long long ans = 0;
  for(int mask=1; mask<(1<<k); mask++){
    int divCnt = __builtin_popcount(mask);
    long long prod = 1;
    for(int i=0; i<k; i++)
      if((mask>>i)&1){
        if(n / primes[i] >= prod)
          prod *= primes[i];
        else
          prod = n+1;
      }
    
    if(divCnt % 2 == 1)
      ans += n / prod;
    else
      ans -= n / prod;
  }
  printf("%lld\n", ans);
  
  return 0;
}
