/*
 * Problem link : https://cses.fi/problemset/task/1079
 * Prereq:
 * ---> Binomial Coefficients:
 *      https://cses.fi/book/book.pdf   (Chapter 22, Binomial Coefficients)
 * ---> Modular Inverse:
 *      https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * 
 * To calculate a choose b we need to use the formula (a! / ((a-b! * b!)) % MOD.
 * Since the quantity can become too large, we need to output the answer modulo 1e9+7.
 * We can easily calculate (n! % MOD) in O(n) time by simply looping through. We can also
 * calculate ((n!)^(-1) % MOD) by using the modular inverse logic: ((n!)^(MOD-2) % MOD)
 * which also takes another loop to calculate for all n. We can use binary exponentiation
 * to calculate the power of n!.
 * 
 * Let's say that fac[n] contains the n! % MOD, and invfac[n] contains (n!)^(-1) % MOD.
 * Then the formula above becomes (fac[a] / (invfac[a-b] * invfac[b])) % MOD.
 * 
 * Runtime O(n + log(n))
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
  int n;
  scanf("%d", &n);
  
  initFactorials();
  while(n--){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", C(a, b));
  }
  
  return 0;
}
