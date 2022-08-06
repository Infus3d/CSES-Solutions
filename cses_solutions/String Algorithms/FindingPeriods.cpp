/*
 * Problem link : https://cses.fi/problemset/task/1733
 * Prereq: Either Knuth-Morris-Pratt Algorithm
 * https://cp-algorithms.com/string/prefix-function.html
 * 
 * We can get the prefix-array of the input string using KMP algorithm. Once we have pi[]
 * the answer will be (n-k) where k is the length of the all possible prefixes of s that are
 * also the suffixes of s (basically pi[] values). We can start with k = pi[n-1] to get the largest
 * length of such prefix, after which we will just use pi[] table to find the lower length such
 * prefixes: k = pi[k-1] which is unsurprisingly a simple KMP logic.
 * I recommend picking a string, building its pi[] table and testing the above so you can see why
 * it is correct.
 * 
 * Here is the explanation of the similar problem:
 * https://cp-algorithms.com/string/prefix-function.html#compressing-a-string
 * 
 * You can also solve it using Z-function in O(n) in a very similar way as KMP.
 * Alternately, you can solve it in O(n*log(n)) using polynomial hashing and binary-search.
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
  
  int cur = pi[n-1];
  while(cur > 0){
    printf("%d ", n-cur);
    cur = pi[cur-1];
  }
  printf("%d\n", n-cur);
  
  return 0;
}
