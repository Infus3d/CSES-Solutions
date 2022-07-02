/*
 * Problem link : https://cses.fi/problemset/task/1680
 * Pre-req:
 * Topological Sort -> https://cses.fi/book/book.pdf  (Section 16.1)
 * 
 * Since the problem guarantees that there won't be any cycles in the input, we can safely
 * do topological sort and expect all nodes to be sorted in the result.
 * Let a[] be the array after sorting is done. Then the node a[i] in the array tells us that
 * all of its prerequisites (or nodes in the path that lead to a[i]) a[j] are located before 
 * a[i] in the array, that is in the indices j < i.
 * 
 * This is very convenient because now we can simply interate over the array from beginning to end
 * and just process the dp to find the longest path to every node u and store it in dp[u]. dp[u] here
 * contains the number of nodes in such longest path.
 * 
 * We initiate dp[u] values of all nodes u to -1 so that it tells whether node u has been visited
 * or not. We initiate the starting node value to 1 (node 1).
 * Let a[i] = u on the i'th iteration:
 * -----> We first check if dp[u] == -1, because if it is, then there is no path from node 1 to node u.
 *        But if is anything other than -1, then we look through all neighbors v of u and update their 
 *        cost dp[v] = max(dp[v], dp[u] + 1).
 * ----------> If dp[v] is smaller than dp[u] + 1, then we've found a longer route to v and we need
 *             to mark u as the predecessor of v on its longest route (from[v] = u) so that we can
 *             trace it back later.
 * ----------> If not, then path from u to v is smaller than some other path that lead to v. So we
 *             do nothing.
 * 
 * At the end, if dp[n] == -1, then the answer is IMPOSSIBLE. If it isn't, then there is at least some
 * path from node 1 to node n and dp[n] contains the number of nodes in the longest of such paths. Using
 * our from[] array we can trace back this longest path and print it out.
 * 
 * Runtime O(n + m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, inDeg[N], dp[N], from[N];
vector<int> E[N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    inDeg[b]++;
  }
  
  queue<int> Q;
  for(int i=1; i<=n; i++){
    dp[i] = from[i] = -1;
    if(inDeg[i] == 0)
      Q.push(i);
  }
  
  vector<int> sortedNodes;
  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    
    sortedNodes.push_back(u);
    
    for(int v : E[u]){
      inDeg[v]--;
      if(inDeg[v] == 0)
        Q.push(v);
    }
  }
  
  dp[1] = 0;
  for(int u : sortedNodes)
    if(dp[u] != -1){ //if there is a path from node 1 to node u
      for(int v : E[u])
        if(dp[v] == -1 || dp[v] < dp[u] + 1){
          dp[v] = dp[u] + 1;
          from[v] = u;
        }
    }
  
  if(dp[n] == -1)
    printf("IMPOSSIBLE\n");
  else{
    vector<int> path;
    int curNode = n;
    while(curNode != -1){
      path.push_back(curNode);
      curNode = from[curNode];
    }
    
    printf("%d\n", (int)path.size());
    for(int i=path.size()-1; i>=0; i--)
      printf("%d ", path[i]);
    puts(""); //this is just endline
  }
  
  
  
  return 0;
}
