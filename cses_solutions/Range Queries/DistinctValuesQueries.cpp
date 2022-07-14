/*
 * Problem link : https://cses.fi/problemset/task/1734
 * Prereq :
 * ----> Segment tree or Binary Indexed tree:
 *       https://cses.fi/book/book.pdf  (Chapter 9)
 * 
 * This is a well known problem that can be solved with not only segment trees but also
 * Mo's algorithm in O(n + q^(3/2)).
 * Please refer to the following tutorial for O(n + q*(log(n) + log(q))) solution:
 * https://usaco.guide/problems/cses-1734-distinct-values-queries/solution
 * 
 * The tutorial uses BIT but the code below uses segment tree. In practice BIT is faster than
 * segment tree but has less functionality. It is very useful in strict time limited problems.
 * 
 * Runtime O(n + q*(log(n) + log(q)))
 * */
#include "bits/stdc++.h"

#define mid(x, y)  ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, a[N], ans[N], T[N<<2];
pair<pair<int, int>, int> queries[N];
map<int, int> lastVisited;

void upd(int x, int val, int l, int r, int v){
  if(l == r){
    T[v] += val;
    return;
  }
  if(x <= mid(l, r))
    upd(x, val, l, mid(l, r), v<<1);
  else
    upd(x, val, mid(l, r)+1, r, v<<1|1);
  T[v] = T[v<<1] + T[v<<1|1];
}

int get(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return 0;
  if(x <= l && r <= y)
    return T[v];
  return get(x, y, l, mid(l, r), v<<1) + get(x, y, mid(l, r)+1, r, v<<1|1);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  
  for(int i=1; i<=q; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    queries[i] = {{b, a}, i};
  }
  
  sort(queries+1, queries+q+1);
  
  int curptr = 1;
  for(int i=1; i<=q; i++){
    auto [r, l] = queries[i].first;
    while(curptr <= r){
      if(lastVisited.find(a[curptr]) != lastVisited.end())
        upd(lastVisited[a[curptr]], -1, 1, n, 1);
      
      upd(curptr, +1, 1, n, 1);
      lastVisited[a[curptr]] = curptr;
      curptr++;
    }
    ans[queries[i].second] = get(l, r, 1, n, 1);
    //~ printf("%d %d %d\n", l, r, ans[queries[i].second]);
  }
  
  for(int i=1; i<=q; i++)
    printf("%d\n", ans[i]);
  
  return 0;
}
