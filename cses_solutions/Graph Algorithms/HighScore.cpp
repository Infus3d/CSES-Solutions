/*
 * Problem link : https://cses.fi/problemset/task/1673
 * Prerequisite:
 * DFS and BFS : https://cses.fi/book/book.pdf  (Chapter 12)
 * Bellman-Ford : https://cses.fi/book/book.pdf  (Section 13.1)
 * 
 * I would recommend solving CycleFinding first as it is a direct subproblem of this problem.
 * With the help of that problem you'll be able to find a negative cycles in directed graphs.
 * 
 * In this solutoin however, the cycle is found using an alternative approach with DFS: we
 * iterate through every node 1..n and mark node i as the 'head-node' on each iteration and
 * run dfs on the graph starting from i. The aim is to find out if there is a positive (in this
 * problem we need to find positive instead of negative cycles) cycle that also ends at i:
 * 
 * ----> We maintain two arrays throughout the DFS: vis[] and remCost[] where vis[u] is the
 *       visited status of the node while remCost[u] contains the maximal cost of any path
 *       from u to head-node.
 *       We start from head-node and explore the graph marking visited cells with vis[] array.
 *       Let's call our current node u. If we encounter a visited node v as our neighbor, then
 *       we consider 2 options:
 *       -----> If v == head-node, then remCost[u] = max(remCost[u], cost_of_edge_u_v)
 *       -----> If v != head-node, then remCost[u] = max(remCost[u], remCost[v] + cost_of_edge_u_v)
 *       At the end of the dfs, if remCost[head-node] is greater than 0, then there is a positive cycle
 *       involving head-node (or i, in our iteration).
 * 
 * Now the problem asks us to find out if it is possible to arrive at positive cycle from 1 while also
 * reach n from the same cycle. Since we've already found if a node is part of a positive cycle for all
 * nodes, all we need to do is to see if that node is reachable from 1 and if that node can reach n. This can
 * be done by simply running another DFS or BFS and just mainting 2 dimensional array reachable[i][j] that
 * has a value of 1 if j is reachable by i. Note that while calculating this reachable table, we do not
 * need to worry about the cost of the edges as we're only testing for 'reachability'.
 * Once we have our table reachable[][] and remCost[] we can simply go through all nodes i and check
 * the condition for 'infinite maximization of the score': remCost[i] > 0 and reachable[1][i] and reachable[i][n]
 * 
 * If there is no such infinite maximization possibility in the graph, we simply need to calculate the largest
 * path (analogous to shortest path, just signs switched) using Bellman-Ford's algorithm.
 * 
 * Runtime O(n^2 + n*m)
 * */

#include "bits/stdc++.h"

using namespace std;

const int N = 2501;

long long n, m, cost[N], remCost[N];
bool reachable[N][N];
vector<pair<pair<int, int>, int>> allEdges;
vector<pair<int, int>> E[N];
vector<int> vis;

void dfs(int u, int rootNode){
  vis[u] = 1;
  
  for(auto [v, c] : E[u])
    if(vis[v] == 0)
      dfs(v, rootNode);
  
  for(auto [v, c] : E[u]){
    if(v == rootNode)
      remCost[u] = max(remCost[u], (long long)c);
    else if(remCost[v] != -LLONG_MAX)
      remCost[u] = max(remCost[u], remCost[v] + c);
  }
}

int main(){
  scanf("%lld%lld", &n, &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    E[a].push_back({b, c});
    allEdges.push_back({{a, b}, c});
  }
  
  //Calculating reachable[i][j] table for all i, j (if j is reachable from i)
  //Time complexity O(n^2 + n*m)
  for(int i=1; i<=n; i++){
    reachable[i][i] = true;
    queue<int> Q;
    
    Q.push(i);
    while(!Q.empty()){
      int u = Q.front();
      Q.pop();
      
      for(auto [v, c] : E[u]){
        if(reachable[i][v] == false){
          reachable[i][v] = true;
          Q.push(v);
        }
      }
    }
  }
  
  vis.resize(n+1);
  for(int i=1; i<=n; i++){
    fill(vis.begin(), vis.end(), 0);
    fill(remCost, remCost+n+1, -LLONG_MAX);
    
    dfs(i, i);
    //If there is a positive cycle and any path from 1 to n through i
    if(remCost[i] > 0 && reachable[1][i] && reachable[i][n]){
      printf("-1\n");
      return 0;
    }
  }
  
  //If there is no positive cycle, then we find the max-cost path using Bellman-Ford
  for(int i=2; i<=n; i++) cost[i] = (long long) -1e14; //setting to negative infinity first
  for(int i=1; i<n; i++){
    for(auto e : allEdges){
      int a = e.first.first, b = e.first.second;
      int c = e.second;
      cost[b] = max(cost[b], cost[a] + c);
    }
  }
  
  printf("%lld\n", cost[n]);
  
  return 0;
}
