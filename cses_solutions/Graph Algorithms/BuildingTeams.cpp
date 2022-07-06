/*
 * Problem link : https://cses.fi/problemset/task/1668
 * 
 * We store the friendships as a graph using adjacency list, where the edge between
 * u and v represents their friendship.
 * Notice that the graph can have multiple connected 'sub-graphs' and that team
 * composition for one sub-graph is completely independent of other sub-graphs.
 * For a particular sub-graph, we can pick a starting node and assign it to either team
 * 1 or 2 and run a dfs through that sub-graph. Let's say that we are at node u and
 * need to assign it to teamNum team:
 * -----> We assign u to teamNum by simply marking it as such : teamNumber[u] = teamNum.
 * -----> Then we recursively visit each of u's neighbors (or friends) by switching current
 *        teamNumber because obviously no two friends can be in the same team.
 * -----> we run the above 2 until there are no nodes left in the sub-graph
 * 
 * We do the above for every single connected sub-graph of the given graph and then check for
 * its validity. Since we have a team assigned to each person, this is easy to check:
 * -----> For every i (1 <= i <= n) we just check if its friends have the same team number assigned
 *        to them. If yes, then answer is IMPOSSIBLE because there is no way we can 'handle' the
 *        connected sub-graph the node i is in. If no, then continue on.
 * 
 * If everything is fine, then output teamNumber[] array.
 * 
 * Runtime O(n + m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, teamNumber[N];
vector<int> E[N];

void dfs(int x, int tnum){
  teamNumber[x] = tnum;
  
  for(int i : E[x])
    if(teamNumber[i] == 0)
      dfs(i, 3-tnum); //every time we switch from 1 to 2, or from 2 to 1
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  //we need this loop because the given graph has multiple conntected sub-graphs
  //and doing dfs(1) just from 1 source may not necessarily reach all other nodes
  for(int i=1; i<=n; i++) 
    if(teamNumber[i] == 0)
      dfs(i, 1);
  
  for(int i=1; i<=n; i++){
    for(int j : E[i])
      if(teamNumber[i] == teamNumber[j]){
        printf("IMPOSSIBLE\n");
        return 0;
      }
  }
  
  for(int i=1; i<=n; i++)
    printf("%d ", teamNumber[i]);
  puts("");
  
  return 0;
}
