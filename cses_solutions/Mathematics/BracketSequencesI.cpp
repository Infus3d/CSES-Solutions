/*
 * Problem link : https://cses.fi/problemset/task/2064
 * Prereq:
 * ---> Binomial Coefficients:
 *      https://cses.fi/book/book.pdf   (Chapter 22, Binomial Coefficients)
 * ---> Modular Inverse:
 *      https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * 
 * First we notice that for a bracket sequence to be valid, the number of '(' and ')'
 * must be equal. If not, then the answer is 0.
 * When n is even, the number of valid bracket sequences of length n is exactly the
 * (n/2)'th Catalan Number. You can learn about catalan numbers from the following book:
 * https://cses.fi/book/book.pdf    (Chapter 22, Catalan Numbers)
 * 
 * If you need further explanation, the video below covers it in great detail:
 * https://www.youtube.com/watch?v=oZHY0FeBFtw
 * 
 * Runtime (n + log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;
const int N = 1e6+1;

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
  int n;
  scanf("%d", &n);
  if(n % 2 == 1){
    puts("0");
    return 0;
  }
  
  initFactorials();
  int ans = (C(n, n/2) - C(n, n/2+1) + MOD) % MOD;
  printf("%d\n", ans);
  
  return 0;
}
