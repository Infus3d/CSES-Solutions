/*
 * Problem link : https://cses.fi/problemset/task/1195
 * Prereq : Dijkstra's Algorithm for finding shortest path
 * https://cses.fi/book/book.pdf    (Page 126)
 * 
 * The naive approach would be to manually halve the cost of each edge and then
 * run Dijkstra's Algorithm to find the shortest path from 1 to all other nodes.
 * This would take total of O(m * (n + m*log(m))) which is too slow for m <= 2e5
 * constraint.
 * 
 * To make it faster, we can incorporate an easy dp into Dijkstra. Instead
 * of keeping just 1 array for the cost of the shortest path we would now need 2: cost[N][2]
 * where cost[u][0] is the cost of the shortest path from 1 to u with all edge weights kept
 * untouched (natural Dijkstra's cost) but cost[u][1] is the cost of the shortest path from
 * 1 to u with 1 of the edges (so far) halved. The answer to the problem then becomes cost[n][1].
 * 
 * Queue in this solution will consist of tuples (costSoFar, u, t) where costSoFar is the cost
 * of the path from 1 to u so far, u is the node and t is the 'type-indicator' that is described
 * above. t = 0 means we can use halving-coupon on the following edge, t = 1 means we can not.
 * 
 * Transitions from cost[u][t] : 
 * -------> t = 1 case: We look through all neighboring nodes v of u and check whether cost[v][1]
 *          is greater than cost[u][1] + cost_of_edge. If it is, then update cost[v][1] and push
 *          the node into queue. This is the same as simply doing the dijkstra's transition.
 * 
 * -------> t = 0 case: We first do what we did for t = 1 case. Then, since there hasn't been any 
 *          edge on which the halving-coupon was used so far, we can try to use it now. For that, 
 *          we again go through all neighboring nodes v of u and check if cost[v][1] is greater than
 *          cost[u][0] + cost_of_edge/2. If it is, we update cost[v][1] and push the node (v) into
 *          queue along with t = 1;
 * 
 * Again, the final answer would be cost[n][1].
 * 
 * Runtime O(n + m*log(m)) becase having two arrays for costs would simply incrase the constant but
 * we don't include constants in O-notation.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, vis[N][2];
long long cost[N][2];
vector<pair<int, int>> E[N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    E[a].push_back({b, c});
  }
  
  set<pair<long long, pair<int, int>>> Q;
  for(int i=1; i<=n; i++){
    if(i != 1) cost[i][0] = (long long) 1e14; //setting to infinity, except for the initial node
    cost[i][1] = (long long) 1e14;
  }
  
  Q.insert({0LL, {1, 0}});
  while(!Q.empty()){
    auto [u, t] = Q.begin()->second;
    Q.erase(Q.begin());
    
    if(vis[u][t] == 1) continue;
    vis[u][t] = 1;
    
    for(auto [v, c] : E[u]){
      if(cost[v][t] > cost[u][t] + c){
        cost[v][t] = cost[u][t] + c;
        Q.insert({cost[v][t], {v, t}});
      }
      if(t == 0 && cost[v][1] > cost[u][t] + c/2){
        cost[v][1] = cost[u][t] + c/2;
        Q.insert({cost[v][1], {v, 1}});
      }
    }
  }
  
  printf("%lld\n", cost[n][1]);
  
  return 0;
}
