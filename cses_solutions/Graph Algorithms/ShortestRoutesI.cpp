/*
 * Problem link : https://cses.fi/problemset/task/1671
 * 
 * The problem literally asks us to implement the Dijkstra's Algorithm that
 * finds the shortest distances from the source node to any other reachable
 * node in the graph in a very efficient manner.
 * You can learn about Dijkstra by referring to the wonderful book:
 * https://cses.fi/book/book.pdf  Page(126)
 * 
 * Runtime O(n + m*logn(m))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, vis[N];
long long cost[N];
vector<pair<int, int>> E[N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    E[a].push_back({b, c});
  }
  
  set<pair<long long, int>> Q;
  
  Q.insert({0LL, 1});
  for(int i=2; i<=n; i++)
    cost[i] = LLONG_MAX; //setting the initial costs to infinity, except for the initial node
  
  while(!Q.empty()){
    int u = Q.begin()->second;
    Q.erase(Q.begin());
    
    if(vis[u] == 1) continue;
    vis[u] = 1;
    
    for(auto i : E[u]){
      int v = i.first, c = i.second;
      if(cost[u] + c < cost[v]){
        cost[v] = cost[u] + c;
        Q.insert({cost[v], v});
      }
    }
  }
  
  for(int i=1; i<=n; i++)
    printf("%lld ", cost[i]);
  puts("");
  
  return 0;
}
