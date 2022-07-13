/*
 * Problem link : https://cses.fi/problemset/task/1143
 * 
 * The problem asks us to find the left-most leaf-node in the segment tree that has
 * enough rooms for the given group count. Keep in mind that leaf-nodes represent
 * the hotels and values at those nodes are the room counts of the hotels.
 * 
 * Since we know what value we are looking for, we can build a max-segment tree and
 * walk in the tree to find the left-most node that has value greater than what we
 * are looking for. We start from the root node and see if this range [1, n] contains a hotel
 * that has rooms more than our current group-member-count val. If not, then we return 0.
 * If yes, that is if value at that node T[v] >= val, then such hotel is either in the left
 * or right child. Since we need to assign the groups to the smallest numbered hotel that
 * has enough rooms, we first look into the left child. If the returned value from the left
 * child is anything but 0, then that would be the index of the hotel that we place the current
 * group in. If it is 0, then we look into the right child.
 * We stop the recursion once we hit singularity - when l == r - we know that we have found a particular
 * hotel with rooms >= val. So we just update the room count with T[v] -= val and return the index of the
 * hotel which is l (or r, they're equal).
 * 
 * Potential better explanation:
 * https://usaco.guide/plat/segtree-ext?lang=cpp
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, m, a[N], T[N<<2]; //N<<2 is the same as N*4, it left-shiftes N twice

#define mid(x, y) ((x+y)/2)

void build_tree(int l, int r, int v){
  if(l == r){
    T[v] = a[l];
    return;
  }
  build_tree(l, mid(l, r), v<<1);
  build_tree(mid(l, r)+1, r, v<<1|1);
  T[v] = max(T[v<<1], T[v<<1|1]);
}

int find_and_update(int val, int l, int r, int v){
  if(T[v] < val) //if there is no hotel in this range with enough rooms
    return 0;
  if(l == r){
    T[v] -= val;
    return l;
  }
    
  //we first check the left child, because we need to place in them in the smallest numbered possible hotel
  int ret = find_and_update(val, l, mid(l, r), v<<1);
  T[v] = max(T[v<<1], T[v<<1|1]);
  if(ret > 0)
    return ret;
  
  //if left side hotels do not have enough rooms, we resort to right side
  ret = find_and_update(val, mid(l, r)+1, r, v<<1|1);
  T[v] = max(T[v<<1], T[v<<1|1]);
  return ret;
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  
  build_tree(1, n, 1);
  
  for(int i=1; i<=m; i++){
    int b; scanf("%d", &b);
    printf("%d ", find_and_update(b, 1, n, 1));
  }
  return 0;
}
