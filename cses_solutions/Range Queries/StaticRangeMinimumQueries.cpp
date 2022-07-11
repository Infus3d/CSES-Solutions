/*
 * Problem link : https://cses.fi/problemset/task/1647
 * Prereq:
 * ----> Sparse Table:
 *       https://cses.fi/book/book.pdf   (Section 9.1)
 * 
 * This problem can be solved with both sparse table and segment trees. Sparse table
 * uses precalculated table of minimum values before all queries are encountered, making
 * it an offline/non-dynamic algorithm. The below code uses sparse table because it has
 * a build runtime of O(n*log(n)) but O(1) query time.
 * 
 * Segment tree can be used for both static and dynamic queries but it has O(log(n)) query time.
 * 
 * Runtime O(n*log(n) + q)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, a[N];
int st[N][18]; //sparse table

int main(){
  scanf("%d%d", &n, &q);
  for(int i=0; i<n; i++)
    scanf("%d", &a[i]);
  
  for(int i=0; i<n; i++)
    st[i][0] = a[i];
  
  for(int j=1; j<18; j++)
    for(int i=0; i+(1<<j)<=n; i++)
      st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
  
  vector<int> lg(n+1);
  int currentLog = 0;
  for(int i=1; i<=n; i++){
    if(i == (1<<(currentLog+1)))
      currentLog++;
    lg[i] = currentLog;
  }
  
  while(q--){
    int l, r;
    scanf("%d%d", &l, &r);
    l--; r--;
    int k = lg[r-l+1];
    int ans = min(st[l][k], st[r-(1<<k)+1][k]);
    printf("%d\n", ans);
  }
  
  return 0;
}
