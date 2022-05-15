/*
 * Problem link : https://cses.fi/problemset/task/1744
 * Thorough explanation : https://codeforces.com/blog/entry/70018
 * (You might need to scroll down to locate the problem)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 501;

int a, b;
int dp[N][N];

int rec(int x, int y){
  if(x == y)  //whenever we have a square, we stop cutting
    return 0;
  
  int &ret = dp[x][y];
  if(ret != -1) return ret; //if we have visited this same exact state before, we just return its saved value
  
  ret = (int)1e9;
  for(int i=1; i<x; i++)   //cutting horizontally
    ret = min(ret, rec(i, y) + rec(x-i, y) + 1);
  
  for(int i=1; i<y; i++)   //cutting vertically
    ret = min(ret, rec(x, i) + rec(x, y-i) + 1);
  
  return ret;
}

int main(){
  scanf("%d%d", &a, &b);
  
  memset(dp, -1, sizeof dp);
  printf("%d\n", rec(a, b));
  
  return 0;
}
