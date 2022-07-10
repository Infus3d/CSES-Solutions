/*
 * Problem link : https://cses.fi/problemset/task/1684
 * Prereq: 
 * ----> SCC - strongly connected components:
 *       https://cses.fi/book/book.pdf                 (Chapter 17)
 *       https://www.youtube.com/watch?v=Rs6DXyWpWrI   (Kosaraju's algo, With code)
 *       https://www.youtube.com/watch?v=HOOmetF56BI   (Kosaraju's algo, with pseudo-code but more in-depth)
 * 
 * ----> 2-SAT:
 *       https://cses.fi/book/book.pdf   (Section 17.2)
 *       https://cp-algorithms.com/graph/2SAT.html#implementation
 * 
 * We are given n conditions where we need to satisfy at least one of the two toppings in each one. If we
 * lable +a topping as a statement A and -a topping as a negated statement !A, the problem can be written
 * in terms of propositional logic.
 * 
 * For example:
 * 3 6
 * +a -b
 * +c +d
 * -e +f
 * 
 * we can write the above as
 * (a or !b) and (c or d) and (!e or f)
 * 
 * With this, the problem translates into what's known as 2-SAT (two-satisfaction) problem and there is a well
 * known solution to it. Please refer to the links above for tutorials.
 * 
 * Runtime O(n + m)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, m, comp[N], vis[N];
vector<int> ordered;
vector<int> E[N], rE[N];

int notOf(int u){
  if(u > n) return (u-n);
  return (u+n);
}

void dfs(int u){
  vis[u] = 1;
  for(int v : E[u])
    if(!vis[v])
      dfs(v);
  ordered.push_back(u);
}

void dfs2(int u, int id){
  comp[u] = id;
  for(int v : rE[u])
    if(!comp[v])
      dfs2(v, id);
}

void find_SCCs(){
  for(int i=1; i<=2*n; i++)
    if(!vis[i])
      dfs(i);
  
  int cnt = 0;
  for(int i=0; i<2*n; i++){
    int u = ordered[2*n-i-1];
    if(comp[u] == 0)
      dfs2(u, ++cnt);
  }
}

int main(){
  scanf("%d%d", &m, &n);
  for(int i=0; i<m; i++){
    char ca, cb;
    int a, b;
    scanf(" %c%d %c%d", &ca, &a, &cb, &b);
    if(ca == '-') a = notOf(a);
    if(cb == '-') b = notOf(b);
    
    int na = notOf(a), nb = notOf(b);
    E[na].push_back(b);
    E[nb].push_back(a);
    
    rE[b].push_back(na);
    rE[a].push_back(nb);
  }
  
  find_SCCs();
  
  vector<char> ans;
  for(int u=1; u<=n; u++){
    int nu = notOf(u);
    if(comp[u] == comp[nu]){
      puts("IMPOSSIBLE");
      return 0;
    }
    ans.push_back((comp[u] > comp[nu] ? '+' : '-'));
  }
  
  for(char i : ans)
    printf("%c ", i);
  puts("");
  
  
  return 0;
}
