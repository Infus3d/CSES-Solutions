/*
 * Problem link : https://cses.fi/problemset/task/1133
 * 
 * We can achieve this by 2 simple DFS runs with basic DP. We just need to keep track
 * of 2 values: dist[] will be for calculating the sum of distances and nodeCnt[] where
 * nodeCnt[u] will keep the number of nodes in u's subtree.
 * 
 * In the first DFS run, for all nodes u we calculate the sum of distances from u to all nodes
 * in its subtree (we also calculate the nodeCnt[] array):
 * -----> We look through the children v of node u and add their dist[v] onto the current dist[u].
 *        We also need to account for the edge between u and v which adds +1 to the length of every
 *        path in dist[v]. So in total, we do dist[u] += dist[v] + nodeCnt[v] because there are exactly
 *        nodeCnt[v] count of paths from node v in its subtree.
 * 
 * -----> nodeCnt[u] value is easy to calculate as we just sum the nodeCnt[v] values of u's children v.
 *        And then simple add +1 to nodeCnt[u] because we need to count the node u itself.
 * 
 * In the second DFS run, we make dist[u] contain not just the sum distances in u's subtree but also the
 * sum of distances from all other nodes. In the code below, it is called downDFS because we kind of trickle
 * down the distances 'from all other nodes that are not in u's subtree' from u's parent onto u's dist[] value.
 * We start the second DFS from the root node and also remember that dist[root] already contains the sum of distances
 * from u to all other nodes in the tree as it is the root of the tree:
 * -----> We look through the children v of node u (making u the parent of the node v) and before going into
 *        the child v we calculate dist[v] for this child. Assuming dist[u] already contains the sum of distances
 *        from u to all other nodes, we add (dist[u] - (dist[v] + nodeCnt[v])) onto dist[v]. This value is just
 *        the sum of distances from node u to all other nodes excluding the nodes in v's subtree. But we're not done
 *        yet because we did not account for the edge between node u and v for all such distances. Since we know that
 *        the number of such distances/paths is (n - nodeCnt[v]) and each of them get +1 from transitioning from node
 *        u to node v, we simply add their product (n - nodeCnt[v]) * (+1) onto dist[v]. Now dist[v] contains sum of 
 *        distances to all nodes from node v.
 * 
 * We just output dist[] array as answer.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, nodeCnt[N]; //nodeCnt[u] is the number of nodes in u's subtree, including u
long long dist[N];
vector<int> E[N];

void upDFS(int u, int par){
  for(int v : E[u])
    if(v != par){
      upDFS(v, u);
      dist[u] += (dist[v] + nodeCnt[v]);
      nodeCnt[u] += nodeCnt[v];
    }
  nodeCnt[u] += 1; //counting itself
}

void downDFS(int u, int par){
  for(int v : E[u])
    if(v != par){
      long long distances = (dist[u] - (dist[v] + nodeCnt[v])); //sum of distances from u to all nodes outside v's subtree
      dist[v] += distances + (n - nodeCnt[v]); //each of such (n - nodeCnt[v]) distances increase by +1 when going from node u to node v
      downDFS(v, u);
    }
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  upDFS(1, 0);
  downDFS(1, 0);
  
  for(int i=1; i<=n; i++)
    printf("%lld ", dist[i]);
  puts("");
  
  return 0;
}
