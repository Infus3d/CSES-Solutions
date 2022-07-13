/*
 * Problem link : https://cses.fi/problemset/task/1693
 * 
 * The problem asks us to find the Eulerian Path of the given directed graph that
 * starts from node 1 and ends at node n. Finding Eulerian path is easy once you
 * know how to find Eulerian Circuits. I recommend solving Mail Delivery problem
 * first because you will learn an approach to find such circuits.
 * 
 * Eulerian Path exists in the given graph only in 2 cases:
 * -----> when indegree of each node also equals its outdegree 
 * 
 * -----> There is exactly one node with outdegree 1 more than its indegree (start), and
 *        exactly one node with indegree 1 more than its outdegree (end) and all other
 *        nodes have their indegrees and outdegrees equal.
 * 
 * Since we have our ending node != starting node, the answer to this problem is IMPOSSIBLE
 * if the graph is anything but the 2nd case above.
 * 
 * After we make sure the graph contains the Eulerian path, we add an extra edge from node n
 * to node 1 to make both of these nodes' indegrees equal their outdegrees. Afterwards, we can
 * go ahead use our approach for finding Eulerian circuits but we start from node n instead of 1.
 * Because after we find the circuit, we can pretend we there never was an edge that we previously
 * manually added - the edge from n to 1 - and omit the last node in the eulerian circuit to make
 * it an eulerian path :)
 * 
 * For more information and better explanation:
 * https://cses.fi/book/book.pdf    (Section 19.1)
 * 
 * Runtime O(n+m)
 * */

#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+2;

int n, m, visEdge[N*2], vis[N], inDeg[N], outDeg[N];
vector<pair<int, int>> E[N];
vector<pair<int, int>>::iterator it[N];
vector<int> ans;

//this is also just a dfs from node 1, to see if it can reach all the edges
void checkReach(int u){
  vis[u] = 1;
  for(auto [v, idx] : E[u])
    if(!vis[v])
      checkReach(v);
}

void dfs(int u){
  for(; it[u] != E[u].end(); it[u]++){
    auto [v, idx] = *it[u];
    if(!visEdge[idx]){
      visEdge[idx] = 1;
      dfs(v);
    }
    if(it[u] == E[u].end())
      break;
  }
  ans.push_back(u);
}

int main(){
  scanf("%d%d", &n, &m);
  
  E[n].push_back({1, m});
  inDeg[1]++; outDeg[n]++;
  
  for(int i=0; i<m; i++){
    int a, b; 
    scanf("%d%d", &a, &b);
    E[a].push_back({b, i});
    inDeg[b]++;
    outDeg[a]++;
  }
  
  checkReach(1);
  
  for(int i=1; i<=n; i++){
    if(inDeg[i] != outDeg[i] || (!vis[i] && inDeg[i] > 0)){
      puts("IMPOSSIBLE");
      return 0;
    }
  }
  
  for(int i=1; i<=n; i++)
    it[i] = E[i].begin();
  dfs(n);
  
  for(int i=(int)ans.size()-2; i>=0; i--)
    printf("%d ", ans[i]);
  puts("");
  
  return 0;
}
