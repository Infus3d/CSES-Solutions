/*
 * Problem link : https://cses.fi/problemset/task/1711
 * 
 * The problem asks us to find edge-distinct paths from node 1 to node n.
 * This value equals the maximum-flow of the given graph. It makes sense
 * because maximum-flow also equals the minimum cut of the graph and once
 * we use all edges in the minimum-cut there won't be any way to get from
 * node 1 to node n. Please refer to these links for better understanding:
 * 
 * https://cses.fi/book/book.pdf  (Section 20.2, Disjoint paths)
 * https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/edgedisjoint.pdf
 * 
 * We can print out the paths by simply going through the graph greedily
 * and marking each edge 'visited' to avoid printing it twice.
 * 
 * Runtime O(n*m^2) with Edmonds-Karp algorithm
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 5e2+1;

int capacity[N][N], ocapacity[N][N];
int n, m, parent[N];
vector<int> E[N];

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

void dfs(int u, vector<int> &path){
  path.push_back(u);
  if(u == n) return;
  
  for(int v : E[u])
    if(capacity[u][v] < ocapacity[u][v]){
      dfs(v, path);
      if(path.back() == n)
        return;
    }
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
    capacity[a][b]++;
    ocapacity[a][b]++;
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
  
  printf("%d\n", flow);
  while(flow--){
    vector<int> path;
    dfs(1, path);
    printf("%d\n", (int)path.size());
    for(int i : path)
      printf("%d ", i);
    puts("");
    
    for(int i=1; i<(int)path.size(); i++)
      capacity[path[i-1]][path[i]] = ocapacity[path[i-1]][path[i]]; //here we mark the edge path[i-1]-->path[i] visited
  }
  
  return 0;
}
