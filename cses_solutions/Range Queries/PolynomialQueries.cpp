/*
 * Problem link : https://cses.fi/problemset/task/1736
 * Prereq: 
 * -----> Segment tree with lazy propagation:
 *        https://cses.fi/book/book.pdf  (Section 20.1)
 *        https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation
 * 
 * It is almost like the normal range-add-value-and-range-sum lazy segment tree. However in this problem
 * we are adding the sequences of 1, 2, 3, ... , r-l+1, onto range [l, r]. This sequence is called
 * an arithmetic progression and they are usually represented with 3 values:
 * -----> initial value 'init' of the progression, which is 1 for the example above.
 * -----> the difference 'diff' between the terms in the progression, which is also 1 in our example.
 * -----> the number of terms 'cnt' in the progression, which is (r-l+1) for our example.
 * 
 * The problem asks us to add an arithmetic progression with init = 1, diff = 1 and cnt = r-l+1 into
 * the range. This increases the sum of the range by total of (cnt * (2*init + (cnt-1)*diff) / 2).
 * However some intervals inside [l, r] increases by different amount than some others in segment tree.
 * For any interval though, we can determine initial value the progression should start with and the
 * number of terms for that interval (rightend - leftend+1) and the difference stays the same (1).
 * Once we have the 3 values of the progression we're trying to add into an interval [i, j] we can
 * just add the init to that node's initial value, the diff to that node's difference. These are the
 * values we keep in 'lazy' part of the segment tree. We can increase the sum of the range by the above
 * formula.
 * 
 * The nice addition of the arithmetic progression is one of its properties:
 * Let's say we have a progression A with A.init, A.diff and A.cnt and another one B with its own 3 values.
 * Then to add them into a single progression C, we just need C.init = A.init + B.init, C.diff = A.diff + B.diff
 * and C.cnt = A.cnt (or B.cnt, they're the same for a fixed interval).
 * 
 * For example, imagine we have a segment tree over the array with length 8 and we have 2 upd/add queries
 * (4, 8) and (1, 8). Let's also say that the tree is all 0 initially,
 * -----> upd (4, 8) will start at the root node and go the right child to get the range [4, 8] entirely
 *        in its reach. Then updating this range would make the 'array' (the leaf nodes) effectively
 *        [0, 0, 0, 0, 1, 2, 3, 4].
 * 
 * -----> upd (1, 8) will start at the root node and get the range [1, 8] entirely in its reach. So the update
 *        will effectively add
 *        [1, 2, 3, 4, 5, 6, 7, 8] 
 *        onto
 *        [0, 0, 0, 0, 1, 2, 3, 4]
 *        makign it
 *        [1, 2, 3, 4, 6, 8, 10, 12]
 *        
 *        You can see that for the interval (4, 8) the addition simply made another progression with init = 6,
 *        diff = 2 and cnt = 4.
 * 
 * We can use the addition property of arithmetic progression when updating as well as pushing/flushing parent
 * lazy values onto its children.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y) ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, a[N];

struct node{
  long long sum, init, diff;
} T[N*4];

void build_tree(int l, int r, int v){
  if(l == r){
    T[v].sum = a[l];
    return;
  }
  build_tree(l, mid(l, r), v*2);
  build_tree(mid(l, r)+1, r, v*2+1);
  T[v].sum = T[v*2].sum + T[v*2+1].sum;
}

void process(long long init, long long diff, int cnt, int v){
  T[v].sum += cnt * (2*init + (cnt-1)*diff) / 2;
  T[v].init += init;
  T[v].diff += diff;
}

void push(int l, int r, int v){
  if(T[v].init == 0) 
    return;
    
  process(T[v].init, T[v].diff, mid(l, r)-l+1, v*2);
  process(T[v].init+(mid(l, r)-l+1)*T[v].diff, T[v].diff, r-mid(l, r), v*2+1);
  
  T[v].init = T[v].diff = 0;
}

void upd(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return;
  
  if(x <= l && r <= y){
    process(l-x+1, 1, r-l+1, v);
    return;
  }
  
  push(l, r, v);
  
  upd(x, y, l, mid(l, r), v*2);
  upd(x, y, mid(l, r)+1, r, v*2+1);
  
  T[v].sum = T[v*2].sum + T[v*2+1].sum;
}

long long sum(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return 0LL;
  
  if(x <= l && r <= y)
    return T[v].sum;
  
  push(l, r, v);
  
  return sum(x, y, l, mid(l, r), v*2) + sum(x, y, mid(l, r)+1, r, v*2+1);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  
  build_tree(1, n, 1);
  
  while(q--){
    int t, l, r;
    scanf("%d%d%d", &t, &l, &r);
    if(t == 1)
      upd(l, r, 1, n, 1);
    else
      printf("%lld\n", sum(l, r, 1, n, 1));
  }
  
  return 0;
}
