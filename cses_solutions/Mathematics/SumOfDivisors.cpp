/*
 * Problem link : https://cses.fi/problemset/task/1082
 * 
 * The following video fully explains how to find the divisors of a single number n
 * as well as the sum of all divisors of all numbers up to n.
 * https://www.youtube.com/watch?v=JqWiWJQOQyU
 * 
 * The video should not be hard to understand but following link might help clear
 * some confusion about 2^(-1) % MOD = 2^(MOD-2) % MOD (Also known as modular inverse):
 * ----> https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * 
 * Runtime O(sqrt(n) + log(MOD)) where MOD = 1e9+7.
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

int bmod(int x, int deg){
  if(deg == 0) 
    return 1 % MOD;
  
  int half = bmod(x, deg/2);
  int full = (1LL * half * half) % MOD;
  if(deg % 2 == 1)
    full = (1LL * full * x) % MOD;
  
  return full;
}

int main(){
  long long n;
  scanf("%lld", &n);
  
  long long ans = 0, curDiv = 1, inv2 = bmod(2, MOD-2);
  while(curDiv <= n){
    long long quotient = n / curDiv;
    long long st = curDiv, en = n / quotient;
    long long curBlockSum = (((((en-st+1) % MOD) * ((st + en) % MOD)) % MOD) * inv2) % MOD;
    ans = (ans + ((curBlockSum * quotient) % MOD)) % MOD;
    curDiv = en+1;
  }
  printf("%lld\n", ans);
  
  return 0;
}
