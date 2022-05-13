/*
 * Problem link: https://cses.fi/problemset/task/2181
 * 
 * For in-depth explanation please refer to
 * https://usaco.guide/adv/dp-more?lang=cpp
 * 
 * There are more than a single way to solve this problem
 * with varying time complexities. To learn more about them
 * plese visit:
 * https://discuss.codechef.com/t/bitmask-dp-note-cses-counting-tilings/92175
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

/**
 * Instead of keeping the entire [n][m][mask]
 * we can eliminate the two dimensions of dp
 * and replace it with only [2] as the dp
 * of any state [i][j][mask] is concerned with
 * [i-1][j][mask] (exact previous one).
 ** */
int dp[2][(1<<10)];

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  
  dp[0][0] = 1;
  for(int j=0; j<m; j++){ //processing row-by-row
    for(int i=0; i<n; i++){ //and then column-by-column
      for(int mask=0; mask<(1<<n); mask++){
        dp[1][mask] = dp[0][mask ^ (1<<i)];
        
        if(i > 0 && !(mask & (1<<i)) && !(mask & (1<<(i-1))))
          dp[1][mask] += dp[0][mask ^ (1<<(i-1))];
        
        if(dp[1][mask] >= MOD) dp[1][mask] -= MOD;
      }
      
      for(int mask=0; mask<(1<<n); mask++){
        dp[0][mask] = dp[1][mask];
        dp[1][mask] = 0;
      }
    }
  }
  printf("%d\n", dp[0][0]);
  
  return 0;
}
