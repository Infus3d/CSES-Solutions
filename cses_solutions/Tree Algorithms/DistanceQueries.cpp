/*
 * Problem link : https://cses.fi/problemset/task/1135
 * Prereq:
 * Lowest Common Ancestor and Binary Lifting:
 * ----> https://www.youtube.com/watch?v=dOAxrhAUIhA  <-------- Hopefully you won't need to read other sources after this video
 *       https://cses.fi/book/book.pdf  (Chapter 18)
 *       https://cp-algorithms.com/graph/lca_binary_lifting.html
 *       https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor
 * 
 * I recommend solving Company Queries II before attempting this problem as it is a direct subproblem
 * of this problem.
 * 
 * As the cost of edges is monotone in the tree - each being just 1 - we can simply find the lowest
 * common ancestor of the two nodes u and v in the query and find the distance between them using
 * the depth[] values of lca and nodes u and v.
 * The distance would be the depth difference between u and lca(u, v) added onto the depth difference
 * between v and lca(u, v): depth[u] + depth[v] - 2*depth[lca(u, v)].
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, depth[N], P[N][18];
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

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  dfs(1, 0);
  build_lca();
  
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    int theLCA = lca(a, b);
    printf("%d\n", (depth[a] - depth[theLCA]) + (depth[b] - depth[theLCA]));
  }
  
  return 0;
}
