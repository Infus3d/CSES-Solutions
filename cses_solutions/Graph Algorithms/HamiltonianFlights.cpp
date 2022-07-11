/*
 * Problem link : https://cses.fi/problemset/task/1690
 * Prereq:
 * -----> Hamiltonian Paths:
 *        https://cses.fi/book/book.pdf   (Section 19.2)
 * -----> Bitmask + dp:
 *        https://cses.fi/book/book.pdf   (Section 10. 5)
 * 
 * The problem asks us to find the number of hamiltonian paths that start from
 * node 1 and ends at node n in the given directed graph.
 * 
 * Hamiltonian path is a path that visites each node of the graph exactly once.
 * The reason n <= 20 in this problem is that unlike Eulerian paths, Hamiltonian
 * path is extremely difficult to find in efficient time. It is known as NP-hard
 * as of now meaning no one found a polynomial time solution to the problem yet.
 * 
 * For that reason, we use dynamic programming with bitmasks to solve the problem.
 * We have dp[mask][i] maintain the number of hamiltonian paths that start from
 * node 1 and end at node i using only the nodes that are in the set of {mask}.
 * Transition is easy (note that 1 becomes 0, and n becomes n-1 as it is more 
 * convenient to have 0-indexed node numbers):
 * ------> We find a node that is not in {mask} set so far, that is we find an
 *         index (node number) idx, such that idx'th bit of mask is not set.
 * 
 * ------> We see if there is a road from node i to node idx. If there is, we add
 *         dp[mask][i] onto dp[mask | (1<<idx)][idx] for every edge between i and idx.
 * 
 * ------> We take this mentioned sum mod 1e9+7 as described in the problem.
 * 
 * The answer is then dp[(1<<n)-1][n-1]. n-1 instead of n because 0-indexed.
 * 
 * 
 * Runtime O(2^n * n^2). Although this complexity is indeed the running time of the approach,
 * the code below does some optimizations to fit into 1 sec time limit.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 20;
const int MOD = 1e9+7;

int n, m;
int dp[1<<N][N];
long long c[N][N];

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    c[a][b]++;
  }
  
  dp[1][0] = 1;
  for(int mask=1; mask<(1<<n); mask++){
    if((mask&1) == 0) //we have to start the path from the first node - node 0
      continue;
    if(((mask>>(n-1))&1) && (mask != (1<<n)-1))  //we have to end at node n-1
      continue;
    vector<int> one, zer;
    int k = __builtin_popcount(mask);
    
    for(int i=0; i<n; i++){
      if(k != n-1 && i == n-1) //again there is no use calculating for node n-1 if it is not the lat node
        break;
      if((mask>>i)&1)
        one.push_back(i);
      else
        zer.push_back(i);
    }
    
    for(int i : one){
      for(int j : zer)
        dp[mask|(1<<j)][j] = (dp[mask|(1<<j)][j] + ((c[i][j] * dp[mask][i])%MOD)) % MOD;
    }
  }
  printf("%d\n", dp[(1<<n)-1][n-1]);
  
  return 0;
}
