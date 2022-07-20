/*
 * Problem link : https://cses.fi/problemset/task/2080
 * Prereq:
 * Centroid Decomposition:
 * ---> https://robert1003.github.io/2020/01/16/centroid-decomposition.html
 * 
 * The solution below was adapted from the following tutorial:
 * https://usaco.guide/problems/cses-2080-fixed-length-paths-i/solution
 * 
 * I strongly recommend going through the tutorial above and the solution editorial to fully
 * understand the concept.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, k, subtree[N]; //subtree[u] is the number of nodes in u's subtree
vector<int> E[N];

long long ans;
int maxDepth, cnt[N];
bool processed[N];

int get_subtree_sizes(int u, int par){
  subtree[u] = 1;
  for(int v : E[u])
    if(!processed[v] && v != par)
      subtree[u] += get_subtree_sizes(v, u);
  
  return subtree[u];
}

int get_centroid(int u, int par, int limit){
  for(int v : E[u])
    if(!processed[v] && v != par && subtree[v] > limit)
      return get_centroid(v, u, limit);
  
  return u;
}

void get_cnt(int u, int par, bool filling, int depth){
  if(depth > k) return;
  maxDepth = max(maxDepth, depth);
  if(filling == true)
    cnt[depth]++;
  else
    ans += cnt[k - depth];
  
  for(int v : E[u])
    if(!processed[v] && v != par)
      get_cnt(v, u, filling, depth+1);
}

void centroid_decomposition(int u){
  int centroid = get_centroid(u, 0, get_subtree_sizes(u, 0)/2);
  processed[centroid] = true;
  
  maxDepth = 0;
  for(int v : E[centroid])
    if(!processed[v]){
      get_cnt(v, centroid, false, 1);
      get_cnt(v, centroid, true, 1);
    }
  
  fill(cnt+1, cnt+maxDepth+1, 0); //cnt[0] = 1 stays the same
  for(int v : E[centroid])
    if(!processed[v])
      centroid_decomposition(v);
}

int main(){
  scanf("%d%d", &n, &k);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  cnt[0] = 1;
  centroid_decomposition(1);
  printf("%lld\n", ans);
  
  return 0;
}
