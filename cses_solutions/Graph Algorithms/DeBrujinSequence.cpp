/*
 * Problem link : https://cses.fi/problemset/task/1692
 * 
 * We can make graph with nodes numbered from [0 to 2^(n-1)) representing
 * the last n-1 bits of current [window] of the sequence. Each node has
 * 2 outgoing edges with costs 0 and 1. This outgoing edges can be visualised
 * as appending the cost (0 or 1) of the edge to the back of current node
 * and taking the last n-1 bits of the result to the next node. For example,
 * if we have our current node u = 010 then edge with cost 1 will point to node
 * v = 0[101] = 101 and edge with cost 0 will point to node w = 0[100] = 100.
 * 
 * After constructing such graph, we can start from any node and find the euler
 * circuit of the graph. The answer will then be the number of the starting node
 * appended to the front of the cost-sequence on the euler path.
 * 
 * Please refer to the following for better explanation:
 * https://cses.fi/book/book.pdf  (Chapter 19, De-Brujin Sequences)
 * 
 * Runtime O(2^n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 15;

int n;
vector<int> E[1<<N], ans;

void dfs(int u){
  while(E[u].size() > 0){
    int v = E[u].back();
    E[u].pop_back();
    dfs(v);
  }
  ans.push_back(u%2);
}

int main(){
  scanf("%d", &n);
  if(n == 1)
    puts("01");
  else{
    int hmask = (1<<(n-2))-1; //helper-mask
    for(int i=0; i<(1<<(n-1)); i++){
      E[i].push_back(((i&hmask)<<1)|0);
      E[i].push_back(((i&hmask)<<1)|1);
    }
    
    dfs(0);
    
    for(int i=0; i<n-1; i++) // the value of the initial node
      printf("0");
    for(int i=(int)ans.size()-2; i>=0; i--) //euler path edge values
      printf("%d", ans[i]);
    puts("");
  }
  
  return 0;
}
