/*
 * Problem link : https://cses.fi/problemset/task/1681
 * Prereq:
 * Topological Sort -> https://cses.fi/book/book.pdf  (Section 16.1)
 * 
 * Very similar to Longest Flight Routes problem where we are given an undirected
 * graph with no cycles that we can do a topological sort on. However this time, we
 * need to count the number of ways to reach n instead of the longest route.
 * 
 * Let a[] be the resulting array containing nodes sorted in topological order, where
 * a[i] comes after all of its requirements a[j], that is j < i.
 * Also let dp[u] be the number of ways to reach node u from 1.
 * 
 * With these in mind, we can iterate over a[] from beginning to the end and on each
 * iteration i we can update the neighbors v of a[i] (a[i] is also a node) by just
 * dp[v] += dp[a[i]] (mod 1e9+7).
 * We need to start with dp[] array initialized to zero on all nodes except the starting
 * node 1 because we have exactly one way of reaching node 1 from node 1 :D
 * Then the answer to the problem is just dp[n].
 * 
 * Runtime O(n + m)
 * */

#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;
const int MOD = 1e9+7;

int n, m, inDeg[N], dp[N];
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
  
  dp[1] = 1;
  for(int u : sortedNodes)
    for(int v : E[u])
      dp[v] = (dp[v] + dp[u]) % MOD;
  
  printf("%d\n", dp[n]);
  
  return 0;
}

