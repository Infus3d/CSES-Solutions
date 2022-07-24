/*
 * Problem link : https://cses.fi/problemset/task/2187
 * Prereq:
 * ---> Binomial Coefficients:
 *      https://cses.fi/book/book.pdf   (Chapter 22, Binomial Coefficients)
 * ---> Modular Inverse:
 *      https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * ---> Catalan Numbers:
 *      https://cses.fi/book/book.pdf  (Chapter 22, Catalan Numbers)
 * 
 * It is recommended that you solve Bracket Sequences I before attempting the harder version.
 * This problem is simply an extension of its previous version where we need to handle few
 * case works with given initial prefix of the bracket sequence and solve the rest using the
 * logic of Catalan Numbers.
 * The following video tutorial clearly explains the solution:
 * https://www.youtube.com/watch?v=uc0io6icKfY
 * 
 * Runtime O(n + log(MOD))
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;
const int N = 1e6+1;

char s[N];
long long fac[N], invfac[N];

long long bmod(long long x, int deg){
  if(deg == 0) return 1;
  if(deg == 1) return x % MOD;
  long long half = bmod(x, deg/2);
  long long full = (half * half) % MOD;
  if(deg % 2) full = (full * x) % MOD;
  return full;
}

void initFactorials(){
  fac[0] = 1;
  for(int i=1; i<N; i++)
    fac[i] = (fac[i-1] * i) % MOD;
  
  invfac[N-1] = bmod(fac[N-1], MOD-2);
  for(int i=N-2; i>=0; i--)
    invfac[i] = (invfac[i+1] * (i+1)) % MOD;
}

int C(int n, int k){
  if(k < 0 || n < k)
    return 0;
  return (((fac[n] * invfac[n-k]) % MOD) * invfac[k]) % MOD;
}

int main(){
  int n, k;
  scanf("%d%s", &n, s);
  k = strlen(s);
  
  int opening = 0, valid = 1;
  for(int i=0; i<k; i++){
    opening += (s[i] == '(' ? 1 : -1);
    if(opening < 0)
      valid = 0;
  }
  
  int m = (opening + (n - k)) / 2;
  if(n % 2 == 1 || !valid || m < opening){
    puts("0");
    return 0;
  }
  
  initFactorials();
  int ans = (C(n-k, m) - C(n-k, m+1) + MOD) % MOD;
  printf("%d\n", ans);
  
  return 0;
}
