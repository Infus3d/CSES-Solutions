/*
 * Problem link : https://cses.fi/problemset/task/1160
 * Prereq:
 * Binary lifting/jumping : https://usaco.guide/plat/binary-jump?lang=cpp
 * Topological sort : https://cses.fi/book/book.pdf  (Section 16.1)
 * Lowest common ancestor : https://cses.fi/book/book.pdf  (Section 18.3)
 * 
 * You can find a nice solution of this problem via this link:
 * https://usaco.guide/problems/cses-1160-planets-queries-ii/solution
 * 
 * Runtime is O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, t[N];
int inDeg[N], distToCycle[N];
int inCycleDist[N], root[N];
int cycleID[N], cycleHead[N], cycleSize[N];
int P[N][18];

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%d", &t[i]);
    inDeg[t[i]]++;
  }
  
  queue<int> Q;
  for(int i=1; i<=n; i++)
    if(inDeg[i] == 0)
      Q.push(i);
  
  vector<int> sorted;
  while(!Q.empty()){
    int u = Q.front();
    int v = t[u];
    
    Q.pop();
    sorted.push_back(u);
    
    inDeg[v]--;
    if(inDeg[v] == 0)
      Q.push(v);
  }
  
  int cycleid = 0;
  memset(inCycleDist, -1, sizeof(inCycleDist));
  for(int i=1; i<=n; i++)
    if(inDeg[i] > 0 && inCycleDist[i] == -1){
      int u = i, cnt = 0;
      cycleid++;
      
      while(inCycleDist[u] == -1){
        inCycleDist[u] = cnt++; //these distances are from node cycleHead[cycleid] to node u
        cycleID[u] = cycleid;
        u = t[u];
      }
      cycleHead[cycleid] = i;
      cycleSize[cycleid] = cnt;
    }
  
  for(int i=sorted.size()-1; i>=0; i--){
    int u = sorted[i], v = t[sorted[i]];
    
    if(inCycleDist[v] != -1) //then it is root of this tree
      root[u] = v;
    else
      root[u] = root[v];
    
    distToCycle[u] = distToCycle[v]+1;
    cycleID[u] = cycleID[v];
  }
  
  for(int i=1; i<=n; i++)
    P[i][0] = t[i];
  
  for(int j=1; j<18; j++)
    for(int i=1; i<=n; i++)
      if(P[i][j-1] != 0)
        P[i][j] = P[P[i][j-1]][j-1];
  
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    
    if(inCycleDist[a] == -1 && inCycleDist[b] == -1){ //they are both not in a cycle, i.e they are both in a tree
      int dist = -1;
      if(root[a] == root[b] && distToCycle[b] <= distToCycle[a]){
        int distDifference = distToCycle[a] - distToCycle[b];
        
        int x = a;
        for(int i=17; i>=0; i--)
          if(distDifference >= (1 << i)){
            distDifference -= (1 << i);
            x = P[x][i];
          }
        
        if(x == b)
          dist = distToCycle[a] - distToCycle[b];
      }
      
      printf("%d\n", dist);
    }
    else if(inCycleDist[a] != -1 && inCycleDist[b] != -1){ //they are both in a cycle
      int dist = -1;
      if(cycleID[a] == cycleID[b]){
        dist = inCycleDist[b] - inCycleDist[a];
        if(dist < 0)
          dist += cycleSize[cycleID[a]];
      }
      
      printf("%d\n", dist);
    }
    else{ //one is in a cycle, the other is in a tree
      int dist = -1;
      if(inCycleDist[a] == -1 && cycleID[a] == cycleID[b]){
        dist = distToCycle[a];
        
        int csize = cycleSize[cycleID[root[a]]];
        dist += ((inCycleDist[b] - inCycleDist[root[a]]) + csize) % csize;
      }
      
      printf("%d\n", dist);
    }
  }
  
  return 0;
}
