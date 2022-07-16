/*
 * Problem link : https://cses.fi/problemset/task/1735
 * 
 * When we have range updates **and** range queries we have to use lazy propagation
 * with segment trees. This problem asks us to do both 'set' and 'add' operations
 * together.
 * 
 * We just need to keep track of 3 values in each node: sum, lazy-value-to-add and
 * lazy-value-to-set of its range. When an add operation comes, we do it as we would
 * with normal lazy-sum-segment-tree. However when 'set' operation comes to a speicific
 * range, it 'nullifies' all 'set' and 'add' operations that was made before on this
 * range. For that we simply make the lazy-value-to-add and lazy-value-to-set equal to 0
 * and then do the 'set' operation afterwards. Same with parent-child pushing/flushing
 * processes.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y) ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, d[N];

struct node{
  long long sum, lzadd, lzset;
} T[N*4];

void processAdd(long long val, int l, int r, int v){
  T[v].sum += val * (r-l+1);
  T[v].lzadd += val;
}

void processSet(long long val, int l, int r, int v){
  T[v].sum = val * (r-l+1);
  T[v].lzadd = 0;
  T[v].lzset = val;
}

void push(int l, int r, int v){
  if(T[v].lzset > 0){
    processSet(T[v].lzset, l, mid(l, r), v*2);
    processSet(T[v].lzset, mid(l, r)+1, r, v*2+1);
    T[v].lzset = 0;
  }
  
  if(T[v].lzadd > 0){
    processAdd(T[v].lzadd, l, mid(l, r), v*2);
    processAdd(T[v].lzadd, mid(l, r)+1, r, v*2+1);
    T[v].lzadd = 0;
  }
}

void updAdd(int x, int y, long long val, int l, int r, int v){
  if(r < x || y < l)
    return;
  
  if(x <= l && r <= y){
    processAdd(val, l, r, v);
    return;
  }
  
  push(l, r, v);
  
  updAdd(x, y, val, l, mid(l, r), v*2);
  updAdd(x, y, val, mid(l, r)+1, r, v*2+1);
  
  T[v].sum = T[v*2].sum + T[v*2+1].sum;
}

void updSet(int x, int y, long long val, int l, int r, int v){
  if(r < x || y < l)
    return;
  
  if(x <= l && r <= y){
    processSet(val, l, r, v);
    return;
  }
  
  push(l, r, v);
  
  updSet(x, y, val, l, mid(l, r), v*2);
  updSet(x, y, val, mid(l, r)+1, r, v*2+1);
  
  T[v].sum = T[v*2].sum + T[v*2+1].sum;
}

long long getSum(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return 0LL;
  
  if(x <= l && r <= y)
    return T[v].sum;
  
  push(l, r, v);
  
  return getSum(x, y, l, mid(l, r), v*2) + getSum(x, y, mid(l, r)+1, r, v*2+1);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%d", &d[i]);
    updSet(i, i, d[i], 1, n, 1);
  }
  
  while(q--){
    int t, a, b, x;
    scanf("%d%d%d", &t, &a, &b);
    if(t == 1){
      scanf("%d", &x);
      updAdd(a, b, x, 1, n, 1);
    }
    else if(t == 2){
      scanf("%d", &x);
      updSet(a, b, x, 1, n, 1);
    }
    else
      printf("%lld\n", getSum(a, b, 1, n, 1));
  }
  
  return 0;
}
