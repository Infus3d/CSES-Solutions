/*
 * Problem link : https://cses.fi/problemset/task/1145
 * 
 * This is a famous problem known as longest increasing
 * subsequence. There are countless sources where you can
 * learn about the algorithm.
 * CSES book : https://cses.fi/book/book.pdf
 * wikipedia : https://en.wikipedia.org/wiki/Longest_increasing_subsequence#:~:text=In%20computer%20science%2C%20the%20longest,not%20necessarily%20contiguous%2C%20or%20unique.
 * CF blog : https://codeforces.com/blog/entry/70018
 * */

#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  
  vector<int> dp;
  for(int i=0; i<n; i++){
    int x; scanf("%d", &x);
    
    vector<int>::iterator it = lower_bound(dp.begin(), dp.end(), x);
    if(it == dp.end())
      dp.push_back(x);
    else
      *it = x; //we can access the element the iterator points to by *
  }
  printf("%d\n", (int)dp.size());
  
  return 0;
}
