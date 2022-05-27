/*
 * Problem link : https://cses.fi/problemset/task/2162
 * 
 * We can literally implement what the problem tells us to.
 * Starting from 1 through n we go in circles and mark/visit
 * every other unvisited number and print it out.
 * We can do this because on every full rotation around the circle
 * we visit/print half of it. As there are only n numbers initially,
 * there will be at most [exactly actually] log(n) rotation through
 * the circle.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<int> vis(n);
  
  int cnt = 0, p = 0, par = 0;
  while(cnt < n){
    if(!vis[p]){
      par ^= 1;
      if(!par){
        printf("%d ", p+1);
        vis[p] = 1;
        cnt++;
      }
    }
    p = (p+1) % n;
  }
  printf("\n");
  
  return 0;
}
