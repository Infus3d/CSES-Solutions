/*
 * Problem link : https://cses.fi/problemset/task/1751
 * Prereq : Topological Sort
 * https://cses.fi/book/book.pdf  (Section 16.1)
 * 
 * We are given a functional graph where each node points to only 1 other node.
 * This gives the graph a special property: the graph consists of multiple components
 * where each component has exactly one cycle in it, and other nodes that are not in
 * the cycle but in this component point 'towards' that cycle. This cycle can also be
 * seen as the root of a tree, where the remaining nodes outside the cycle are the elements
 * of the tree.
 * 
 * The problem asks us to find how we far we can travel through the graph without visiting the
 * same node twice starting from the node u (1 <= u <= n). We can already tell that in a functional
 * graph, starting from a node and following through the path will eventually lead you to a cycle,
 * which in turn will eventually lead you to a visited node as it is a cycle.
 * All we need to know is two things : 1. how far away is node u from its component's cycle. and
 * 2. how big is the cycle because we need to travel through every node in the cycle to arrive at
 * a visited node.
 * 
 * We can use topological sort to find the cycles of each component. I think I mentioned before that
 * topological sort can not tell the 'locations' of the cycle but only whether it exists or not. It
 * turns out that it actually can locate the cycle within some special graphs and functional graph
 * is one of them. So we do a topological sort on the graph and get all the nodes that are not in the
 * cycle sorted. The nodes that make up a cycle will be left with inDegrees of exactly 1 and will not
 * be in the resulting sorted[] array.
 * Since we now know that inDeg[u] = 1 means that node u is in a cycle, we can start from node u and
 * traverse this cycle (stop when we are again at u) to find the size - cycleSize. At this point, we
 * know that the maximum number of edges used for the nodes in this cycle is cycleSize, so we just
 * assign dist[v] = cycleSize for every node v in this cycle.
 * 
 * Later, we can use our sorted[] array to find the distances of the nodes outside the cycle. We start
 * from the end and iterate towards the beginning of the array. Let's say that we are iteration i, and
 * let's mark the current node as u = sorted[i]. We get the node v that node u is pointing to by v = t[u].
 * Afterwards, all we need to do is take the dist[v] and assign dist[u] = dist[v] + 1.
 * 
 * We can print out dist[] array as answer to the problem.
 * 
 * Runtime O(n + m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, t[N];
int inDeg[N], dist[N];

int main(){
  scanf("%d", &n);
  for(int i=1; i<=n; i++){
    scanf("%d", &t[i]);
    inDeg[t[i]]++;
  }
  
  queue<int> Q;
  for(int i=1; i<=n; i++)
    if(inDeg[i] == 0)
      Q.push(i);
  
  vector<int> sorted;
  while(!Q.empty()){
    int u = Q.front();
    int v = t[u];
    
    Q.pop();
    sorted.push_back(u);
    
    inDeg[v]--;
    if(inDeg[v] == 0)
      Q.push(v);
  }
  
  for(int i=1; i<=n; i++){
    if(inDeg[i] == 0 || dist[i] > 0) continue;
    
    int u = i, cnt = 0;
    stack<int> S;
    while(u != i || !cnt){
      S.push(u);
      u = t[u];
      cnt++;
    }
    
    while(!S.empty()){
      dist[S.top()] = cnt;
      S.pop();
    }
  }
  
  for(int i=sorted.size()-1; i>=0; i--){
    int u = sorted[i], v = t[sorted[i]];
    dist[u] = dist[v] + 1;
  }
  
  for(int i=1; i<=n; i++)
    printf("%d ", dist[i]);
  puts("");
  
  return 0;
}
