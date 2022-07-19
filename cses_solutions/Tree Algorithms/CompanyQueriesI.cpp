/*
 * Problem link : https://cses.fi/problemset/task/1687
 * Prereq: 
 * Lowest Common Ancestor and Binary Lifting:
 * ----> https://www.youtube.com/watch?v=dOAxrhAUIhA  <-------- Hopefully you won't need to read other sources after this video
 *       https://cses.fi/book/book.pdf  (Chapter 18)
 *       https://cp-algorithms.com/graph/lca_binary_lifting.html
 *       https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor
 * 
 * This is a classic application of binary lifting on the given tree. Binary lifting
 * refers to the fact that when we want to find k'th ancestor of x, we advance by 2's
 * powers until we hit k'th ancestor.
 * One thing that might help you understand it better using the above sources is that
 * any positive integer x can be written as a sum of 2's powers. For example, 2 = 2^1,
 * 3 = 2^1 + 2^0 and 19 = 2^4 + 2^1 + 2^0. So in binary lifting when we want to find
 * 19th ancestor of x, we first go to (2^4)'th ancestor of x, and then (2^1)'th ancestor
 * of that node, and finally (2^0)'th ancestor of the latter node.
 * 
 * Runtime O((n+q)*log(n)) because n*log(n) to build the ancestry table and log(n) per query.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, P[N][18]; //18 because 17 = log2(2e5)

int main(){
  scanf("%d%d", &n, &q);
  for(int i=2; i<=n; i++){
    int a; scanf("%d", &a);
    P[i][0] = a;
  }
  
  for(int j=1; j<18; j++)
    for(int i=1; i<=n; i++)
      if(P[i][j-1] > 0)
        P[i][j] = P[P[i][j-1]][j-1];
  
  while(q--){
    int x, k;
    scanf("%d%d", &x, &k);
    for(int i=17; i>=0; i--)
      if(k - (1<<i) >= 0){
        k -= (1<<i);
        x = P[x][i];
      }
    
    printf("%d\n", (x == 0 ? -1 : x));
  }
  
  return 0;
}
