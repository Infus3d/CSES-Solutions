#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, m, depth[N], P[N][18], ans[N];
vector<int> E[N];

void dfs(int u, int par){
  depth[u] = depth[par]+1;
  P[u][0] = par;
  for(int v : E[u])
    if(v != par)
      dfs(v, u);
}

void build_lca(){
  for(int j=1; j<18; j++)
    for(int i=1; i<=n; i++)
      if(P[i][j-1] > 0)
        P[i][j] = P[P[i][j-1]][j-1];
}

int lca(int u, int v){
  if(depth[u] < depth[v])
    swap(u, v);
  
  for(int i=17; i>=0; i--)
    if(depth[u] - (1<<i) >= depth[v])
      u = P[u][i];
  
  if(u == v) return u;
  
  for(int i=17; i>=0; i--)
    if(P[u][i] != P[v][i])
      u = P[u][i], v = P[v][i];
  
  return P[u][0];
}

void upDFS(int u, int par){
  for(int v : E[u])
    if(v != par){
      upDFS(v, u);
      ans[u] += ans[v];
    }
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  dfs(1, 0);
  build_lca();
  
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    int c = lca(a, b);
    ans[c]--, ans[P[c][0]]--;
    ans[a]++, ans[b]++;
  }
  
  upDFS(1, 0);
  
  for(int i=1; i<=n; i++)
    printf("%d ", ans[i]);
  puts("");
  
  return 0;
}
