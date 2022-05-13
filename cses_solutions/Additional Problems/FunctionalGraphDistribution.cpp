/*
 * Problem link: https://cses.fi/problemset/task/2415
 * 
 * Pre-reqs to understand the solution:
 * Binomial Coefficient: https://en.wikipedia.org/wiki/Binomial_coefficient
 * Stirling Numbers of the first kind: https://en.wikipedia.org/wiki/Stirling_numbers_of_the_first_kind
 * Cayley's formula: https://en.wikipedia.org/wiki/Cayley's_formula
 * 
 * Please refer to the following tutorial for in-depth explanation of the solution (you can use google translate):
 * https://abc864197532.github.io/2021/09/15/cses-additional-sol/
 * 
 * The solution to the problem stems from noticing that there is exactly 1 outgoing edge from every node.
 * This implies that there are n edges in total no matter how you partition the nodes. Note that this
 * is just 1 edge more than what's needed to form a tree out of n nodes, meaning there is exactly 1
 * cycle in every connected component of any size.
 * 
 * The goal is to find the answer to the problem for every k (1<=k<=n) separately in O(n) time 
 * which leads to O(n^2) overall runtime. (k here stands for k components of the functional graph)
 * To achieve this for a particular k we first notice that every component has a cycle in it.
 * Then:
 * ----> We iterate over the number of nodes j (1 <= j <= n) we want to dedicate to k components
 * ----> We count the number of ways we can choose those j nodes (n choose j)
 * ----> We count the number of ways we can form k cycles from those j nodes (n 'stirling' j)
 * ----> But what about the (n-j) nodes that are not in the cycle? We can attach them to any
 *       of the k cycles and make sure that they don't form a cycle among themselves. According to Cayley's
 *       formula, the number of ways to make labelled forest on n nodes with k connected trees so that the nodes
 *       1, 2, 3, ... k belong to a different tree in the forest is: k * n^(n-k-1). We can use this formula
 *       in our solution: The number of ways to assign (n-j) non-cyclic nodes to k(irrelevant) cycles with j nodes in total
 *       is j * n^(n - j - 1)
 * 
 * ----> We multiply all of the above values to get the answer (number of ways to make a j-node functional
 *       graph with k components) for current j:
 *       (n choose j) * (n 'stirling' j) * j * n^(n - j - 1)
 * 
 * We take the sum over all j for every k and print it as described in the output of the problem.
 * */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 5001;
const int MOD = 1e9+7;

ll pown[N], C[N][N], S[N][N];

int add(int x, int y){
  return (x + y) % MOD;
}

int mul(int x, int y){
  return (1LL * x * y) % MOD;
}

void init_powers(int n){
  pown[0] = 1;
  for(int i = 1; i < N; i++)
    pown[i] = mul(pown[i-1], n);
}

void init_choose(){
  C[0][0] = 1;
  for(int n=1; n<N; n++){
    C[n][0] = C[n][n] = 1;
    for(int k=1; k<n; k++)
      C[n][k] = add(C[n-1][k], C[n-1][k-1]);
  }
}

void init_stirling(){
  S[0][0] = 1;
  for(int n = 1; n < N; n++)
    for(int k = 1; k <= n; k++)
      S[n][k] = add(S[n-1][k-1], mul((n-1), S[n-1][k]));
}

ll T(int n, int k){
  ll sum = 0;
  for(int j = 1; j <= n; j++){
    ll a = C[n][j];  //n choose j
    ll b = S[j][k];  //# of ways to have k disjoint cycles on j nodes
    ll c = (j == n ? 1 : mul(pown[n-j-1], j)); // when j == n, j * n^(n-j-1) = j * n^(-1) = 1
    
    sum = add(sum, mul(a, mul(b, c)));
  }
  return sum;
}

int main(){
  int n;
  scanf("%d", &n);
  
  init_powers(n);
  init_choose();
  init_stirling();
  
  for(int k = 1; k <= n; k++)
    printf("%lld\n", T(n, k));
}
