/*
 * Problem link : https://cses.fi/problemset/task/1132
 * 
 * The farthest distance nodes to any node u in the tree will be one of the end-points
 * of the diameter of the tree. You can learn why this is the case in the Diameter section
 * of the Chapter 14 of the book: https://cses.fi/book/book.pdf
 * 
 * We easily find the diameter and the two end-nodes of such diameter using DFS. To calculate
 * the maximum distances for both end-nodes we run a final dfs where we just maximize the
 * dist[] values.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n;
vector<int> E[N];

void dfs(int u, int par, int curDist, vector<int> &dist){
  dist[u] = max(dist[u], curDist);
  for(int v : E[u])
    if(v != par)
      dfs(v, u, curDist+1, dist);
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
    
  vector<int> dist1(n+1, 0);
  dfs(1, 0, 0, dist1); //first DFS to find the first end-node of the diamater
  
  int maxDist = 0, theNode = -1;
  for(int i=1; i<=n; i++)
    if(dist1[i] > maxDist)
      maxDist = dist1[i], theNode = i; //finding the first end-node
  
  vector<int> dist2(n+1, 0);
  if(theNode != -1)
    dfs(theNode, 0, 0, dist2); //second dfs to find the second end-node of the diamater
  
  maxDist = 0, theNode = -1;
  for(int i=1; i<=n; i++)
    if(dist2[i] > maxDist)
      maxDist = dist2[i], theNode = i; //finding the second end-node
  
  //since dist2 contains the distances from first end-node, we initiate another dfs for second-end node to maximize the distances
  if(theNode != -1)
    dfs(theNode, 0, 0, dist2); 
  
  for(int i=1; i<=n; i++)
    printf("%d ", dist2[i]);
  puts("");
  
  return 0;
}
