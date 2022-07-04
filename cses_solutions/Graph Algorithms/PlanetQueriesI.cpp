/*
 * Problem link : https://cses.fi/problemset/task/1750
 * Prereq: Binary lifting/jumping
 * https://usaco.guide/plat/binary-jump?lang=cpp
 * 
 * The input in this problem is a special kind of graph called functional or successor
 * graph since each node has only 1 successor - the node that they 'point' to.
 * Interesting thing about successor graph is that it consists of multiple
 * components where each component has exactly one 'central' cycle that the rest of
 * the nodes [that are not in this cycle, but in this component] point towards. To see
 * this, just write down a random permutation of n numbers and draw edges between
 * node i and node perm[i] on a piece of paper. Try a few of these permutation to fully
 * understand how these graphs look.
 * 
 * The aforementioned functionality of successor graphs makes it obvious that there will always
 * be k'th successor of any node in the graph for all k (1 <= k <= infinity). So we can use
 * what is known as binary lifting to find such k'th successor as requested in this problem.
 * 
 * We pre-calculate the successor table and for each query i, we just binary lift x[i] by k[i]
 * times to get to the k[i]'th successor of x[i].
 * 
 * Runtime O((n+q)*log(max_k)) where max_k is 1e9 in this problem
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, succ[N][30];

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &succ[i][0]);
  
  for(int j=1; j<30; j++)
    for(int i=1; i<=n; i++)
      succ[i][j] = succ[succ[i][j-1]][j-1];
  
  while(q--){
    int x, k;
    scanf("%d%d", &x, &k);
    
    for(int i=29; i>=0; i--)
      if(k >= (1 << i)){
        k -= (1 << i);
        x = succ[x][i];
      }
    
    printf("%d\n", x);
  }
  return 0;
}
