/*
 * Problem link : https://cses.fi/problemset/task/1635
 * Tutorial : https://codeforces.com/blog/entry/70018
 * 
 * Simplest form of 0-1 knapsack where we have infinite
 * number of coins of each type and the adding order
 * of the coins is not specified.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6;
const int MOD = 1e9+7;

int n, x;
int dp[N+1], c[100];

int main(){
  scanf("%d%d", &n, &x);
  for(int i=0; i<n; i++) 
    scanf("%d", &c[i]);
  
  dp[0] = 1;
  for(int i=1; i<=x; i++){
    for(int j=0; j<n; j++)
      if(i-c[j] >= 0)
        dp[i] = (dp[i] + dp[i-c[j]]) % MOD;
  }
  printf("%d\n", dp[x]);
  
  return 0;
}
