/*
 * Problem link : https://cses.fi/problemset/task/1715
 * Prereq:
 * ---> Binomial Coefficients:
 *      https://cses.fi/book/book.pdf   (Chapter 22, Binomial Coefficients)
 * ---> Modular Inverse:
 *      https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * ---> Multinomical Coefficient:
 *      https://cses.fi/book/book.pdf    (Chapter 22, Multinomial Coefficient)
 * 
 * First let's treat the characters as if they all were different, that is n different characters
 * in the given string of length n.
 * The number of different strings that can be formed then would simply be n! because we have n
 * choices for the first letter/place, n-1 choices for the second, n-2 for third, etc.
 * However we know that some of characters can be the same, in fact there can only be 26 different
 * characters. Let cnt['a'], cnt['b'], ..., cnt['z'] contain the number of occurrences of each of
 * these characters.
 * Then the answer would be n! / (cnt['a']! * cnt['b']! * cnt['c']! * ... * cnt['z']!) because
 * we need to avoid counting the multiple re-orderings of the same/similar characters in our initial
 * n! permutation. In any given permutation of n! possible permutations, there will be cnt['a']!
 * possible re-orderings of bunch of 'a' letters between themselves. The same is true for letters b, c, e, ..., z.
 * 
 * Please refer to the following video for greater detail:
 * https://www.youtube.com/watch?v=dZUrTPDu6GI
 * 
 * Runtime O(n + log(n) + alpha) where alphe is the number of possible characters in the given string
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
  scanf("%s", s);
  int n = strlen(s);
  vector<int> lettercnt(26);
  for(int i=0; i<n; i++)
    lettercnt[s[i]-'a']++;
  
  initFactorials();
  long long ans = fac[n];
  for(int i=0; i<26; i++)
    ans = (ans * invfac[lettercnt[i]]) % MOD;
  printf("%lld\n", ans);
  
  return 0;
}
