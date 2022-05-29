/*
 * Problem link : https://cses.fi/problemset/task/1630
 * Book link : https://cses.fi/book/book.pdf
 * 
 * The solution to the problem is explained on page 60 of section
 * 6.3 under Greedy Algorithms.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<pair<long long, long long>> a(n);
  for(int i=0; i<n; i++)
    scanf("%lld%lld", &a[i].first, &a[i].second);
  
  sort(a.begin(), a.end());
  long long ans = 0;
  for(int i=0; i<n; i++){
    if(i > 0) a[i].first += a[i-1].first;
    ans += a[i].second - a[i].first;
  }
  printf("%lld\n", ans);
  
  return 0;
}
