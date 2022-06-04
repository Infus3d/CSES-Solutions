/*
 * Problem link : https://cses.fi/problemset/task/1667
 * 
 * The same logic as Labyrinth problem where we need to use BFS to find
 * the shortest path from A to B but this time it is on a graph instead
 * of a grid.
 * 
 * We store the edges of the graph in an adjacency list and initialize
 * the cost of all nodes to 'infinity'. We then start from the beginning
 * node [1] and spread the BFS to all other nodes to calculate the minimum
 * distance. During any iteration of the queue, we will have the curNode:
 * -----> We then look through all neighbors [i] of curNode and see if their
 *        cost[i] is bigger than cost[curNode] + 1. If it is, then update the
 *        cost and push the node into the queue. Also update the from[i] = curNode
 *        which helps us trace the path back from n to 1 for output.
 * 
 * Runtime O(n + m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, cost[N], from[N];
vector<int> E[N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  for(int i=1; i<=n; i++)
    cost[i] = INT_MAX;   //Initializing all costs to 'infinity'
  
  queue<int> Q;
  Q.push(1); cost[1] = 0; //cost of the initial node is 0
  
  while(!Q.empty()){
    int curNode = Q.front();
    Q.pop();
    
    for(int i : E[curNode])
      if(cost[i] > cost[curNode] + 1){
        cost[i] = cost[curNode] + 1;
        from[i] = curNode;  //from[i] = j means there is a path to i from j
        Q.push(i);
      }
  }
  
  if(cost[n] == INT_MAX)
    printf("IMPOSSIBLE\n");
  else{
    vector<int> trace;
    
    int curNode = n;
    while(curNode != 1){ //we start from n, trace the path back to 1 using from[]
      trace.push_back(curNode);
      curNode = from[curNode];
    }
    trace.push_back(1);
    
    reverse(trace.begin(), trace.end());
    
    printf("%d\n", cost[n]+1);
    for(int i : trace)
      printf("%d ", i);
    puts("");
  }
  
  return 0;
}
