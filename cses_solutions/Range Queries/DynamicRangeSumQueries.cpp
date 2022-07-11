/*
 * Problem link : https://cses.fi/problemset/task/1648
 * 
 * This is the literal application of range sum segment tree. To learn about segment trees
 * please refer to the following:
 * https://cses.fi/book/book.pdf  (Section 9.3)
 * https://www.youtube.com/watch?v=QvgpIX4_vyA
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, a[N];
long long T[N*4];

#define mid(x, y)  ((x+y)/2)

//x << i means shift x to the left i times, or in other words x*(2^i)
void build_tree(int l, int r, int v){
  if(l == r){
    T[v] = a[l];
    return;
  }
  build_tree(l, mid(l, r), v<<1); //v<<1 is basically v*2
  build_tree(mid(l, r)+1, r, v<<1|1); //v<<1|1 is then v*2+1
  
  T[v] = T[v<<1] + T[v<<1|1];
}

void upd(int x, int val, int l, int r, int v){
  if(l == r){
    T[v] = val;
    return;
  }
  if(x <= mid(l, r))
    upd(x, val, l, mid(l, r), v<<1);
  else
    upd(x, val, mid(l, r)+1, r, v<<1|1);
  
  T[v] = T[v<<1] + T[v<<1|1];
}

long long sum(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return 0LL;
  if(x <= l && r <= y)
    return T[v];
  
  return sum(x, y, l, mid(l, r), v<<1) + sum(x, y, mid(l, r)+1, r, v<<1|1);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  
  build_tree(1, n, 1);
  while(q--){
    int t, a, b;
    scanf("%d%d%d", &t, &a, &b);
    if(t == 1)
      upd(a, b, 1, n, 1);
    else
      printf("%lld\n", sum(a, b, 1, n, 1));
  }
  return 0;
}
