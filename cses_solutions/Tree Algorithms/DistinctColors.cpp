/*
 * Problem link : https://cses.fi/problemset/task/1139
 * Prereq: 
 * Fenwick or Segment tree:
 * -----> https://cp-algorithms.com/data_structures/fenwick.html
 * -----> https://cp-algorithms.com/data_structures/segment_tree.html
 * Euler Tour Tehcnique (flattening the tree):
 * -----> https://usaco.guide/gold/tree-euler?lang=cpp
 * 
 * I strongly recommend solving the easier version of this problem first:
 * https://cses.fi/problemset/task/1734
 * 
 * After flattening the tree using Euler Tour Technique, the problem turns into a range distinct query
 * problem: given an array of n integers a[] and n queries in the form {l, r} --> find the number of distinct
 * integers in the range a[l, r]. This is the same problem as Distinct Values Queries and the link to the problem
 * is given above. You can find the solution of this problem in Range Queries section.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, cnt, d[N], ans[N];
int in[N], out[N], fen[N];
vector<int> E[N], Queries[N];
vector<int> ordered;
map<int, int> lastVisited;

void dfs(int u, int par){
  in[u] = ++cnt;
  ordered.push_back(u);
  for(int v : E[u])
    if(v != par)
      dfs(v, u);
  out[u] = cnt;
}

void add(int x, int val){
  while(x <= cnt){
    fen[x] += val;
    x += x & (-x);
  }
}

int sum(int x){
  int res = 0;
  while(x > 0){
    res += fen[x];
    x -= x & (-x);
  }
  return res;
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<=n; i++)
    scanf("%d", &d[i]);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  dfs(1, 0);
  for(int i=1; i<=n; i++)
    Queries[out[i]].push_back(i);
  
  for(int i=1; i<=n; i++){
    int curVal = d[ordered[i-1]];
    if(lastVisited.find(curVal) != lastVisited.end()) //if it has been seen before
      add(lastVisited[curVal], -1);
    
    lastVisited[curVal] = i;
    add(i, +1);
    
    for(int idx : Queries[i]){
      int j = in[idx];
      ans[idx] = (sum(i) - sum(j-1));
    }
  }
  
  for(int i=1; i<=n; i++)
    printf("%d ", ans[i]);
  
  return 0;
}
