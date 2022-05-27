/*
 * Problem link : https://cses.fi/problemset/task/2216
 * 
 * if you observe a sample:
 * 7 5 6 8 4 2 3 1
 * 
 * with collecting rounds:
 * 1
 * 2 3
 * 4
 * 5 6
 * 7 8
 * 
 * You can observe that the last element of each round is 1 less
 * than the first element of the next round. This implies that whenever
 * we have two elements i, i+1 with position[i+1] < position[i] in the
 * array, then we need to start a new round for i+1. So we simply
 * count the number of such consecutive pairs in the array.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<int> pos(n+1);
  for(int i=1; i<=n; i++){
    int a; scanf("%d", &a);
    pos[a] = i;
  }
  
  int ans = 1;
  for(int i=2; i<=n; i++)
    if(pos[i] < pos[i-1])
      ans++;
  printf("%d\n", ans);
  
  return 0;
}
