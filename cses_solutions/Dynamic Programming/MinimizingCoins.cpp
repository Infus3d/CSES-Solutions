/*
 * Problem link : https://cses.fi/problemset/task/1634
 * Tutorial : https://codeforces.com/blog/entry/70018
 * 
 * Almost the same as Coin Combinations I but in this one
 * we need to minimize the number of coins instead of counting
 * the number of ways to achieve x.
 * This is well known knapsack problem which you can learn from
 * the blog link above.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6;

int n, x;
int dp[N+1], c[100];

int main(){
  scanf("%d%d", &n, &x);
  for(int i=0; i<n; i++)
    scanf("%d", &c[i]);
  
  for(int i=0; i<=x; i++) 
    dp[i] = (int)1e9; //setting to 'infinity'
  
  dp[0] = 0;
  for(int i=1; i<=x; i++){
    for(int j=0; j<n; j++)
      if(i-c[j] >= 0)
        dp[i] = min(dp[i], dp[i-c[j]]+1);
  }
  
  if(dp[x] == (int)1e9)
    printf("-1\n");
  else
    printf("%d\n", dp[x]);
  
  return 0;
}
