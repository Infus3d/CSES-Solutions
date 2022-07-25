/*
 * Problem link : https://cses.fi/problemset/task/1722
 * 
 * N'th fibonacci number can be found by raising a certain matrix to a certain degree.
 * The matrix itself and the degree varies depending on how you define the matrix.
 * The code below uses the matrix |0, 1| which is the same as the one in the book
 * https://cses.fi/book/book.pdf  |1, 1|
 * Please refer to the Fibonacci Numbers section of Chapter 23 of this book to understand
 * the properties of fibonacci numbers and how to find them with matrices.
 * To fully comprehend and even try other examples of matrix exponentiation please refer
 * to the blog: https://codeforces.com/blog/entry/80195
 * 
 * Runtime (k^3 * log(n)) where k is the size of the matrix which is just 2 here
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

struct matrix{
  long long a, b, c, d;
};

matrix mul(matrix &x, matrix &y){
  matrix ret;
  ret.a = ((x.a * y.a)%MOD + (x.b * y.c)%MOD) % MOD;
  ret.b = ((x.a * y.b)%MOD + (x.b * y.d)%MOD) % MOD;
  ret.c = ((x.c * y.a)%MOD + (x.d * y.c)%MOD) % MOD;
  ret.d = ((x.c * y.b)%MOD + (x.d * y.d)%MOD) % MOD;
  return ret;
}

matrix bmod(matrix x, long long deg){
  if(!deg) return (matrix){1, 0, 0, 1}; //identity matrix
  if(deg == 1) return x; //return x^1
  
  matrix half = bmod(x, deg/2);
  matrix full = mul(half, half);
  if(deg % 2 == 1)
    full = mul(full, x);
  
  return full;
}

int main(){
  long long n;
  scanf("%lld", &n);
  
  matrix a = {0, 1, 1, 1};
  printf("%lld\n", bmod(a, n).b);
  
  return 0;
}
