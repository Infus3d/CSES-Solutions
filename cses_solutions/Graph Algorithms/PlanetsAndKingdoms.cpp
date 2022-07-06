/*
 * Problem link : https://cses.fi/problemset/task/1683
 * 
 * The problem asks to find strongly connected components in the given directed graph.
 * Strongly connected components are a set of nodes and vertices, where each node in that
 * component is reachable by all other nodes in the component.
 * 
 * There are 2 well-known algorithms for finding SCC's: Kosaraju's and Tarjan's.
 * The code is the direct application of Kosaraju's algorithm on the given graph.
 * 
 * You can learn about SCC's via following:
 * https://cses.fi/book/book.pdf                 (Chapter 17)
 * https://www.youtube.com/watch?v=Rs6DXyWpWrI   (Kosaraju's algo, With code)
 * https://www.youtube.com/watch?v=HOOmetF56BI   (Kosaraju's algo, with pseudo-code but more in-depth)
 * 
 * Runtime O(n+m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, comp[N], vis[N];
vector<int> ordered;
vector<int> E[N], rE[N]; //rE -> reversed edge

void dfs(int u){
  vis[u] = 1;
  for(int v : E[u])
    if(vis[v] == 0)
      dfs(v);
  ordered.push_back(u);
}

void dfs2(int u, int id){
  comp[u] = id;
  for(int v : rE[u])
    if(comp[v] == 0)
      dfs2(v, id);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    rE[b].push_back(a);
  }
  
  for(int i=1; i<=n; i++)
    if(vis[i] == 0)
      dfs(i);
  
  int cnt = 0;
  reverse(ordered.begin(), ordered.end());
  for(int u : ordered)
    if(comp[u] == 0)
      dfs2(u, ++cnt);
  
  printf("%d\n", cnt);
  for(int i=1; i<=n; i++)
    printf("%d%c", comp[i], " \n"[i == n]);
  
  return 0;
}
