/*
 * Problem link : https://cses.fi/problemset/task/1696/
 * 
 * The bipartite matching problem can be solved with max-flow algorithm.
 * In this problem, we have a bipartite graph with boys as the first set of nodes
 * and girls as the other set. There won't be any edges between the nodes in the
 * same set, that is no boy-boy or girl-girl potential pairs (sadly).
 * 
 * As there is no obvious starting node (source) and ending node (sink) for us to
 * run a flow algorithm on, we can create them! We can add those nodes and determine
 * the maximum flow of the graph which will be the maximum number of pairings too.
 * 
 * Please refer to the wonderful explanation on this book to understand how this works:
 * https://cses.fi/book/book.pdf    (Chapter 20, Maximum matchings)
 * 
 * To locate the pairs, we can go through the initial edges a --> b and see if the cost
 * of that edge (capacity[a][b]) is fully used, that is if it is equal to 0.
 * 
 * Runtime O((n+m)*k^2)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e3+2;

int capacity[N][N];
int n, m, k, parent[N];
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
  scanf("%d%d%d", &n, &m, &k);
  for(int i=0; i<k; i++){
    int a, b; 
    scanf("%d%d", &a, &b);
    
    b += n;
    if(!capacity[a][b]){
      E[a].push_back(b);
      E[b].push_back(a);
      
      capacity[a][b] = 1;
      allEdges.push_back({a, b});
    }
  }
  
  int stNode = 0, enNode = n+m+1;
  for(int i=1; i<=n; i++){
    E[stNode].push_back(i);
    E[i].push_back(stNode);
    capacity[stNode][i]++;
  }
  for(int i=n+1; i<=n+m; i++){
    E[i].push_back(enNode);
    E[enNode].push_back(i);
    capacity[i][enNode]++;
  }
  
  int flow = 0, new_flow = 0;
  while((new_flow = bfs(stNode, enNode))){
    flow += new_flow;
    int cur = enNode;
    
    while(cur != stNode){
      int prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
      cur = prev;
    }
  }
  
  vector<pair<int, int>> ans;
  for(auto [u, v] : allEdges)
    if(capacity[u][v] == 0)
      ans.push_back({u, v});
  
  //~ printf("flow -> %d\n", flow);
  printf("%d\n", (int)ans.size());
  for(auto [i, j] : ans)
    printf("%d %d\n", i, j-n);
  
  return 0;
}
