/*
 * Problem link : https://cses.fi/problemset/task/1636
 * Tutorial : https://codeforces.com/blog/entry/70018
 * 
 * The only difference of this problem with Coin Combinations I
 * is that the adding order of the coins is specified. Each element
 * must be less than or equal to the next element in the addition order:
 * {2, 2, 2, 3} is allowed but {2, 2, 3, 2} is not counted although they
 * both sum up to 9.
 * 
 * Code-wise the only difference is the order of the two loops that calculate
 * dp. Notice how the loop for(j<n) is the outer loop now. By doing so we guarantee
 * that the element j+1 is added only after all combinations of elements 0...j have
 * been counted.
 * Runtime O(n*x)
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
  for(int j=0; j<n; j++){
    for(int i=1; i<=x; i++)
      if(i-c[j] >= 0)
        dp[i] = (dp[i] + dp[i-c[j]]) % MOD;
  }
  printf("%d\n", dp[x]);
  
  return 0;
}
