/*
 * Problem link : https://cses.fi/problemset/task/1130
 * 
 * Imagine that we are at an arbitrary node u and want to calculate the maximal matching
 * for u's subtree and store it in maxmatch[u]. Let's also assume that such maxmatch[w]
 * values are already calculated for all nodes w in u's subtree. Then for current
 * u, we can choose any of the edges between u and its children and claim that we want to add
 * this edge into max-matching of u's subtree. If we call such an edge e and the node on its
 * other endpoint v, then the maximum-matching would be equal to the sum of the following:
 * 
 * ----> +1 because we want to add edge e
 * ----> Sum of maxmatch[x] where x is the child of node v. This means that since we are adding
 *       edge e, both endpoints u and v are marked 'visited' and can not involve other incident
 *       edges. So the best we can do is go through children of v and add their maxmatch values
 *       because they don't have any common edges with v that is in their maximum matching.
 *       (Remember that maxmatch[u] is maximum-matching for u's subtree only, it has nothing to
 *       do with u's parent node).
 * ----> Sum of nodes t where t is the set of children of node u excluding node v. This means
 *       that we can freely choose any child of u that is not v, and add their maximum-matching
 *       to our our current one (u's subtree's maxmatch) because such nodes t do not have a common
 *       edge with node u.
 * 
 * To achieve all of this, let's maintain a dp[N][2] array where:
 * ---> dp[u][1] contains the maximum matching for u's subtree - it is our maxmatch[u] array from
 *      above. We calculate it as the maximum over all maximum-matchings that could be done considering
 *      each of u's incident edges with its child nodes.
 * 
 * ---> dp[u][0] contains the sum of maximum matchings of the subtrees of all child nodes of u. This
 *      can be calculated by simply summing up the dp[v][1] values of all of u's children v.
 * 
 * The answer to the problem is then just dp[root][1].
 * Please refer to the code below to understand it better. 
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, dp[N][2];
vector<int> E[N];

void dfs(int u, int par){
  for(int v : E[u]){
    if(v != par){
      dfs(v, u);
      dp[u][0] += dp[v][1];
    }
  }
  for(int v : E[u]){
    if(v != par)
      dp[u][1] = max(dp[u][1], dp[v][0] + (dp[u][0] - dp[v][1]) + 1);
  }
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  dfs(1, 0);
  printf("%d\n", dp[1][1]);
  
  return 0;
}
