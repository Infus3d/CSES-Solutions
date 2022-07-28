/*
 * Problem link : https://cses.fi/problemset/task/1725
 * Prereq: 
 * ---> Basic understanding of probabilities:
 *      https://cses.fi/book/book.pdf   (Chapter 24, first 3 sections)
 * 
 * We can solve this problem easily using dynamic programming. Let us have a dp[][]
 * array with dp[i][j] representing the probability of the sum amount j after i dice
 * rolls. For ex: dp[1][0] = 0, dp[1][1] = dp[1][4] = 1/6 and dp[2][2] = 1/36, etc.
 * Transition between the dp states is farily straightforward - to calculate dp[i][j]:
 * ----> We note that the sum we are trying to reach is j on i'th roll. On each roll
 *       we can have a score of 1...6 so from (i-1)'th roll to i'th roll the sum can change
 *       by values 1...6. Let's say that on the i'th roll we got the score k, then all we 
 *       need to do is dp[i][j] += dp[i-1][j-k] / 6. This means that we just take the probability
 *       of sum (j-k) on the previous dice roll and divide by 6 because k has a chance of 1/6.
 * 
 * The answer is then just the sum of the range dp[n][a] + dp[n][a+1] + ... dp[n][b-1] + dp[n][b].
 * Runtime O(n^2) here the constant is 6 but we ignore it in big-O.
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  
  vector<vector<double>> dp(n+1, vector<double>(6*n+1));
  dp[0][0] = 1;
  
  for(int i=1; i<=n; i++){
    for(int j=i; j<=6*i; j++){
      for(int k=1; k<=min(6, j); k++)
        dp[i][j] += dp[i-1][j-k]/6.0;
    }
  }
  
  double ans = 0.0;
  for(int i=a; i<=b; i++)
    ans += dp[n][i];
  printf("%.6lf\n", ans);
  
  return 0;
}

