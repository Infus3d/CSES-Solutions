/*
 * Problem link : https://cses.fi/problemset/task/2166/
 * 
 * Let's build a segment tree over the input array that maintains 2 crucial
 * information in each of its intervals[l, r]:
 * -----> 1. The maximum prefix sum in this interval [l, r]
 * -----> 2. The sum of the values of this interval [l, r]
 * 
 * We already know how to calculate the sum in the segment tree: 
 * S[parent] = S[left-child] + S[right-child].
 * 
 * The maximum prefix-sum P[parent] of the parent range [l, r] is the maximum of the following:
 * -------> P[left-child] because it might be optimal to just take the maximum of the left child.
 * -------> S[left-child] + P[right-chlid] because it might be optimal to extend the prefix into
 *          the right child, which includes the entirely of the left-child and the prefix of the
 *          right child.
 * 
 * We implement the build, update and getMax methods' transitions [between parent and its children]
 * as described above.
 * 
 * Finally, we can just print out the maximum prefix sum we get from getMax method.
 * In the code below, instead of keeping 2 separate arrays S and P we only keep one array T as a pair
 * of long long integers, where T[i].first = P[i] and T[i].second = S[i].
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y) ((x+y)/2)  //compiler replaces all mid(x, y) with ((x+y)/2)

using namespace std;

const int N = 2e5+1;

typedef pair<long long, long long> pll; //just re-naming the type to be something smaller

int n, q, a[N];
pll T[N<<2]; //N<<2 ----> left-shifting twice = N*4

pll process(pll L, pll R){
  pll M;
  M.first = max(L.first, L.second + R.first);
  M.second = L.second + R.second;
  return M;
}

void build_tree(int l, int r, int v){
  if(l == r){
    T[v] = {max(0, a[l]), a[l]};
    return;
  }
  build_tree(l, mid(l, r), v<<1);
  build_tree(mid(l, r)+1, r, v<<1|1);
  
  T[v] = process(T[v<<1], T[v<<1|1]);
}

void upd(int x, int val, int l, int r, int v){
  if(l == r){
    T[v] = {val, val};
    return;
  }
  if(x <= mid(l, r))
    upd(x, val, l, mid(l, r), v<<1);
  else
    upd(x, val, mid(l, r)+1, r, v<<1|1);
  
  T[v] = process(T[v<<1], T[v<<1|1]);
}

pll getMax(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return {0, 0};
  
  if(x <= l && r <= y)
    return T[v];
  
  auto lef = getMax(x, y, l, mid(l, r), v<<1);
  auto rig = getMax(x, y, mid(l, r)+1, r, v<<1|1);
  
  return process(lef, rig);
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
      printf("%lld\n", getMax(a, b, 1, n, 1).first);
  }
  
  return 0;
}
