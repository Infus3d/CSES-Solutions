/*
 * Problem link : https://cses.fi/problemset/task/1639
 * Thorough explanation : https://codeforces.com/blog/entry/70018
 * (You might need to scroll down to locate the problem)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 5e3+2;

int n, m;
char a[N], b[N];
int dp[N][N];

int main(){
  scanf("%s", a); n = strlen(a);
  scanf("%s", b); m = strlen(b);
  
  for(int i=0; i<=n; i++){
    for(int j=0; j<=m; j++){
      dp[i][j] = (i == 0 && j == 0 ? 0 : (int)1e9);
      if(i > 0) dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
      if(j > 0) dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
      if(i > 0 && j > 0) dp[i][j] = min(dp[i][j], dp[i-1][j-1] + (a[i-1] != b[j-1]));
    }
  }
  printf("%d\n", dp[n][m]);
  
  return 0;
}
