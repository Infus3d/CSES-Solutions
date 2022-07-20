/*
 * Problem link : https://cses.fi/problemset/task/2080
 * Prereq:
 * Centroid Decomposition:
 * ---> https://robert1003.github.io/2020/01/16/centroid-decomposition.html
 * 
 * The solution below was adapted from the following tutorial:
 * https://usaco.guide/problems/cses-2081-fixed-length-paths-ii/solution
 * 
 * This problem is just a little complicated version of the previous version of the problem
 * Fixed Length Paths I. In this solution, we just employ extra data structure (either segment
 * tree or fenwick tree) to be able to get the sum of the range [a, b] of the paths.
 * I strongly recommend going through the tutorial above and the solution editorial to fully
 * understand the concept.
 * 
 * Runtime O(n*log(n)^2)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+5;

int n, ka, kb, subtree[N]; //subtree[u] is the number of nodes in u's subtree
vector<int> E[N];

long long ans;
int maxDepth, cnt[N];
bool processed[N];

void add(int x, int val){
  for(x++; x<=n; x += x & (-x))
    cnt[x] += val;
}

long long query(int l, int r){
  long long res = 0;
  for(r++; r > 0; r -= r & (-r))
    res += cnt[r];
  
  for(; l > 0; l -= l & (-l))
    res -= cnt[l];
  
  return res;
}

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
  if(depth > kb) return;
  maxDepth = max(maxDepth, depth);
  if(filling == true)
    add(depth, +1);
  else
    ans += query(max(0, ka-depth), kb-depth);
  
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
  
  for(int i=1; i<=maxDepth; i++)
    add(i, -query(i, i));
  for(int v : E[centroid])
    if(!processed[v])
      centroid_decomposition(v);
}

int main(){
  scanf("%d%d%d", &n, &ka, &kb);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  add(0, 1);
  centroid_decomposition(1);
  printf("%lld\n", ans);
  
  return 0;
}
