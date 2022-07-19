/*
 * Problem link : https://cses.fi/problemset/task/2134
 * Prereq:
 * ----> Segment Tree: https://cp-algorithms.com/data_structures/segment_tree.html
 * ----> Lowest Common Ancestor: https://cp-algorithms.com/graph/lca.html
 * ----> Heavy-light decomposition: https://cp-algorithms.com/graph/hld.html#sum-of-the-numbers-on-the-path-between-two-vertices
 * 
 * This is the entry level problem in heavy-light decomposition tutorials. The aim of the algorithm
 * is to divide the tree into multiple heavy and light paths so and construct a segment tree on each
 * of these paths. The best feature of heavy-light decomposition is that there can be at most log(n)
 * number of heavy paths (and such path-switches) from any node to the root of the tree. Since each
 * of these paths contain a single-node-update range-max segment tree every log(n) path switches will
 * cost another log(n) time for segment tree search. So each query in the problem is answer in log(n)^2
 * time which is still pretty fast.
 * 
 * Please refer to the tutorial above to learn about HLD.
 * 
 * Runtime O(n*log(n) + q*log(n)^2)
 * */
#include "bits/stdc++.h"

#define mid(x, y) ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, d[N], P[N][18];
int T[N<<2]; //T is for a very simple single-node-update and range-max segment tree
vector<int> E[N];

/*
 * Implementation for HLD below is taken/adapted from
 * https://cp-algorithms.com/graph/hld.html#implementation
 * */

vector<int> parent, depth, heavy, head, pos, nodeCnt;
int cur_pos;

void dfs(int u){
  nodeCnt[u] = 1;
  int max_cur_size = 0;
  
  for(int v : E[u]){
    if(v != parent[u]){
      parent[v] = u;
      depth[v] = depth[u] + 1;
      dfs(v);
      nodeCnt[u] += nodeCnt[v];
      
      if(nodeCnt[v] > max_cur_size)
        max_cur_size = nodeCnt[v], heavy[u] = v;
    }
  }
}

//this is just another dfs that decomposes the tree inti heavy and light paths
void decompose(int u, int h){
  head[u] = h, pos[u] = ++cur_pos;
  if(heavy[u] != -1)
    decompose(heavy[u], h);
  
  for(int v : E[u]){
    if(v != parent[u] && v != heavy[u])
      decompose(v, v);
  }
}

void initHLD(){
  parent = vector<int>(n+1); //these vectors are initiated with 0
  depth = vector<int>(n+1);
  heavy = vector<int>(n+1, -1);
  head = vector<int>(n+1);
  pos = vector<int>(n+1);
  nodeCnt = vector<int>(n+1);
  cur_pos = 0;
  
  dfs(1);
  decompose(1, 1);
}

void build_lca(){
  for(int i=1; i<=n; i++)
    P[i][0] = parent[i];
  
  for(int j=1; j<18; j++)
    for(int i=1; i<=n; i++)
      if(P[i][j-1] > 0)
        P[i][j] = P[P[i][j-1]][j-1];
}

int lca(int u, int v){
  if(depth[u] < depth[v])
    swap(u, v);
  
  for(int i=17; i>=0; i--)
    if(depth[u] - (1<<i) >= depth[v])
      u = P[u][i];
  
  if(u == v) return u;

  for(int i=17; i>=0; i--)
    if(P[u][i] != P[v][i])
      u = P[u][i], v = P[v][i];
  
  return P[u][0];
}

void upd(int x, int val, int l, int r, int v){
  //~ printf("%d %d %d %d %d\n", x, val, l, r, v);
  if(l == r){
    T[v] = val;
    return;
  }
  
  if(x <= mid(l, r))
    upd(x, val, l, mid(l, r), v*2);
  else
    upd(x, val, mid(l, r)+1, r, v*2+1);
  
  T[v] = max(T[v*2], T[v*2+1]);
}

int get(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return 0;
  
  if(x <= l && r <= y)
    return T[v];
  
  return max(get(x, y, l, mid(l, r), v*2), get(x, y, mid(l, r)+1, r, v*2+1));
}

int query(int a, int b){
  int res = d[a];
  //~ for(; head[a] != head[b]; b = parent[head[b]])
    //~ res = max(res, get(pos[head[b]], pos[b], 1, cur_pos, 1));
  //~ res = max(res, get(pos[a], pos[b], 1, cur_pos, 1));
  
  while(a != b){
    if(head[b] == b){
      res = max(res, d[b]);
      b = parent[b];
    }
    else if(depth[head[b]] > depth[a]){
      res = max(res, get(pos[head[b]], pos[b], 1, cur_pos, 1));
      b = parent[head[b]];
    }
    else{
      res = max(res, get(pos[a], pos[b], 1, cur_pos, 1));
      break;
    }
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
  
  initHLD();
  build_lca();
  
  for(int i=1; i<=n; i++)
    upd(pos[i], d[i], 1, cur_pos, 1);
  
  while(q--){
    int t, a, b;
    scanf("%d%d%d", &t, &a, &b);
    if(t == 1){
      d[a] = b;
      upd(pos[a], b, 1, cur_pos, 1);
    }
    else{
      int c = lca(a, b);
      printf("%d ", max(query(c, a), query(c, b))); //two different paths to the lca from 2 lower nodes
    }
  }
  
  return 0;
}
