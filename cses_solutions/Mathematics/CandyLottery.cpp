/*
 * Problem link : https://cses.fi/problemset/task/1727
 * 
 * For each i from 1 to k, we can calculate the probability of giving n children
 * candies such the maximum among them is i. We can them multiply this probability
 * by i to get the expected maximum for this i. To get the overall expected maximum
 * number of candies, we can add contributions of each i.
 * To find the probability of giving n children at most i candies each (and at least one
 * such i) we can subtract ((i-1)/k)^n from (i/k)^n. This is because the probability of
 * distributing at most i candies to n children is (i/k)^n and among those ((i-1)/k)^n
 * have no i candies distributed (over all children).
 * 
 * Runtime O(k*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

double bmod(double x, int deg){
  if(!deg) return 1.0;
  if(deg == 1) return x;
  double half = bmod(x, deg/2);
  double full = half * half;
  if(deg % 2) full = full * x;
  return full;
}

int main(){
  int n, k;
  scanf("%d%d", &n, &k);
  
  double ans = 0.0;
  for(int i=1; i<=k; i++){
    double prob = bmod((double)i/k, n) - bmod((double)(i-1)/k, n);
    ans += prob * (double)i;
  }
  printf("%.6lf\n", ans);
  
  return 0;
}
