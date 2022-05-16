/* 
 * Problem link : https://cses.fi/problemset/task/2413
 * 
 * Main thing to keep in mind in this problem is that
 * there are only 2 columns. And structure-wise only
 * the 'jointness' of those columns matter (on every row).
 * There can only be 2 different 'rows':
 * 
 * Disjoint:
 *  ---- ----
 * |    |    |
 *  ---- ----
 * 
 * or Connected:
 *  ---------
 * |         |
 *  ---------
 * 
 * So since n <= 1e6 we can keep track of the last row we
 * put on every iteration: dp[i][j] wiht 1 <= i <= n, j = 0/1.
 * dp[i][j] represents the number of ways to construct a tower
 * with i rows that ends in a 'row-type' j (Disjoint/0 or Connected/1).
 * 
 * Then dp[i][0] can be calculated as the sum of:
 * ------> We can extend the left-side of the last (i-1) row's Disjoint 
 *         structure: dp[i][0] += dp[i-1][0];
 * ------> We can extend the right-side of the last (i-1) row's Disjoint
 *         structure: dp[i][0] += dp[i-1][0];
 * ------> We can extend both left and right side of the last (i-1) row's
 *         Disjoint structure simultaneously: dp[i][0] += dp[i-1][0];
 * ------> We can just put a new disjoint row that does not extend any
 *         column of the last row: dp[i][0] += dp[i-1][0] + dp[i-1][1];
 * 
 * To calculate dp[i][1]:
 * ------> We can extend the last (i-1) row's Connected structure: dp[i][1] += dp[i-1][1];
 * ------> We can just put a new Connected row without extending the last
 *         Connected row: dp[i][1] += dp[i-1][1];
 * ------> We can also just put a new Connected row without extending the last
 *         Disjoint row: dp[i][1] += dp[i-1][0]
 * 
 * The final answer is then simply: dp[n][0] + dp[n][1]
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6;
const int MOD = 1e9+7;

int t, n, dp[N+1][2];

int main(){
  dp[1][0] = dp[1][1] = 1;
  for(int i=2; i<=N; i++){
    dp[i][0] = ((4LL * dp[i-1][0]) % MOD + dp[i-1][1]) % MOD;
    dp[i][1] = ((2LL * dp[i-1][1]) % MOD + dp[i-1][0]) % MOD;
  }
  scanf("%d", &t);
  while(t--){
    scanf("%d", &n);
    printf("%d\n", (dp[n][0] + dp[n][1]) % MOD);
  }
  
  return 0;
}
