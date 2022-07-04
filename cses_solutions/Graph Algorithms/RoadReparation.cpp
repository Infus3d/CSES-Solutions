/*
 * Problem link : https://cses.fi/problemset/task/1675
 * 
 * The problem gives a graph and asks to find the minimum spanning tree
 * for this graph. There are 2 well-known algorithms for finding such
 * spanning trees: Kruskal's and Prim's.
 * 
 * You can learn both from the following book: 
 * https://cses.fi/book/book.pdf   (Chapter 15)
 * 
 * The solution below uses the Kruskal's algorithm.
 * Runtime O(n + m*log(m))
 * */

#include "bits/stdc++.h"

using namespace std;

const int N = 1e5+1;

int n, m, par[N];
vector<pair<int, pair<int, int>>> edges;

int findParent(int x){
  if(par[x] == x)
    return x;
  return par[x] = findParent(par[x]);
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    edges.push_back({c, {a, b}});
  }
  sort(edges.begin(), edges.end());
  
  for(int i=1; i<=n; ++i) par[i] = i;
  
  long long ans = 0ll;
  for(auto [c, i] : edges){
    auto [u, v] = i;
    
    if(findParent(u) != findParent(v)){
      ans += c;
      par[findParent(v)] = findParent(u);
    }
  }
  
  printf("%lld\n", ans);
  
  return 0;
}
