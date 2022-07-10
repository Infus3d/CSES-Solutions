/*
 * Problem link : https://cses.fi/problemset/task/1686
 * Prereq:
 * -----> Strongly Connected Components:
 *        https://cses.fi/book/book.pdf    (Section 17.1)
 *
 * Let us imagine the strongly-connected-components in the graph as a single node
 * as we can travel from any node to any other node in this component, the cost of
 * the united component/node will be just the sum of all of its nodes.
 * 
 * Now we have a new graph nodes of which are SCC's of the older graph connected by
 * some of the edges that are not inside SCC's. This graph is now acyclic as we took
 * care of all cycles in the graph. This means that we can just do a topological sort
 * on the graph and calculate the cost on the sorted resulting array with basic DP.
 * Please refer to either the solution of Investigation problem or the following book
 * to understand how you can do such DP:
 * https://cses.fi/book/book.pdf   (Section 16.2)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, vis[N], comp[N];
long long compCost[N], coins[N], score[N];
vector<int> ordered;
vector<int> E[N], rE[N], newE[N];

void dfs(int u){
  vis[u] = 1;
  for(auto v : E[u])
    if(!vis[v])
      dfs(v);
  ordered.push_back(u);
}

void dfs2(int u, int id){
  comp[u] = id;
  for(auto v : rE[u])
    if(!comp[v])
      dfs2(v, id);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=1; i<=n; i++) scanf("%lld", &coins[i]);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    rE[b].push_back(a);
  }
  
  for(int i=1; i<=n; i++)
    if(!vis[i])
      dfs(i);
  
  int cnt = 0;
  for(int i=0; i<n; i++){
    int u = ordered[n-i-1];
    if(comp[u] == 0)
      dfs2(u, ++cnt);
  }
  
  for(int u=1; u<=n; u++){
    compCost[comp[u]] += coins[u];
    for(int v : E[u])
      if(comp[u] != comp[v])
        newE[comp[u]].push_back(comp[v]);
  }
  
  for(int u=1; u<=cnt; u++){
    score[u] = max(score[u], compCost[u]);
    for(int v : newE[u])
      if(score[v] < score[u] + compCost[v])
        score[v] = score[u] + compCost[v];
  }
  
  long long ans = 0;
  for(int i=1; i<=cnt; i++)
    ans = max(ans, score[i]);
  printf("%lld\n", ans);
  
  return 0;
}
