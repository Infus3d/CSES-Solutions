/*
 * Problem link : https://cses.fi/problemset/task/1096
 * 
 * We can translate the problem into a linear recurrence of the form:
 * f(n) = f(n-1) + f(n-2) + f(n-3) + f(n-4) + f(n-5) + f(n-6)
 * 
 * where f(n) is the answer to the problem with input n:
 * the number of ways to get the sum by throwing a dice.
 * 
 * Just like fibonacci numbers - that have linear recurrece fib(n) = fib(n-1) + fib(n-2) -
 * we can build a square matrix of the recurrence f() and take its result
 * raised to the exponent n before finally multiplying it with input matrix to get the
 * answer for f(n).
 * To understand the solution I recommend taking your time to fully understand the concept
 * using following sources (not all necessary, but jump to next one if you're still confused):
 * https://cses.fi/book/book.pdf   (Chapter 23, Linear Recurrences)
 * https://codeforces.cc/blog/entry/67776
 * https://www.geeksforgeeks.org/find-nth-term-a-matrix-exponentiation-example/
 * https://codeforces.com/blog/entry/80195
 * 
 * Runtime O(k^3 * log(n)) where k = 6 here.
 * */
#include "bits/stdc++.h"

using namespace std;

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
  matrix res(6, 6, true);
  while(deg > 0){
    if(deg & 1)
      res = res * base;
    base = base * base;
    deg /= 2;
  }
  return res;
}

int main(){
  long long n;
  scanf("%lld", &n);
  matrix base(6, 6);
  for(int i=0; i<6; i++){
    for(int j=0; j<6; j++){
      if(i == 5 || i+1 == j)
        base.v[i][j] = 1;
    }
  }
  
  matrix npower = fast_power(base, n);
  
  matrix initial(6, 1);
  initial.v[0][0] = 1;
  initial.v[1][0] = 1;
  initial.v[2][0] = 2;
  initial.v[3][0] = 4;
  initial.v[4][0] = 8;
  initial.v[5][0] = 16;
  
  matrix ans = npower * initial;
  
  printf("%lld\n", ans.v[0][0]);
  
  return 0;
}
