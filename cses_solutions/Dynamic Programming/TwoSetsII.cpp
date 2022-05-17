/* 
 * Problem link : https://cses.fi/problemset/task/1093
 * 
 * When we divide the numbers into two equal sum sets,
 * the sum of each set will be the half of total, where
 * total is n * (n+1) / 2.
 * 
 * This reduces the problem to: given numbers 1 through n
 * count how many ways you can achieve total/2 sum by using
 * each number no more than once.
 * The reduced problem is a 0-1 knapsack where the outer loop
 * iterates over the values we want to put into the set and
 * the inner loop iterates over the sums we have so far in our dp.
 * By going from maximum sum to minimum sum ensures that we use
 * each value once.
 * Runtime O(n^3)
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

int n, dp[(500 * 501)/2];

int main(){
  scanf("%d", &n);
  int totalSum = n * (n+1) / 2;
  int halfSum = totalSum / 2;
  
  dp[0] = 1;
  for(int j=1; j<n; j++){
    /* going from halfsum to 0 ensures we use each j once.
     * To see this, try modifying the loop from 0 to halfSum
     * and observe the behavior.
     * */
    for(int i=halfSum; i >= 0; i--)
      if(i + j <= halfSum)
        dp[i + j] = (dp[i + j] + dp[i]) % MOD;
  }
  
  if(totalSum % 2 == 1) //we can't divide into two equal sums when odd
    printf("0\n");
  else
    printf("%d\n", dp[halfSum]); 
  
  return 0;
}
