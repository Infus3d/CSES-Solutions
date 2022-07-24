/*
 * Problem link : https://cses.fi/problemset/task/2209
 * 
 * We can apply burnside's lemma to make sure we only count one of multiple
 * rotationally-identical colorings. To learn more about it I recommed reading
 * the following in the given order:
 * ---> https://cses.fi/book/book.pdf    (Chapter 22, Burnside's Lemma)
 * ---> https://brilliant.org/wiki/burnsides-lemma/
 * ---> https://en.wikipedia.org/wiki/Burnside%27s_lemma
 * 
 * Runtime O(n*log(n)) but can be done even more efficiently
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

int bmod(int x, int deg){
  if(!deg) return 1;
  if(deg == 1) return x;
  int half = bmod(x, deg/2);
  int full = (1LL * half * half) % MOD;
  if(deg % 2) full = (1LL * full * x) % MOD;
  return full;
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  
  int ans = 0;
  for(int i=0; i<n; i++)
    ans = (ans + bmod(m, __gcd(i, n))) % MOD;
  ans = (1LL * ans * bmod(n, MOD-2)) % MOD;
  printf("%d\n", ans);
  
  return 0;
}
