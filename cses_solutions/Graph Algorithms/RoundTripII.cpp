/*
 * Problem link : https://cses.fi/problemset/task/1678
 * 
 * The problem asks us to find any cycle within the given directed graph.
 * Since the roads are unidirectional the usual method of cycle finding for
 * undirectional graph does not work but we can improve upon it.
 * 
 * Let us have 3 possible visited states of any node inside DFS:
 * ----> vis[u] = 0 means the node is unvisited yet
 * ----> vis[u] = 1 means the node has been visited but we're still traversing
 *       or exploring one of u's neighbors/children
 * ----> vis[u] = 2 means the node is visited and all of its neighbors/children have been explored/visited
 * 
 * Now in a usual DFS iteration we would visit the node we come into with 1 as we have yet to explore
 * its neighbors. Then we check for all neighbors v of u:
 * -----> if vis[v] == 0 we go into that node as it is completely unvisited
 * -----> if vis[v] == 1 we know that v has been visited but not all of its children have been completely
 *        explored. This tells us that if we were to trace back from u to where we came from, we would eventually
 *        get to v, creating a cycle. The only thing we need to do is to keep in mind which node u has been accessed
 *        from using from[] array.
 * -----> if vis[v] == 2 we don't know much about the node. It may lead us to a cycle, but it also may not. Hence
 *        we don't do anything.
 * 
 * Whenever we have vis[v] == 1 we just remember the cycle using its two nodes u and v (begin and end nodes) and trace
 * the cycle using with from[] array to output the path.
 * 
 * Runtime O(n+m) because it is just DFS
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, vis[N], from[N];
int beginNode, endNode;
vector<int> E[N];

void dfs(int u, int par){
  from[u] = par;
  vis[u] = 1;
  
  for(int v : E[u]){
    if(vis[v] == 0)
      dfs(v, u);
    else if(vis[v] == 1 && beginNode == -1){ //if we're still in the 'child-chain' of v and no cycle has been found yet
      beginNode = u;
      endNode = v;
    }
  }
  
  vis[u] = 2;
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
  }
  
  beginNode = endNode = -1;
  for(int i=1; i<=n; i++)
    if(vis[i] == 0)
      dfs(i, -1);
  
  if(beginNode == -1)
    printf("IMPOSSIBLE\n");
  else{
    vector<int> ans;
    
    int curNode = beginNode;
    while(curNode != from[endNode]){
      ans.push_back(curNode);
      curNode = from[curNode];
    }
    ans.push_back(beginNode);
    reverse(ans.begin(), ans.end());
    
    printf("%d\n", (int)ans.size());
    for(int i : ans)
      printf("%d ", i);
    puts("");
  }
  
  return 0;
}
