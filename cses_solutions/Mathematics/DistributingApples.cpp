/*
 * Problem link : https://cses.fi/problemset/task/1716
 * Prereq:
 * ---> Binomial Coefficients:
 *      https://cses.fi/book/book.pdf   (Chapter 22, Binomial Coefficients)
 * ---> Modular Inverse:
 *      https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * 
 * The solution to the problem is already explained in the CSES book:
 * https://cses.fi/book/book.pdf    (Chapter 22, Page 209)
 * 
 * But if you need a video editorial the following might be helpful:
 * https://www.youtube.com/watch?v=Jb88BpY8WpM
 * 
 * Runtime O(n + log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;
const int N = 2e6+1;

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
  int n, m;
  scanf("%d%d", &n, &m);
  
  initFactorials();
  printf("%d\n", C(m+n-1, n-1));
  
  return 0;
}
