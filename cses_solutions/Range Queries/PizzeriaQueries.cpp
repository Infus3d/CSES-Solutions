/*
 * Problem link : https://cses.fi/problemset/task/2206
 * Prereq:
 * ---> Segment trees:
 *      https://cses.fi/book/book.pdf   (Section 9.3, 9.4)
 *  
 * In problem statement, p_a+|a−b| is in fact:
 * -----> p_a + (a - b) if a >= b
 * -----> p_a + (b - a) if a < b
 * 
 * Since for every query, we have our b fixed - that is we know what building we ordering pizza
 * from, and it stays constant for all a that we look for - we can just try to minimize
 * (p_a + a) for pizzerias on the right side of b, and minimize (p_a - a) for pizzerias on the left
 * side of b. We can maintain 2 minimum segment trees: Left and Right where Left segment tree holds
 * values for the left side -> (p_a - a) and Right segment tree holds values of each pizzeria for
 * the right side -> (p_a + a).
 * When querying for the minimal price from position b, we can get the minimal value in the range
 * [1, b] from Left segment tree and add b to make it (p_a - a + b) and also get the minimal value
 * in the range [b, n] from the Right segment tree and subtract b from it to make it (p_a + a - b).
 * We print the min of these 2 prices as a result.
 * 
 * Please refer to this link to understand it better:
 * https://usaco.guide/problems/cses-2206-pizzeria-queries/solution
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y)  ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, a[N];

struct segtree{
  vector<int> T;
  
  segtree(){ T = vector<int>(N*4, INT_MAX); }
  
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
} L, R;

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%d", &a[i]);
    L.upd(i, a[i]-i, 1, n, 1);
    R.upd(i, a[i]+i, 1, n, 1);
  }
  
  while(q--){
    int t, a, b;
    scanf("%d%d", &t, &a);
    if(t == 1){
      scanf("%d", &b);
      L.upd(a, b-a, 1, n, 1);
      R.upd(a, b+a, 1, n, 1);
    }
    else{
      int lef = L.get(1, a, 1, n, 1) + a;
      int rig = R.get(a, n, 1, n, 1) - a;
      printf("%d\n", min(lef, rig));
    }
  }
  
  return 0;
}
