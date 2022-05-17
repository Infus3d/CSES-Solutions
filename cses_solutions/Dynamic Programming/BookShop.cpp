/*
 * Problem link : https://cses.fi/problemset/task/1158
 * Tutorial : https://codeforces.com/blog/entry/70018
 * 
 * This is a well known application of dynamic programming
 * called 0-1 knapsack. Please refer to the blog above
 * to learn more.
 * Runtime O(n*x)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5;
const int K = 1e3;

int n, x;
int dp[N+1], h[K], s[K];

int main(){
  scanf("%d%d", &n, &x);
  for(int i=0; i<n; i++) scanf("%d", &h[i]);
  for(int i=0; i<n; i++) scanf("%d", &s[i]);
  
  memset(dp, -1, sizeof(dp));
  
  dp[0] = 0;
  for(int i=0; i<n; i++){
    for(int j=x; j>=0; j--)
      if(dp[j] != -1 && j+h[i] <= x)
        dp[j+h[i]] = max(dp[j+h[i]], dp[j] + s[i]);
  }
  
  int ans = 0;
  for(int i=0; i<=x; i++)  //since we are allowed to use at most x, we need to take the maximum of all dp[i] with i <= x
    ans = max(ans, dp[i]);
  printf("%d\n", ans);
  
  return 0;
}
