/*
 * Problem link : https://cses.fi/problemset/task/1723
 * 
 * Let's create an adjancency matrix where base[i][j] contains the number of
 * directed edges from i to j initially. Then the answer to the problem is
 * (base^k)[1][n] where (base^k) is the base matrix raised to k'th power using
 * binary exponentiation of matrices (log(n^3 * log(k)) complexity).
 * 
 * It is not hard to see what this is the case. Let's refer to the path with length t
 * as t-path. Then:
 * ----> base[i][k] contains the number of 1-paths from i to k
 * ----> base[k][j] contains the number of 1-paths from k to j
 * ----> (base[i][k] * base[k][j]) is the number of 2-paths from i to j through k
 * ----> (base^2)[i][j] = base[i][k] * base[k][j] over all k meaning that (base^2)[i][j]
 *       now contains the total number of 2-paths from i to j.
 * 
 * If you want to learn more: https://cp-algorithms.com/graph/fixed_length_paths.html
 * 
 * Runtime O(n^3 * log(k))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e2+1;
const int MOD = 1e9+7;

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
  
  matrix operator * (const matrix &u){
    matrix temp(n, u.m);
    for(int i=0; i<n; i++)
      for(int j=0; j<u.m; j++)
        for(int k=0; k<m; k++)
          temp.v[i][j] = (temp.v[i][j] + (v[i][k] * u.v[k][j])) % MOD;
    
    return temp;
  }
};

matrix fast_power(matrix base, long long deg){
  matrix res(base.n, base.m, true);
  while(deg > 0){
    if(deg & 1)
      res = res * base;
    base = base * base;
    deg /= 2;
  }
  return res;
}

int main(){
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  matrix base(n, n);
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    a--, b--;
    base.v[a][b]++;
  }
  
  printf("%lld\n", fast_power(base, k).v[0][n-1]);
  
  return 0;
}
