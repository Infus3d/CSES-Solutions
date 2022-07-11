/*
 * Problem link : https://cses.fi/problemset/task/1649
 * 
 * Just like dynamic range sum queries, this problem can also be solved by segment
 * trees. All we need to do is to turn the sum of the two child nodes into the minimum
 * of the said child nodes. And modify the range_min function (in the code below, it is
 * get()).
 * 
 * You can learn about segment trees via following:
 * https://cses.fi/book/book.pdf  (Section 9.3)
 * https://www.youtube.com/watch?v=QvgpIX4_vyA
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, a[N];
int T[N*4];

#define mid(x, y)  ((x+y)/2)

//x << i means shift x to the left i times, or in other words x*(2^i)
void build_tree(int l, int r, int v){
  if(l == r){
    T[v] = a[l];
    return;
  }
  build_tree(l, mid(l, r), v<<1); //v<<1 is basically v*2
  build_tree(mid(l, r)+1, r, v<<1|1); //v<<1|1 is then v*2+1
  
  T[v] = min(T[v<<1], T[v<<1|1]);
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
  
  T[v] = min(T[v<<1], T[v<<1|1]);
}

int get(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return INT_MAX;
  if(x <= l && r <= y)
    return T[v];
  
  return min(get(x, y, l, mid(l, r), v<<1), get(x, y, mid(l, r)+1, r, v<<1|1));
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
      printf("%d\n", get(a, b, 1, n, 1));
  }
  return 0;
}
