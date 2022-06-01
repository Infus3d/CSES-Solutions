/*
 * Problem link : https://cses.fi/problemset/task/1629
 * 
 * We can sort the given intervals by their right end b[i] values
 * and choose the intervals greedily. We should always choose the
 * interval i (in sorted order) if the right end of our last chosen
 * interval j (b[j]) is smaller than left end of i (a[i]). This
 * guarantees that the maximum number of movies is watched overall.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<pair<int, int>> movie(n);
  for(int i=0; i<n; ++i){
    int a, b;
    scanf("%d%d", &a, &b);
    movie[i] = {b, a};
  }
  sort(movie.begin(), movie.end());
  
  int curR = 0, ans = 0;
  for(int i=0; i<n; i++){
    int a = movie[i].second, b = movie[i].first;
    if(curR <= a)
      curR = b, ans++;
  }
  printf("%d\n", ans);
  
  return 0;
}
