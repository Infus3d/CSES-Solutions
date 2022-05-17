/*
 * Problem link : https://cses.fi/problemset/task/1638
 * Tutorial : https://codeforces.com/blog/entry/70018
 * 
 * This is farily simple grid-dp where we have only 2
 * types of cells: empty and blocked (or trapped).
 * Since we are allowed to move only right or down, we
 * can calculate the number of ways by iterating first
 * row-by-row then column-by-column (in each row).
 * We will maintain a 2-dimensional dp state dp[i][j]
 * that contains the number of ways to get from (0, 0)
 * to (i, j):
 * -----} if current cell is empty:
 * ------------> if it is not the topmost row, then one can come into
 *               the cell (i, j) from the top: dp[i][j] += dp[i-1][j]
 * 
 * ------------> if it is not the leftmost column, then one can come into
 *               the cell (i, j) from the left: dp[i][j] += dp[i][j-1]
 * 
 * -----} if current cell is trapped, then dp[i][j] = 0
 * 
 * Final answer will then be dp[n-1][n-1]
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e3;
const int MOD = 1e9+7;

int n, dp[N][N];
char s[N][N];

int main(){
  scanf("%d", &n);
  for(int i=0; i<n; i++)
    scanf("%s", s[i]);
  
  dp[0][0] = 1;
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++){
      if(s[i][j] == '.'){ //if we can move to this block
        if(i > 0)
          dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD; //one can come from the top
        if(j > 0)
          dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD; //one can come from the left
      }
      else //if the cell has a trap
        dp[i][j] = 0;
    }
  
  printf("%d\n", dp[n-1][n-1]);
  
  return 0;
}
