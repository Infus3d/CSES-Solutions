/*
 * Problem link : https://cses.fi/problemset/task/1688
 * Prereq:
 * Lowest Common Ancestor and Binary Lifting:
 * ----> https://cses.fi/book/book.pdf  (Chapter 18)
 *       https://cp-algorithms.com/graph/lca_binary_lifting.html
 * 
 * The problem asks us to find the lower common ancestor of two nodes u and v. There is an
 * efficient algorithm that builds the ancestry table in n*log(n) time so that the LCA of
 * u and v can be calculated with log(n) time per query. Please refer to the links above to
 * learn about the algorithm.
 * One thing that might help you understand it better using the above sources is that
 * any positive integer x can be written as a sum of 2's powers. For example, 2 = 2^1,
 * 3 = 2^1 + 2^0 and 19 = 2^4 + 2^1 + 2^0. So in binary lifting when we want to find
 * 19th ancestor of x, we first go to (2^4)'th ancestor of x, and then (2^1)'th ancestor
 * of that node, and finally (2^0)'th ancestor of the latter node.
 * 
 * I also recommend solving Company Queries I before attempting this problem.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q;
int depth[N], P[N][18]; //18 because 17 = log2(2e5)

void build_lca(){
  for(int j=1; j<18; j++)
    for(int i=1; i<=n; i++)
      if(P[i][j-1] > 0)
        P[i][j] = P[P[i][j-1]][j-1];
}

int lca(int u, int v){
  if(depth[u] < depth[v])
    swap(u, v);
  
  for(int i=17; i>=0; i--)
    if(depth[u] - (1<<i) >= depth[v])
      u = P[u][i];
  
  if(u == v) return u; //if u was in v's subtree
  
  for(int i=17; i>=0; i--) //if u and v have disjoint subtrees, that is their lca will be equal to neither u nor v
    if(P[u][i] != P[v][i])
      u = P[u][i], v = P[v][i];
  
  return P[u][0];
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=2; i<=n; i++){
    int a; scanf("%d", &a);
    depth[i] = depth[a]+1;
    P[i][0] = a;
  }
        
  build_lca();
  
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", lca(a, b));
  }
  
  return 0;
}
