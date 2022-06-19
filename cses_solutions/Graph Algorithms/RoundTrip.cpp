/*
 * Problem link : https://cses.fi/problemset/task/1669
 * 
 * This problem asks us to find a cycle of length at least 3 and print out
 * the nodes along that cycle. The problem would have been challenging if
 * it asked to find a particular cycle but since we can print out any of such
 * cycles it is pretty straightforward.
 * 
 * We use dfs to traverse the graph and visit every single node on the way.
 * Once we find (come back) to a node that has already been visited, then we
 * have found a cycle. To know if such cycle is of length at least 3, we can
 * keep track of the previous (or parent) node in the dfs. If the 'new-found-
 * -already-visited' node is the same as previous node, then the cycle is of
 * length 2 (just 2 nodes with 2 edges between them). And if it is not the same
 * as previous node, then cycle is at least of length 3. We also maintain a from[]
 * array where from[u] = v indicates that u has been reached by/after v.
 * 
 * Once we have found the desired cycle, we just remember the 2 nodes (beginning
 * and end of cycle) and print out the path using our from[] array.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, from[N], cycleBegin, cycleEnd;
vector<int> E[N];

void dfs(int curNode, int prevNode){
  from[curNode] = prevNode;
  
  for(int i : E[curNode]){
    if(from[i] == 0)
      dfs(i, curNode);
    else if(i != prevNode && cycleBegin == 0){
      //i != prevNode guarantees that the cycle lenght is at least 3
      //cycleBegin == 0 is to check if we have yet to find a cycle
      cycleBegin = curNode;
      cycleEnd = i;
    }
  }
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  for(int i=1; i<=n; i++)
    if(from[i] == 0)
      dfs(i, -1);
  
  if(cycleBegin == 0)
    printf("IMPOSSIBLE\n");
  else{
    int curNode = cycleBegin;
    vector<int> ans;
    
    while(true){
      ans.push_back(curNode);
      if(curNode == cycleEnd)
        break;
      curNode = from[curNode];
    }
    ans.push_back(cycleBegin);
    
    printf("%d\n", (int)ans.size());
    for(int i : ans)
      printf("%d ", i);
    puts("");
  }
  
  return 0;
}
