/*
 * Problem link : https://cses.fi/problemset/task/1674
 *  
 * We can do a very simple dp on the given tree. Let's maintain array childCnt[]
 * where childCnt[u] keeps the number of children/subordinates it has.
 * To calculate these values, we run a dfs from the root node - node 1:
 * ----> We look through the neighbors or in this case subordinates v of current node u
 *       in dfs.
 * ----> We go into these neighbors to calculate their childCnt[v] values first
 * ----> After their values are calculated and dfs backtracks, we add (childCnt[v]+1)
 *       onto childCnt[u]. +1 because v is also the subordinate of u.
 * 
 * We can just print out the childCnt[] array as an answer.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, childCnt[N];
vector<int> E[N];

void dfs(int u){
  for(int v : E[u]){
    dfs(v);
    childCnt[u] += childCnt[v] + 1;
  }
}

int main(){
  scanf("%d", &n);
  for(int i=2; i<=n; i++){
    int a; scanf("%d", &a);
    E[a].push_back(i);
  }
  
  dfs(1);
  for(int i=1; i<=n; i++)
    printf("%d ", childCnt[i]);
  
  return 0;
}
