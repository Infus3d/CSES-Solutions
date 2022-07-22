/*
 * Problem link : https://cses.fi/problemset/task/1095
 * Please refer to this video tutorial for explanation:
 * https://www.youtube.com/watch?v=jkZ6c-uAl7Y
 * 
 * Runtime O(n*(log(c) + log(r))) where r = (b ^ c) % 1e9+6
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

int bmod(int x, int deg, int mod){
  if(deg == 0) 
    return 1 % mod;
  
  int half = bmod(x, deg/2, mod);
  int full = (1LL * half * half) % mod;
  if(deg % 2 == 1)
    full = (1LL * full * x) % mod;
  
  return full;
}

int main(){
  int a, b, c, n;
  scanf("%d", &n);
  while(n--){
    scanf("%d%d%d", &a, &b, &c);
    printf("%d\n", bmod(a, bmod(b, c, MOD-1), MOD));
  }
  
  return 0;
}
