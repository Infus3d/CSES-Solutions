/*
 * Problem link : https://cses.fi/problemset/task/1691
 * 
 * The problem asks us to find a Eulerian Circuit in the given undirected graph.
 * Eulerian circuit of a graph is a path that starts from some node, visits
 * all edges in the graph exactly once, and ends at the initial node.
 * Eulerian circuit in an undirected graph can exist only when all of the edges
 * belong to the same connected component and when there is no odd-degree node.
 * That is, degree of every single node in the connected component must be even.
 * 
 * Detecting the existence is not that difficult but finding such circuit involves
 * a little thinking. First, let's note that 2 completely disjoint circuits that share
 * the same node make up a single bigger circuit together. Disjoint here means that
 * the two circuits do not share an edge (but they may share a node!).
 * 
 * That being said, to find the circuit for the graph we start from the postoffice -
 * - node 1 and run a DFS. On each call of the DFS we go through the edges the node u
 * has and go into the ones that haven't been visited before. Now the DFS might run for a while
 * before it finally comes to a 'trench' where the node u has no other edge unvisited.
 * 
 * At that time we know that node u must equal our starting node because it was the only
 * node with odd-number of unvisited edges [remember that we started from this node,
 * and marked one of its edges 'visited']. This tells us that we have found a circuit although
 * it may not necessarily cover all the edges in the graph. For that reason, we mark node u
 * as the 'beginning' of the circuit instead of the 'end' - in fact we mark any node with no
 * unvisited edges left as the next node in the circuit (in the code below, we just print it out).
 * 
 * We backtrack from such nodes as we push them into the path/circuit until we find a node that
 * has at least 2 unvisited node [note that 2 here refers to the fact that any such node should
 * have an even number of edges left]. We then travel into this edge of the node until eventually
 * we come back to this same node, finding another smaller completely disjoint circuit in the graph.
 * Like mentioned before, we can concatenate our previously found circuit with this one and assume
 * we have a bigger single circuit.
 * 
 * For more information and better explanation:
 * https://cses.fi/book/book.pdf    (Section 19.1)
 * https://usaco.guide/CP2.pdf#page=129
 * 
 * Runtime O(n+m)
 * */

#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, visEdge[N*2], vis[N];
vector<pair<int, int>> E[N];
vector<pair<int, int>>::iterator it[N];

//this is also just a dfs from node 1, to see if it can reach all the edges
void checkReach(int u){
  vis[u] = 1;
  for(auto [v, idx] : E[u])
    if(!vis[v])
      checkReach(v);
}

void dfs(int u){
  for(; it[u] != E[u].end(); it[u]++){
    auto [v, idx] = *it[u];
    if(!visEdge[idx]){
      visEdge[idx] = 1;
      dfs(v);
    }
    if(it[u] == E[u].end())
      break;
  }
  printf("%d ", u);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b; 
    scanf("%d%d", &a, &b);
    E[a].push_back({b, i});
    E[b].push_back({a, i});
  }
  
  checkReach(1);
  
  for(int i=1; i<=n; i++){
    int deg = E[i].size();
    //if the edge count is odd or if there is an unreachable node [from node 1] with non-zero degree
    if(deg % 2 || (!vis[i] && deg > 0)){
      puts("IMPOSSIBLE");
      return 0;
    }
  }
  
  for(int i=1; i<=n; i++)
    it[i] = E[i].begin();
  dfs(1);
  puts("");
  
  return 0;
}
