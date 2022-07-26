/*
 * Problem link : https://cses.fi/problemset/task/2210
 * 
 * Just like in Counting Necklace problem, we make use of Burnside's Lemma by
 * counting the sizes of fixed sets of each element/rotation in G where G is
 * just the set of rotations. The possible rotations of the square
 * are 0, 90, 180 and 270 degrees, so there are 4 different rotational elements
 * in G. Over all 4 elements we count the number of 'non-changing' orderings
 * of black and white colors of the grid and sum it up. We then divide the sum
 * by the size of G which is simply 4.
 * If you are interested about why this is true or if you just want to understand
 * it better please refer to the following sources:
 * https://codeforces.com/blog/entry/82103?#comment-833959
 * https://math.stackexchange.com/questions/3587286/using-group-actions-to-determine-the-different-colourings-of-a-grid
 * https://en.wikipedia.org/wiki/Burnside%27s_lemma
 * 
 * Runtime O(log(n^2))
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

long long bmod(int x, long long deg){
  if(deg == 0) return 1 % MOD;
  if(deg == 1) return x % MOD;
  long long half = bmod(x, deg/2);
  long long full = (half * half) % MOD;
  if(deg % 2) full = (full * x) % MOD;
  return full;
}

int main(){
  long long n;
  scanf("%lld", &n);
  
  long long g0 = bmod(2, n*n);
  long long g90 = bmod(2, (n*n + (n % 2 ? 3 : 0))/4);
  long long g180 = bmod(2, (n*n + (n % 2 ? 1 : 0))/2);
  long long g270 = g90;
  
  long long tot = (g0 + g90 + g180 + g270) % MOD;
  long long ans = (tot * bmod(4, MOD-2)) % MOD;
  printf("%lld\n", ans);
  
  return 0;
}
