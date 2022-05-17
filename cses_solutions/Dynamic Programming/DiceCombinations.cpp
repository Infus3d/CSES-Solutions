/*
 * Problem link : https://cses.fi/problemset/task/1633
 * Tutorial : https://codeforces.com/blog/entry/70018
 * (Please locate the problem in this blog ^)
 * Runtime O(n) since 6 is constant
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6;
const int MOD = 1e9+7;

int n, dp[N+1];

int main(){
  scanf("%d", &n);
  
  dp[0] = 1;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=6; j++)
      if(i-j >= 0)
        dp[i] = (dp[i] + dp[i-j]) % MOD;
  }
  printf("%d\n", dp[n]);
  
  return 0;
}
