/*
 * Problem link : https://cses.fi/problemset/task/1138
 * Prereq: 
 * -----> Euler Tour Tehcnique (flattening the tree):
 *        https://usaco.guide/gold/tree-euler?lang=cpp
 * -----> Segment or Fenwick tree:
 *        https://cp-algorithms.com/data_structures/fenwick.html
 *        https://cp-algorithms.com/data_structures/segment_tree.html
 * 
 * I recommend solving Subtree Queries problem before attempting this problem.
 * We assume that we have both the entry (in[u]) and exit (out[u]) times of all nodes in the tree such that
 * the subtree of u can be described in terms of the interval {in[u], out[u]}.
 * Changing the value of a node u from old_value to new_value will basically contribute the difference
 * (new_value - old_value) to the sum of the values on the path from node v to the root node 1 for every
 * such node v in u's subtree. In other words, changing this value will be the same as adding (new_value - old_value)
 * onto every node v in u's subtree. But we should also be careful to not make this difference contribute
 * to nodes outside of u's subtree. To achieve this, we can use the prefix-sum logic where we add +difference
 * to the beginning of the subtree (in[u]) and add -difference to the end of the subtree (out[u]+1) so that
 * whenever taken a sum between 1 and in[u] (entry time of any node u) the result we get is the sum of values
 * on u's path to the root node (which is node 1). We can do point-update-range-sum with both segment tree and
 * fenwick tree. The code below uses fenwick tree because it is relatively faster than segment tree (small constant)
 * even though they both take log(n) time per query.
 * 
 * Potentially better explanation:
 * https://usaco.guide/problems/cses-1138-path-queries/solution
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, cnt;
int d[N], in[N], out[N];
long long fen[N];
vector<int> E[N];

void dfs(int u, int par){
  in[u] = ++cnt;
  for(int v : E[u]){
    if(v != par)
      dfs(v, u);
  }
  out[u] = cnt;
}

void add(int x, int val){
  while(x <= cnt){
    fen[x] += val;
    x += x & (-x);
  }
}

long long sum(int x){
  long long res = 0;
  while(x > 0){
    res += fen[x];
    x -= x & (-x);
  }
  return res;
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &d[i]);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  dfs(1, 0);
  for(int i=1; i<=n; i++){
    add(in[i], d[i]);
    add(out[i]+1, -d[i]);
  }
  
  while(q--){
    int t, a, b;
    scanf("%d%d", &t, &a);
    if(t == 1){
      scanf("%d", &b);
      add(in[a], b-d[a]);
      add(out[a]+1, -(b-d[a]));
      d[a] = b;
    }
    else
      printf("%lld\n", sum(in[a]));
  }
  return 0;
}
