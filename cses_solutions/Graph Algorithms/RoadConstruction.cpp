/*
 * Problem link : https://cses.fi/problemset/task/1676
 * Prereq:
 * Disjoint Set Union&Find : 
 * https://cses.fi/book/book.pdf  (Section 15.2)
 * https://www.geeksforgeeks.org/disjoint-set-data-structures/
 * https://www.youtube.com/watch?v=ayW5B2W9hfo  (5 min video)
 * https://www.youtube.com/watch?v=axaOsCgpupk  (more in-depth explanation)
 * 
 * The problem becomes easy with Disjoint sets. Initially, all cities are disjoint sets of
 * themselves, totalling n sets at the start. When a road connects cities a and b, we union 
 * them into a single set as any city from a's disjoint set can access any city from b's 
 * disjoint set after the construction of the road. While doing that, since we know that the
 * two sets are disjoint we can just add their sizes to get the total size of the new bigger
 * set by inclusion-exclusion principle: 
 * |A| + |B| - |A Intersect B| = |A Union B|  -----> |A intersect B| here is 0
 * 
 * When we get the new size, we can just maximize it with whatever max set size we have so far
 * (initially 1, as every disjoint set contains only one city).
 * 
 * To get the number of components, we note that component number is the same as the number of 
 * disjoint sets. So we start off with n sets/components initially, and when we union two sets
 * we can just decrease the number by 1.
 * 
 * Runtime O(n+m*log(n)) is the best approximation of the time complexity of Disjoint Set DS.
 * The best asymptotic that can be achieved when all optimizations like path compression, halving,
 * union by size, etc. employed is O(n + m*alpha(n)) where alpha represents the inverse Ackermann function.
 * More about time complexity:
 * https://codeforces.com/blog/entry/98275
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m;
int par[N], siz[N];

int find(int x){
  if(par[x] == x)
    return x;
  return par[x] = find(par[x]);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=1; i<=n; i++){
    par[i] = i;
    siz[i] = 1;
  }
  
  int cnt = n, mxSize = 1;
  while(m--){
    int a, b;
    scanf("%d%d", &a, &b);
    
    //these function calls also 'flatten' the ancestry of both a and b, 
    //so we can just use par[a] and par[b] instead of find(a) and find(b) below
    if(find(a) != find(b)){ 
      if(siz[par[a]] < siz[par[b]])
        swap(a, b);
      
      siz[par[a]] += siz[par[b]];
      par[par[b]] = par[a];
      
      mxSize = max(mxSize, siz[par[a]]);
      cnt--;
    }
    
    printf("%d %d\n", cnt, mxSize);
  }
  return 0;
}
