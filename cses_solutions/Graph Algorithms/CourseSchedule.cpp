/*
 * Problem link : https://cses.fi/problemset/task/1679
 * 
 * The problem asks us to do topological sort on the given graph and output nodes in
 * that sorted order. You can read more about topological sort from the following:
 * https://cses.fi/book/book.pdf   (Section 16.1)
 * https://www.geeksforgeeks.org/topological-sorting/
 * 
 * One very nice thing about topological sort is that it detects cycles in the directed graph!
 * If after the sorting not all nodes are present in the result, then there is a cycle. Although
 * it can not exactly locate the cycle, it is still nice that such simple and short algorithm
 * can detect one and can be useful on many occasions.
 * 
 * Runtime O(n + m). Even though the name contains 'sorting' it is linear time :D
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, inDeg[N];
vector<int> E[N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b); //we keep the out-edges of each node
    inDeg[b]++;
  }
  
  queue<int> Q;
  for(int i=1; i<=n; i++)
    if(inDeg[i] == 0) //if node i doesn't have an pre-req nodes
      Q.push(i);
  
  vector<int> ans;
  while(!Q.empty()){
    int u = Q.front();
    Q.pop();
    
    ans.push_back(u); //since u has no pre-reqs left, we just push it to ans
    
    for(int v : E[u]){
      inDeg[v]--;
      if(inDeg[v] == 0)
        Q.push(v);
    }
  }
  
  if((int)ans.size() != n){ // if size is less than n, then there is a cycle
    printf("IMPOSSIBLE\n");
    return 0;
  }
  
  for(int i : ans)
    printf("%d ", i);
  puts("");
  
  return 0;
}
