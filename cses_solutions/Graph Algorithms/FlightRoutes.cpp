/*
 * Problem link : https://cses.fi/problemset/task/1196
 * 
 * Prereq: Dijkstra's Algorithm
 * ---> https://cses.fi/book/book.pdf  (Section 13.2)
 * 
 * Useful link: Wikiepedia page for this problem's solution
 * ---> https://en.wikipedia.org/wiki/K_shortest_path_routing
 * 
 * The key idea in this problem is that when we need the shortest k paths, any of these
 * k paths will visit/cross the same node in the graph at most k times because all edge
 * weights are positive.
 * That being said, we can improve upon the usual Dijkstra's Algorithm to suit our needs.
 * First, we will need count[] array to keep count of how many times each node has been visited.
 * Then we start from the starting node 1 and try to find the shortest k paths to node n by first pushing
 * {cost : 0, node : 1} pair into the Queue (priority queue or multiset in C++).
 * 
 * During the process, we know from Dijkstra's Algorithm that whenever a path is popped from the
 * queue [with path cost : c and path-end-node : u] and that node u has not been 'popped' from the
 * queue before, then c is the minimal cost that leads to node u (from node 1). In our modified
 * version of Dijkstra the same logic follows, however this time when we pop the path we would
 * increase the count[u] by 1 which then tells us that path with cost c is the count[u]'th shortest
 * path that leads to u. 
 * If any node u has their count[u] < k during the finding process (or while loop) then we look through 
 * all of its neighbors v and add a new path into the queue with [path cost : c + u_v_edge_cost, path-end-node : v] 
 * just like you would in a normal Dijkstra's Algorithm. If count[n] (the node we are trying to reach) reaches k, 
 * we stop the finding process and break out of the while loop
 * 
 * Now calculating the runtime of our approach can be quite tricky, but it is possible!
 * The overall runtime is O(k * (n + m*log(m*k))). To understand this, recall that the runtime of the simple
 * Dijkstra's is O(n + m*log(m)) because we visit every node at most once and process their edges at most once
 * (totalling m edges over all nodes 1 through n) and add a new path into queue for each edge at most once with
 * log(m) operations each (because max number of items in the queue is m).
 * In this problem, we visit each node at most k times O(n*k) and it's because of that we process each edge at most
 * k times, which also means that the maximum number of elements in the queue is m*k (hence log(m*k)). Since we add
 * a new path into the queue every time we process an edge, runtime of total insertions will be O(m*k*log(m*k)).
 * Adding them together we get O(k*(n + m*log(m*k))).
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, k, cnt[N];
vector<pair<int, int>> E[N];

int main(){
  scanf("%d%d%d", &n, &m, &k);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    E[a].push_back({b, c});
  }
  
  multiset<pair<long long, int>> Q;
  Q.insert({0, 1}); //node 1 with 0 cost
  
  vector<long long> ans;
  while(!Q.empty() && cnt[n] < k){
    auto [c, u] = *Q.begin();
    Q.erase(Q.begin());
    
    cnt[u]++;
    if(u == n)
      ans.push_back(c);
    
    if(cnt[u] <= k){
      for(auto [v, w] : E[u])
        Q.insert({c + w, v});
    }
  }
  
  for(auto i : ans)
    printf("%lld ", i);
  puts("");
  
  return 0;
}
