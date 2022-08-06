/*
 * Problem link : https://cses.fi/problemset/task/1732
 * Prereq: Knuth-Morris-Pratt string searching algorithm
 * https://cp-algorithms.com/string/prefix-function.html
 * 
 * We can build the pi[] table of the string according to KMP algorithm and simply output
 * the values pi[n-1], pi[pi[n-1]-1], pi[pi[pi[n-1]-1]-1], ... because these are the exact
 * lengths of the prefixes of the string that are also the suffix, in decreasing order.
 * 
 * You can also solve it using Z-function in O(n):
 * https://cp-algorithms.com/string/prefix-function.html
 * 
 * Unsurprisingly, you can solve it with polynomial hashing in O(n) as well:
 * https://codeforces.com/blog/entry/60445
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

vector<int> prefix_function(string &s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  string s;
  cin >> s;
  int n = s.length();
  vector<int> pi = prefix_function(s);
  
  vector<int> ans;
  int cur = pi[n-1];
  while(cur > 0){
    ans.push_back(cur);
    cur = pi[cur-1];
  }
  
  for(int i=(int)ans.size()-1; i>=0; i--)
    printf("%d ", ans[i]);
  
  return 0;
}
