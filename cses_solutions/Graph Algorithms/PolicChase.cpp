/*
 * Problem link : https://cses.fi/problemset/task/1695
 * 
 * If we imagine the cost of the edges as 1, the answer to the problem becomes
 * the min-cut of the graph. Minimum cut of the directed weighted graph is the
 * minimum sum of the weights of some edges such that when these edges are removed
 * there is no path from node 1 to node n. We can turn the undirected graph given
 * in the problem into a directed one by simply changing every edge into 2 one-way edges.
 * 
 * The max-flow algorithm also happens to find the min-cut of the graph. In fact, the
 * max-flow is also the min-cut of the graph. It is a well-known fact and you can 
 * refer to the following to understand it:
 * https://cses.fi/book/book.pdf  (Section 20.1)
 * https://cp-algorithms.com/graph/edmonds_karp.html#ford-fulkerson-method
 * 
 * After finding the max-flow (also the min-cut) we can run one final bfs and group
 * the nodes that can be reached from node 1 into set A and all other nodes into set B.
 * Now, any edge that leads from A to B is the edge that is minimum-cut arrangement.
 * 
 * Maybe simpler solution of this problem:
 * https://usaco.guide/problems/cses-1695-police-chase/solution
 * 
 * Runtime O(n*m^2)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 5e2+1;

int capacity[N][N];
int n, m, parent[N];
vector<int> E[N];
vector<pair<int, int>> allEdges;

int bfs(int st, int en){
  memset(parent, -1, sizeof(parent));
  parent[st] = -2;
  
  queue<pair<int, int>> Q;
  Q.push({st, INT_MAX});
  
  while(!Q.empty()){
    int u = Q.front().first;
    int flow = Q.front().second;
    Q.pop();
    
    for(int v : E[u]){
      if(parent[v] == -1 && capacity[u][v] > 0){
        parent[v] = u;
        int new_flow = min(flow, capacity[u][v]);
        if(v == en)
          return new_flow;
        Q.push({v, new_flow});
      }
    }
  }
  
  return 0;
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b; 
    scanf("%d%d", &a, &b);
    
    E[a].push_back(b);
    E[b].push_back(a);
    
    capacity[a][b]++;
    capacity[b][a]++;
    
    allEdges.push_back({a, b});
    allEdges.push_back({b, a});
  }
  
  int flow = 0, new_flow = 0;
  while((new_flow = bfs(1, n))){
    flow += new_flow;
    int cur = n;
    
    while(cur != 1){
      int prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
      cur = prev;
    }
  }
  
  bfs(1, n);
  
  vector<pair<int, int>> ans;
  for(auto [u, v] : allEdges)
    if(parent[u] != -1 && parent[v] == -1)
      ans.push_back({u, v});
  
  printf("%d\n", (int)ans.size());
  for(auto [i, j] : ans)
    printf("%d %d\n", i, j);
  
  return 0;
}
