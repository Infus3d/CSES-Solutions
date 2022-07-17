/*
 * Problem link : https://cses.fi/problemset/task/1131
 * 
 * We can calculate the diameter of the tree in 2 ways: 1. Two simple DFS runs and
 * 2. One DFS with simple DP.
 * The below approach is the 2nd way of finding diameter with dynamic programming.
 * We start off the dfs by choosing an arbitrary node of the tree as the root.
 * During dfs, the only values that need to be tracked are: toLeaf[u] and maxLength[u].
 * ----> toLeaf[u] is the maximum distance from node u to any of its leaf nodes. This
 *       can be calculated by looking into children v of node u and getting maximum
 *       of toLeaf[v]+1 among all such children.
 * ----> maxLength[u] is the maximum length of the path inside u's subtree with u being
 *       the topmost node in this path. This value could also be interpreted as 'the maximum
 *       length path in u's subtree that involves node u' and can be calculated by taking
 *       the sum of two highest toLeaf[] values among u's children: toLeaf[v1] + toLeaf[v2].
 *       v1 is the child with higest toLeaf[] number and v2 is the second highest such child.
 * 
 * The diameter of the tree would then be the maximum over all maxLength[u] values (over all nodes u).
 * You can read about it in more detail: https://cses.fi/book/book.pdf  (Chapter 14, Diameter)
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, toLeaf[N], maxLength[N];
vector<int> E[N];

void dfs(int u, int par){
  int max1 = 0, max2 = 0;
  for(int v : E[u])
    if(v != par){
      dfs(v, u); //u is just v's parent
      toLeaf[u] = max(toLeaf[u], toLeaf[v]+1);
      if(toLeaf[v]+1 > max1)
        max2 = max1, max1 = toLeaf[v]+1; //max2 takes max1's value and max1 become the new maximum
      else if(toLeaf[v]+1 > max2)
        max2 = toLeaf[v]+1; //even if max1 doesn't change, max2 can still change
    }
  
  maxLength[u] = max1 + max2; //just the concatenation of 2 simple max-paths [to leaves]
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<n; i++){
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b);
    E[b].push_back(a);
  }
  
  dfs(1, 0);
  
  int diameter = 0;
  for(int i=1; i<=n; i++)
    diameter = max(diameter, maxLength[i]);
  printf("%d\n", diameter);
  
  return 0;
}
