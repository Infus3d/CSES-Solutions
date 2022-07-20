/*
 * Problem link : https://cses.fi/problemset/task/1137
 * Prereq: Either BIT/Fenwich-tree or Segment-tree
 * -----> https://cp-algorithms.com/data_structures/fenwick.html
 * -----> https://cp-algorithms.com/data_structures/segment_tree.html
 * 
 * We can flatten the given tree and represent the subtrees of nodes in the tree as a range in the
 * flattened array. To do that, we just need to run a simple dfs and maintain the in[] and out[] times
 * of entry to everynode. Whenever we enter a node u, we increment the counter (cnt) and assign the in[u] = cnt.
 * Afterwards we go into every child of this node u as in a normal dfs and assign out[u] = cnt (without incrementing)
 * right before we leave the node u.
 * 
 * Now, every subtree u in the given tree can be reprsented by the interval [in[u], out[u]] in an array. Here out[u] is
 * the right-end and in[u] is the left-end of the interval and (out[u] - in[u] + 1) = the number of nodes in u's subtree
 * including the node u itself.
 * 
 * With this flattened array (an ranged of each subtree) the problem becomes a very simple single-node-update range-sum
 * query problem. When we want to update the value of the node u to val, we just need to update in[u] to val in whatever
 * data structure we have (either fenwick tree or segment tree). And to get the sum of the subtree u, we just take the sum
 * in the data structure between in[u] and out[u] inclusive.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, d[N], in[N], out[N], cnt;
long long fen[N];
vector<int> E[N];

void dfs(int u, int par){
  in[u] = ++cnt;
  for(int v : E[u])
    if(v != par)
      dfs(v, u);
  out[u] = cnt;
}

void add(int x, int val){
  while(x <= n){
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

long long query(int a, int b){
  return (sum(b) - sum(a-1));
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
  for(int i=1; i<=n; i++) //put the initial values into the data structure
    add(in[i], d[i]);
  
  while(q--){
    int t, a, b;
    scanf("%d%d", &t, &a);
    if(t == 1){
      scanf("%d", &b);
      add(in[a], b-d[a]);
      d[a] = b;
    }
    else
      printf("%lld\n", query(in[a], out[a]));
  }
  
  return 0;
}
