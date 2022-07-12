/*
 * Problem link : https://cses.fi/problemset/task/1694
 * 
 * The problem asks to find the maximum flow from node 1 to node n in the given
 * directed positive weighted graph. There are numerous algorithms to find the
 * max-flow and the code below uses Edmonds-Karp algorithm. It is seen rather
 * as an optimization to Ford-Fulkerson's rough approach to find the flow.
 * You can read about them in the following sources:
 * https://cses.fi/problemset/task/1694   (Chapter 20)
 * https://cp-algorithms.com/graph/edmonds_karp.html#ford-fulkerson-method
 * 
 * Runtime O(n*m^2). Although this is the true asymptotic of the approach, in practice
 * it is much faster.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 5e2+1;

long long capacity[N][N];
int n, m, parent[N];
vector<int> E[N];

long long bfs(int st, int en){
  memset(parent, -1, sizeof(parent));
  parent[st] = -2;
  
  queue<pair<int, long long>> Q;
  Q.push({st, LLONG_MAX});
  
  while(!Q.empty()){
    int u = Q.front().first;
    long long flow = Q.front().second;
    Q.pop();
    
    for(int v : E[u]){
      if(parent[v] == -1 && capacity[u][v] > 0){
        parent[v] = u;
        long long new_flow = min(flow, capacity[u][v]);
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
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if(capacity[a][b] == 0LL){
      E[a].push_back(b);
      E[b].push_back(a);
    }
    capacity[a][b] += c;
  }
  
  long long flow = 0;
  long long new_flow = 0;
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
  
  printf("%lld\n", flow);
  
  return 0;
}
