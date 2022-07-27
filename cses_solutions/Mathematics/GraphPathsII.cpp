/*
 * Problem link : https://cses.fi/problemset/task/1724
 * 
 * Solving Graph Paths I before attempting this problem is strongly recommended.
 * Just like the previous version, we can use the matrix exponentiation idea to
 * find the minimum cost path with k edges. Instead of storing the sum this time
 * we simply store store the minimum path from i to j with k edges in (base^k)[i][j].
 * To unerstand why it works, please refer to the following:
 * https://cp-algorithms.com/graph/fixed_length_paths.html#shortest-paths-of-a-fixed-length
 * 
 * Runtime O(n^3 * log(k))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e2+1;
const long long INF = 2e18+5;

struct matrix{
  int n, m;
  vector<vector<long long>> v;
  matrix(int r, int c, bool identity = false) : n(r), m(c){
    v.resize(r);
    for(int i=0; i<r; i++){
      v[i].resize(c);
      if(identity && r == c)
        v[i][i] = 1;
    }
  }
  
  void fill(long long x){
    for(int i=0; i<n; i++)
      for(int j=0; j<m; j++)
        v[i][j] = x;
  }
  
  matrix operator * (const matrix &u){
    matrix temp(n, u.m);
    temp.fill(INF);
    for(int i=0; i<n; i++)
      for(int j=0; j<u.m; j++)
        for(int k=0; k<m; k++)
          temp.v[i][j] = min(temp.v[i][j], v[i][k] + u.v[k][j]);
    
    return temp;
  }
};

matrix fast_power(matrix base, long long deg){
  matrix res(base.n, base.m);
  bool firstTime = true;
  while(deg > 0){
    if(deg & 1){
      if(firstTime){
        res = base;
        firstTime = false;
      }
      else
        res = res * base;
    }
    base = base * base;
    deg /= 2;
  }
  return res;
}

int main(){
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  matrix base(n, n);
  base.fill(INF);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    a--, b--;
    base.v[a][b] = min(base.v[a][b], (long long)c);
  }
  
  long long ans = fast_power(base, k).v[0][n-1];
  if(ans == INF) ans = -1;
  printf("%lld\n", ans);
  
  return 0;
}
