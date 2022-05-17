/*
 * Problem link : https://cses.fi/problemset/task/1745
 * Thorough explanation : https://codeforces.com/blog/entry/70018
 * (You might need to scroll down to locate the problem)
 * Runtime O(n^2 * x)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e2;
const int K = 1e3;

int n, x[N];
bool dp[N*K+1];

int main(){
  scanf("%d", &n);
  for(int i=0; i<n; i++) 
    scanf("%d", &x[i]);
  
  dp[0] = true; //we assume it is possible to '0'
  for(int j=0; j<n; j++){
    for(int i=N*K; i>=0; i--){
      //this basically means 'if we can construct i and i+current_x is within limit, then we can construct it as well
      if(dp[i] == true && (i + x[j]) <= N*K) 
        dp[i + x[j]] = true;
    }
  }
  
  /* We collect the possible
   * numbers that can be constructed
   * */
  vector<int> possible;
  for(int i=1; i<=N*K; i++)
    if(dp[i] == true)
      possible.push_back(i);
  
  printf("%d\n", (int)possible.size());
  for(int i : possible)
    printf("%d ", i);
  puts("");
  
  return 0;
}
