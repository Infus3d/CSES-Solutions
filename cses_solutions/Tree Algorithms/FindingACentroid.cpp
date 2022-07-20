/*
 * Problem link : https://cses.fi/problemset/task/2079/
 * 
 * Finding a centroid of a tree is the entry-level subproblem of building the centroid-tree
 * of the given tree. You can learn about both in this wonderful tutorial:
 * https://robert1003.github.io/2020/01/16/centroid-decomposition.html
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, subtree[N];
vector<int> E[N];

int getSubtreeSizes(int u, int par = 0){
  subtree[u] = 1;
  for(int v : E[u])
    if(v != par)
      subtree[u] += getSubtreeSizes(v, u);
  return subtree[u];
}

int getCentroid(int limit, int u, int par = 0){
  for(int v : E[u])
    if(v != par && subtree[v] > limit)
      return getCentroid(limit, v, u);
  return u;
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  printf("%d\n", getCentroid(getSubtreeSizes(1) / 2, 1));
  
  return 0;
}
