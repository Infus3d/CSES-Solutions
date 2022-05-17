/*
 * Probem link : https://cses.fi/problemset/task/1637
 * Tutorial : https://codeforces.com/blog/entry/70018
 * 
 * We can maintain a dp[i] that contains the minimum number
 * of moves needed to bring i to 0.
 * On every iteration i we can simply consider all of its
 * digits j and see if subtracting j results in a smaller
 * moves than current dp[i] by dp[i] = min(dp[i], dp[i-j]+1)
 * 
 * Answer is dp[n]
 * Runtime O(n*m) where m = digit count of n
 * */
#include "bits/stdc++.h"

using namespace std;

int n, dp[(int)(1e6)+1];

vector<int> getDigits(int x){
  vector<int> ret;
  while(x > 0){
    ret.push_back(x % 10);
    x /= 10;
  }
  return ret;
}

int main(){
  scanf("%d", &n);
  for(int i=0; i<=n; i++) dp[i] = n+1;
  
  dp[0] = 0;
  for(int i=1; i<=n; i++){
    vector<int> digits = getDigits(i);
    
    for(int j : digits)
      if(i-j < i && i-j >= 0)
        dp[i] = min(dp[i], dp[i-j] + 1);
  }
  printf("%d\n", dp[n]);
  
  return 0;
}
