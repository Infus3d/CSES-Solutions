/*
 * Problem link : https://cses.fi/problemset/task/1095
 * 
 * The naive solution would be to simply multiply the number a b-times.
 * But we can reduce the time complexity significantly from O(b) to O(log(b)) if notice
 * that a^b equals:
 * ----> a^(b/2) * a^(b/2) when b is even
 * ----> a^(b/2) * a^(b/2) * b when b is odd
 * 
 * This tells us that if we know a^(b/2) we can simply take that number and multiply with itself
 * once to get a^b (or multiply again with b when b is odd). So we just need to know a^(b/2) and
 * analogously if we know a^(b/4) we can do the same thing to determine a^(b/2) and so on...
 * You can see the pattern here.
 * The base case of this recursion is when b = 0: we can just return 1 because a^0 = 1.
 * 
 * Runtime O(n*log(b))
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

int bmod(int x, int deg){
  if(deg == 0) 
    return 1;
  
  int half = bmod(x, deg/2);
  int full = (1LL * half * half) % MOD;
  if(deg % 2 == 1)
    full = (1LL * full * x) % MOD;
  
  return full;
}

int main(){
  int a, b, n;
  scanf("%d", &n);
  while(n--){
    scanf("%d%d", &a, &b);
    printf("%d\n", bmod(a, b));
  }
  
  return 0;
}
