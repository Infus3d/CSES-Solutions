/*
 * Problem link : https://cses.fi/problemset/task/1682
 * Prereq : DFS  ->  https://cses.fi/book/book.pdf   (Section 12.1)
 * 
 * There is a theorem that claims if a node u can both reach and be reached by all other nodes
 * in the directed graph, then every node can reach all others.
 * The theorem makes sense because in a directed graph where each node can reach all other nodes,
 * it has to be that one specific node u can reach all other nodes and all other nodes can also
 * reach the node u. Let's take arbitrary nodes v and s where node v is reachable by node u,
 * and node u is reachable by node s. Then, it is the case that node s also reaches node v. The
 * converse is also true from our assumption that node u reaches and is reachable by all other nodes,
 * 
 * To implement, we just need to select an arbitrary node u (in thecode below it's chosen to be node 1).
 * We run the first DFS to check if node 1 can reach all other nodes. Then, we can reverse the edges in the
 * graph and run an analogous DFS from node 1 to check if all other nodes can also reach node 1. We will need
 * two visited[] arrays for this.
 * 
 * Finally, if both visited[] arrays are 1 for all nodes in the graph, then the answer is YES. If it is
 * not the case for at least one node, then that node and 1 are not mutually reachable.
 * 
 * Runtime O(n + m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, vis[N][2];
vector<int> E[N][2];

void dfs(int u, int t){
  vis[u][t] = 1;
  
  for(int v : E[u][t])
    if(vis[v][t] == 0)
      dfs(v, t);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a][0].push_back(b);
    E[b][1].push_back(a);
  }
  
  dfs(1, 0);
  dfs(1, 1);
  
  for(int i=1; i<=n; i++)
    if(!vis[i][0] || !vis[i][1]){
      int a = 1, b = i;
      if(!vis[i][1])  swap(a, b);
      puts("NO");
      printf("%d %d\n", a, b);
      return 0;
    }
  
  puts("YES");
  
  return 0;
}
