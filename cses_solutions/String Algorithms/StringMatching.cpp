/*
 * Problem link : https://cses.fi/problemset/task/1753
 * Prereq: Knuth-Morris-Pratt or Z-function algorithms
 * https://cp-algorithms.com/string/prefix-function.html
 * https://cp-algorithms.com/string/z-function.html
 * 
 * We need to find the number of occurrences of string t inside string s.
 * This is the problem that is introduced in the tutorials of KMP or Z-function
 * so please refer to the above links to learn them.
 * 
 * You can also solve it with polynomial hashing in O(n):
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
  
  string s, t;
  cin >> s >> t;
  int n = s.length(), m = t.length();
  t = t + "#" + s;
  
  vector<int> pi = prefix_function(t);
  
  int ans = 0;
  for(int i=m+1; i<n+m+1; i++){
    if(pi[i] == m)
      ans++;
  }
  printf("%d\n", ans);
  
  return 0;
}
