/*
 * Problem link : https://cses.fi/problemset/task/1717
 * Prereq:
 * ---> Binomial Coefficients:
 *      https://cses.fi/book/book.pdf   (Chapter 22, Binomial Coefficients)
 * ---> Modular Inverse:
 *      https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * 
 * We are asked to find the number of permutations of length n where no number
 * perm[i] in the permutation is equal to its index i: for all i --> perm[i] != i.
 * 
 * We can look at the problem in a different way: let's count the number of permutations
 * that have at least one perm[i] equal to i. Then we can simply subtract this number
 * from n! to get the answer to the problem.
 * 
 * To count such number of permutations efficiently we will need to take advantage of
 * the inclusion-exclusion principle. The following video tutorial explains this pretty nicely:
 * https://www.youtube.com/watch?v=6ENst56fdPc
 * 
 * Runtime O(n + log(n))
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
  
  initFactorials();
  int ans = fac[n];
  for(int i=1; i<=n; i++){
    int cur = ((long long)C(n, i) * fac[n-i]) % MOD;
    if(i % 2 == 1) ans = (ans - cur + MOD) % MOD;
    else ans = (ans + cur) % MOD;
  }
  printf("%d\n", ans);
  
  return 0;
}
