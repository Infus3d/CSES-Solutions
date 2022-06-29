/*
 * Problem link : https://cses.fi/problemset/task/1197
 * Prerequisite:
 * Bellman-Ford and how to detect negative cycles with it:
 * https://cses.fi/book/book.pdf   (Page 123)
 * https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html#implementation
 * 
 * Since the constraints are quite low, we can afford to use Bellman-Ford algorithm to
 * detect the negative cycle in O(n*m). The algorithm guarantees to find the shortest
 * paths to all nodes from the initial node in n-1 steps if there are no negative cycles
 * in the graph. Which means that on the n'th iteration of the algorithm, if it finds
 * two nodes u, v such that there is a shorter route from u to v than dist[v] then there
 * is a negative cycle.
 * 
 * To print the path, we keep track of u when updating v, i.e from[v] = u. Then, we also
 * remember the last node that was updated on the n'th iteration - x. Since it is clear that
 * there is a path from negative cycle to x, we can trace back from x until we hit the negative 
 * cycle. Since there isn't any reliable way to detect whether we're in the negative cycle or not,
 * we do the aformentioned backtracking 'n' times just to ensure that we do fall into the cycle
 * eventually. Then, we are free to print out the cycle using from[] array.
 * 
 * Runtime O(n*m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2501;

int n, m, from[N];
long long dist[N];
vector<pair<pair<int, int>, int>> edges;

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    edges.push_back({{a, b}, c});
  }
  
  int lastUpdatedNode = -1;
  for(int i=0; i<n; i++){
    lastUpdatedNode = -1;
    for(auto e : edges){
      auto [a, b] = e.first;
      auto c = e.second;
      if(dist[b] > dist[a] + c){
        dist[b] = dist[a] + c;
        from[b] = a;
        lastUpdatedNode = b;
      }
    }
  }
  
  if(lastUpdatedNode == -1)
    printf("NO\n");
  else{
    for(int i=0; i<n; i++)
      lastUpdatedNode = from[lastUpdatedNode];
    
    vector<int> cycle;
    int curNode = lastUpdatedNode;
    while(true){
      cycle.push_back(curNode);
      
      if(curNode == lastUpdatedNode && cycle.size() > 1)
        break;
      
      curNode = from[curNode];
    }
    reverse(cycle.begin(), cycle.end());
    
    printf("YES\n");
    for(int i : cycle)
      printf("%d ", i);
    puts("");
  }
  
  return 0;
}
