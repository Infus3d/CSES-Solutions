/* 
 * Problem link : https://cses.fi/problemset/task/1097
 * 
 * You can find a thorough explanation here:
 * https://codeforces.com/blog/entry/70018
 * 
 * Scroll down to locate the problem.
 * Runtime O(n^2)
 * */
#include "bits/stdc++.h"

using namespace std;
using ll = long long;

const int N = 5001;

int n;
ll dp[N][N], x[N], sum;

ll rec(int l, int r){
  if(l == r) 
    return x[l];
  
  ll &ret = dp[l][r];
  if(ret != -1LL) return ret;
  
  ll leftEnd = x[l] - rec(l+1, r);
  ll rightEnd = x[r] - rec(l, r-1);
  ret = max(leftEnd, rightEnd);
  
  return ret;
}

int main(){
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    scanf("%lld", &x[i]);
    sum += x[i];
  }
  
  memset(dp, -1LL, sizeof(dp));
  printf("%lld\n", (sum + rec(0, n-1))/2LL);
  
  return 0;
}
