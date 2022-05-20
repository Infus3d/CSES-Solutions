/*
 * Problem link : https://cses.fi/problemset/task/1090
 * 
 * We can take the weights and sort them first. Then have a pointer
 * at the start l = 0 and at the end r = n-1. There can be 2 conditions
 * at any given state/iteration (answer starts from 0):
 * ------> weight[l] + weight[r] fits into maximum cabin weight x, so we can
 *         just put them together in a cabin. We increase the answer and do l++, r--.
 * 
 * ------> weight[l] + weight[r] is above x in which case we can put weight[r] in a
 *         cabin by itself and move on. We increase the answer and do r--.
 *         The reason we don't put weight[l] in a separate cabin is that if weight[l]+weight[r]
 *         is already greater than x, then weight[l+1]+weight[r] is guaranteed to be > x. But,
 *         weight[l] + weight[r-1] can still have a chance at <= x.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5;

int n, x, p[N];

int main(){
  scanf("%d%d", &n, &x);
  for(int i=0; i<n; i++)
    scanf("%d", &p[i]);
  sort(p, p+n);
  
  int l = 0, r = n-1, ans = 0;
  while(l < r){
    if(p[l] + p[r] <= x)
      l++, r--;
    else
      r--;
    ans++;
  }
  //if they both point to the same weight, then we have no choice but to put that child in a new cabin
  if(l == r)  ans++; 
  printf("%d\n", ans);
}
