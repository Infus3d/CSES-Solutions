/*
 * Problem link : https://cses.fi/problemset/task/1190/
 * 
 * Prereq :
 * -----> Segment Tree
 *        https://cses.fi/book/book.pdf  (Sectoin 9.3, 9.4)
 * 
 * This is a little harder version of the problem Prefix Sum Queries. In this problem
 * we need to keep track of 4 values in a node of the segment tree corresponding to a
 * range [l, r]:
 * -----> The maximum prefix sum of the range [l, r]
 * -----> The maximum suffix sum of the range [l, r]
 * -----> The sum of the range [l, r]
 * -----> The maximum subarray sum of the range [l, r]
 * 
 * We know how to handle the sum of the range, so the rest are calculated aas follows:
 * -----> The maximum prefix sum. Let's say that current range [l, r] corresponds to the node v
 *        in the tree T. Then T[v].prefix = max(T[v*2].prefix, T[v*2].sum + T[v*2+1].prefx). This
 *        is very similar to what we did in Prefix Sum Queries problem.
 * 
 * -----> The maximum suffix sum. Analagous to max prefix sum, for current node v and its child nodes
 *        v*2 and v*2+1: T[v].suffix = max(T[v*2].suffix, T[v*2].sum + T[v*2+1].suf)
 * 
 * -----> Now when we have all other values of the node, it becomes easy to determine the maximum subarray
 *        sum of the current range. T[v].subarrayMaximum would be the maximum among:
 * ------------> Max subarray sum in the left child T[v*2].subarrayMaximum
 * ------------> Max subarray sum in the right child T[v*2+1].subarrayMaximum
 * ------------> By concatenating the max suffix of the left child and max prefix of the right child, we can
 *               create a new subarray with sum T[v*2].suffix + T[v*2+1].prefix
 * 
 * The problem asks us to find the maximum subarray for the entire array, which is just T[1].subarrayMaximum.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y) ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, a[N];

struct node{
  long long pre, suf, sum, maxx;
} T[N<<2];

node combine(node &l, node &r){
  node ret;
  ret.sum = l.sum + r.sum;
  ret.pre = max(l.pre, l.sum + r.pre);
  ret.suf = max(r.suf, r.sum + l.suf);
  ret.maxx = max(l.suf + r.pre, max(l.maxx, r.maxx));
  return ret;
}

void upd(int x, int val, int l, int r, int v){
  if(l == r){
    T[v] = {val, val, val, val};
    return;
  }
  if(x <= mid(l, r))
    upd(x, val, l, mid(l, r), v<<1);
  else
    upd(x, val, mid(l, r)+1, r, v<<1|1);
  
  T[v] = combine(T[v<<1], T[v<<1|1]);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%d", &a[i]);
    upd(i, a[i], 1, n, 1);
  }
  
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    upd(a, b, 1, n, 1);
    printf("%lld\n", max(0LL, T[1].maxx));
  }
  
  return 0;
}
