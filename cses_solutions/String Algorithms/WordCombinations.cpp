/*
 * Problem link : https://cses.fi/problemset/task/1731
 * Prereq: Trie structures
 * https://codeforces.com/blog/entry/68278
 * 
 * We can first insert all words into our trie that we need to construct the original string.
 * Then, we can calculate the number of ways to build the prefix of s[0...i] using O(n^2) dp
 * and store it in dp[i]. The final answer will be simply dp[n].
 * This dp is very much like a knapsack dp where we are given bunch of coins and need to find
 * the number of ways we can make the needed sum, except for in this problem we have strings
 * to match instead of coins.
 * 
 * Runtime O(n^2 + m) where m is the sum of the lengths of all words
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6+1;
const int M = 5e3+1;
const int MOD = 1e9+7;

int trie[N][26], a[N], dp[M], cnt;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  string s;
  cin >> s;
  int n = s.length();
  
  int k;
  cin >> k;
  while(k--){
    string t;
    cin >> t;
    int x = 0;
    for(char i : t){
      int c = i-'a';
      if(trie[x][c] == 0)
        trie[x][c] = ++cnt;
      x = trie[x][c];
    }
    a[x] = 1;
  }
  
  dp[0] = 1;
  for(int i=0; i<=n; i++){
    int x = 0;
    for(int j=i; j<n; j++){
      int c = s[j]-'a';
      if(trie[x][c] == 0)
        break;
      x = trie[x][c];
      if(a[x] != 0)
        dp[j+1] = (dp[j+1] + dp[i]) % MOD;
    }
  }
  printf("%d\n", dp[n]);
  
  return 0;
}
