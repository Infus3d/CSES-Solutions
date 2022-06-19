/*
 * Problem link : https://cses.fi/problemset/task/1666
 * 
 * Prereq:
 * DFS : https://cses.fi/book/book.pdf (page 117)
 * 
 * The idea here is the equivalent of the solution to 'Counting Rooms'
 * problem: we need to count the number of rooms, or in this problem, components. 
 * We essentially have a graph with multiple connected-components in it
 * and we're asked to join them with the minimal possible edges. Let's say that
 * we have k connected-components in the given graph, then the answer - the minimum
 * number of edges to connect them all - will be k-1. To see this, imagine each of
 * the connected-components as a single node/dot (imagine 'zooming-out' and graph becomes
 * tinier). We then align all these nodes in a straight line and connect every two
 * neighboring nodes (i and i+1 for i < k). This will require us at exactly k-1 edges to do.
 * 
 * To print out which nodes to use our new edges on in these connected components, we can
 * run through every node (1 ... n) and see if this node has been visited before. If it is
 * not visited, we assign this node as the 'head' of its connected-component and run dfs
 * to mark all nodes in this connected group as visited.
 * Then, we can use the heads as the connecting ports of each component.
 * 
 * Runtime O(n+m) because dfs is awesome :)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, vis[N];
vector<int> E[N];

void dfs(int x){
  vis[x] = 1;
  for(int i : E[x])
    if(!vis[i])
      dfs(i);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b); //storing the graph in adjacency list
    E[b].push_back(a); 
  }
  
  vector<int> ansNodes;
  for(int i=1; i<=n; i++)
    if(!vis[i]){
      ansNodes.push_back(i);
      dfs(i);
    }
  
  printf("%d\n", (int)ansNodes.size()-1);
  for(int i=1; i<(int)ansNodes.size(); i++)
    printf("%d %d\n", ansNodes[i-1], ansNodes[i]);
  
  return 0;
}
