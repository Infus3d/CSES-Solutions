/*
 * Problem link : https://cses.fi/problemset/task/1136
 * 
 * Prereq:
 * Lowest Common Ancestor and Binary Lifting:
 * ----> https://www.youtube.com/watch?v=dOAxrhAUIhA  <-------- Hopefully you won't need to read other sources after this video
 *       https://cses.fi/book/book.pdf  (Chapter 18)
 *       https://cp-algorithms.com/graph/lca_binary_lifting.html
 *       https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor
 * 
 * We can fix the root of the tree for an arbitrary node so let's choose node 1 as the root. Let's also build
 * lca table of the tree.
 * For each of the m paths between nodes u and v we can find their lca(u, v) = w and simulate increasing the count of each node
 * on this simple path from u to v by simple increasing the count of u and v by 1 (count[u]++, count[v]++) and decrease the
 * count of w by 1 (count[w]--) while also decreasing the count of parent[w] by 1 (count[parent[w]]--).
 * Now after we have done the above for every single one of m paths, we can initiate a dfs to 'sum up' these values so that
 * at the end of the dfs count[u] will contain the number of paths that cross node u. The dfs itself is fairly straightforward:
 * for every child v of node u, we just add their count[v] onto count of node u ----> count[u] += count[v].
 * So you can think of it as a from-bottom-to-up (towards the root) summation of the count values. This should also help you see
 * why we incremented node u and v values by +1: because by summing upwards late in the dfs, we add this +1 to every sinle node
 * on the path from u to lca(u, v) and from v to lca(u, v) at which point there is a single -1 to avoid double counting. We decreased
 * the parent[lca(u, v)] by 1 because the path from u to v does not extend anywhere beyond the lca(u, v).
 * 
 * Runtime O((n+m)*log(n))
 * */
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
