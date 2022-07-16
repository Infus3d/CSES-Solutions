/*
 * Problem link : https://cses.fi/problemset/task/1737
 * 
 * This is a direct application of the persistent segment tree. When asked for a query
 * of 3rd type - when we need to create a copy of k'th array - we just copy the k'th
 * root of the tree to the end of our current arrays list. Later updating this array will
 * generate new nodes [and new root] so it will not modify the actual k'th array.
 * 
 * To learn about persistent segment trees:
 * https://cses.fi/book/book.pdf   (Chapter 28, Dynamic trees onwards)
 * https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
 * https://usaco.guide/adv/persistent?lang=cpp  (Starts with persistent arrays, might be helpful)
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y)  ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, d[N];

struct node{
  node *lef, *rig;
  long long sum;
  node (long long _sum) : sum(_sum) {}
  node(node *l, node *r) : lef(l) , rig(r), sum(0){
    if(l != NULL) sum += l->sum;
    if(r != NULL) sum += r->sum;
  }
};

vector<node*> arrays;

node *build(int l, int r){
  if(l == r) 
    return new node(d[l]);
  return new node(build(l, mid(l, r)), build(mid(l, r)+1, r));
}

node *upd(int x, int val, int l, int r, node *v){
  if(l == r)
    return new node(val);
  
  if(x <= mid(l, r))
    return new node(upd(x, val, l, mid(l, r), v->lef), v->rig);
  else
    return new node(v->lef, upd(x, val, mid(l,r)+1, r, v->rig));
}

long long sum(int x, int y, int l, int r, node *v){
  if(r < x || y < l)
    return 0LL;
  
  if(x <= l && r <= y)
    return v->sum;
  
  return sum(x, y, l, mid(l, r), v->lef) + sum(x, y, mid(l, r)+1, r, v->rig);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &d[i]);
  
  arrays.push_back(build(1, n));
  
  while(q--){
    int t, k, a, b, x;
    scanf("%d%d", &t, &k);
    if(t == 1){
      scanf("%d%d", &a, &x);
      arrays[k-1] = upd(a, x, 1, n, arrays[k-1]);
    }
    else if(t == 2){
      scanf("%d%d", &a, &b);
      printf("%lld\n", sum(a, b, 1, n, arrays[k-1]));
    }
    else{
      arrays.push_back(arrays[k-1]);
    }
  }
  return 0;
}
