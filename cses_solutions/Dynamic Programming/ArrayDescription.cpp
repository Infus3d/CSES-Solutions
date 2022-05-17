/*
 * Problem link : https://cses.fi/problemset/task/1746
 * Thorough explanation : https://codeforces.com/blog/entry/70018
 * (You might need to scroll down to locate the problem)
 * Runtime O(n*m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

int n, m;
int dp[2][101], x[100001];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<n; i++)
    scanf("%d", &x[i]);
  
  for(int i=1; i<=m; i++)
    if(x[0] == 0 || x[0] == i)
      dp[0][i] = 1;
  
  for(int i=1; i<n; i++){
    if(x[i] == 0){   //if we can put whatever we want
      for(int j=1; j<=m; j++)
        for(int k=j-1; k<=j+1; k++)
          if(k >= 1 && k <= m)
            dp[1][j] = (dp[1][j] + dp[0][k]) % MOD;
    }
    else{  //if we are limited to only x[i] on this iteration
      for(int k=x[i]-1; k<=x[i]+1; k++)
        if(k >= 1 && k <= m)
          dp[1][x[i]] = (dp[1][x[i]] + dp[0][k]) % MOD;
    }
    
    //Instead of keeping dp[1e5][1e2] array, we can cut on memory and maintain an alternating
    //dp[2][1e2] array because every i is concerned about its previous state i-1
    for(int j=0; j<=m; j++){
      dp[0][j] = dp[1][j];
      dp[1][j] = 0;
    }
  }
  
  int ans = 0;
  for(int i=1; i<=m; i++)
    if(x[n-1] == 0 || x[n-1] == i)
      ans = (ans + dp[0][i]) % MOD;
  printf("%d\n", ans);
  
  return 0;
}
