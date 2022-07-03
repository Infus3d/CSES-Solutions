/*
 * Problem link : https://cses.fi/problemset/task/1202
 * Prereq: Dijstra's Algorithm
 * https://cses.fi/book/book.pdf  (Section 13.2)
 * 
 * We can use Dijkstra's Algorithm to find the minimal cost of routes from 1 to every node
 * in the graph. During the process, we also keep additional arrays:
 * ----> cost[u] contains the minimal cost over all routes from 1 to u
 * ----> pathCnt[u] contains the number of routes from 1 to u with cost cost[u]
 * ----> minNodeCnt[u] contains the minimal number of edges in the route over all routes
 *       with cost cost[u]
 * ----> maxNodeCnt[u] contains the maximal number of edges in the route over all routes
 *       with cost cost[u]
 * 
 * These are all dp-principled arrays, including cost[u] that is present in a normal Dijkstra's
 * Algorithm. The transitions of these dp states are not difficult. Let's say that we are at
 * node u in Dijkstra loop:
 * -------> We know from the algorithm that cost[u] at this moment contains the minimal possible
 *          price over all routes from 1 to u.
 * -------> Going through all neighbors v of u with edge_cost_u_v = w:
 * ------------> if cost[v] > cost[u] + w then route from u to v is cheaper than any other route
 *               to v so far, so node v 'inherits' the dp values of node u:
 * --------------------> cost[v] = cost[u] + w obviously, just like in normal Dijkstra's
 * --------------------> pathCnt[v] = pathCnt[u] because all the routes with minimal cost that lead
 *                       to v so far are from u.
 * --------------------> minNodeCnt[v] = minNodeCnt[u] + 1 because we need to add the new edge from
 *                       u to v.
 * --------------------> maxNodeCnt[v] = maxNodeCnt[u] + 1 same as above.
 * ------------> if cost[v] == cost[u] + w then we have found another way to reach v with the same
 *               cost. So we just update the dp arrays of node v:
 * --------------------> pathCnt[v] = pathCnt[v] + pathCnt[u] (mod 1e9+7) becase all routes counted
 *                       in pathCnt[u] are disjoint from all routes counted in pathCnt[v] so we can
 *                       just add them to get the total.
 * --------------------> minNodeCnt[v] = min(minNodeCnt[v], minNodeCnt[u]+1) we just take the minimum
 *                       of the two.
 * --------------------> maxNodecnt[v] = max(maxNodeCnt[v], maxNodecnt[u]+1) we just take the maximum
 *                       of the two.
 * 
 * We print the values of the arrays at node n as an answer.
 * 
 * Runtime O(n + m*log(m))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;
const int MOD = 1e9+7;

int n, m, pathCnt[N], minNodeCnt[N], maxNodeCnt[N], vis[N];
long long cost[N];
vector<pair<int, int>> E[N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    E[a].push_back({b, c});
  }
  
  for(int i=1; i<=n; i++){
    cost[i] = (long long) 1e15;
    minNodeCnt[i] = n+1;
    //we also need maxNodeCnt[i] = 0 and pathCnt[i] = 0 but they are already 0
  }
  
  set<pair<long long, int>> Q;
  
  cost[1] = 0;
  pathCnt[1] = 1;
  minNodeCnt[1] = 0;
  maxNodeCnt[1] = 0;
  Q.insert({0, 1});
  
  while(!Q.empty()){
    auto [c, u] = *Q.begin();
    Q.erase(Q.begin());
    
    if(vis[u]) continue;
    vis[u] = 1;
    
    for(auto [v, w] : E[u]){
      if(cost[v] > cost[u] + w){
        Q.insert({cost[u] + w, v});
        
        cost[v] = cost[u] + w;
        pathCnt[v] = pathCnt[u];
        minNodeCnt[v] = minNodeCnt[u] + 1;
        maxNodeCnt[v] = maxNodeCnt[u] + 1;
      }
      else if(cost[v] == cost[u] + w){
        pathCnt[v] = (pathCnt[v] + pathCnt[u]) % MOD;
        minNodeCnt[v] = min(minNodeCnt[v], minNodeCnt[u] + 1);
        maxNodeCnt[v] = max(maxNodeCnt[v], maxNodeCnt[u] + 1);
      }
    }
  }
  
  printf("%lld %d %d %d\n", cost[n], pathCnt[n], minNodeCnt[n], maxNodeCnt[n]);
  
  return 0;
}
