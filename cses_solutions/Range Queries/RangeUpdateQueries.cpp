/*
 * Problem link : https://cses.fi/problemset/task/1651
 * 
 * Since we have a range update query, our previous ways of using segment tree update
 * will not work because they were singular index updates only.
 * The range update and range sum queries can be solved with lazy propagation
 * added to a segment tree but it adds a slight complexity to the code. Please
 * refer to following to learn about lazy-propagation:
 * https://cses.fi/book/book.pdf    (Section 28.1)
 * https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation
 * 
 * However, since this problem only requires a singular index get_sum queries, we can consider
 * the 'lazy' array/tree in lazy-propagation as reduntant. When we have a range update [a, b] += c
 * we can update all segments [l, r] that lie entirely in [a, b] with +c.
 * 
 * Let's add 3 into range [3, 6] in the array a[] = {1, 1, 1, 4, 3, 6, 1, 2} (length 8).
 * We can visualize the segment tree as:
 * 
 *                             [1, 1, 1, 4, 3, 6, 1, 2]
 *                          [1, 1, 1, 4]      [3, 6, 1, 2]
 *                        [1, 1]   [1, 4]    [3, 6]   [1, 2]
 *                       [1] [1]   [1] [4]   [3] [6]  [1], [2]
 * 
 * The actual values in the tree are however:
 *                                       [0]
 *                              [0]                [0]
 *                         [0]      [0]        [0]      [0]
 *                       [1] [1]  [1] [4]    [3] [6]  [1] [2]
 * 
 * Now the range [3, 6] here will include the elements [1, 4, 3, 6] which includes 2 intervals
 * [3, 4] and [5, 6] that lie completely inside [3, 6]. We can simply add +c to these intervals
 * and 'collect' them later on our way up/down when we look for the sum at specific index i.
 * The tree looks like this after +3 update of the range [3, 6]:
 *                                       [0]
 *                              [0]                [0]
 *                         [0]      [3]        [3]      [0]
 *                       [1] [1]  [1] [4]    [3] [6]  [1] [2]
 * 
 * Let's say that we want to find the sum at index 5, which corresponds to the value 5 in the initial
 * array. The answer to the query would just be the sum of the nodes from root node to node that corresponds
 * to index 5: [0] + [0] + [3] + [3] = 6.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, a[N]; //we take N*3 can be too little
long long T[N*4];

#define mid(x, y) ((x+y)/2)

void upd(int x, int y, int val, int l, int r, int v){
  if(r < x || y < l)
    return;
  
  if(x <= l && r <= y){
    T[v] += val;
    return;
  }
  
  upd(x, y, val, l, mid(l, r), v<<1);
  upd(x, y, val, mid(l, r)+1, r, v<<1|1);
}

long long get(int x, int l, int r, int v){
  if(l == r)
    return T[v];
  
  if(x <= mid(l, r))
    return T[v] + get(x, l, mid(l, r), v<<1);
  else
    return T[v] + get(x, mid(l, r)+1, r, v<<1|1);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  
  //build_tree(1, n, 1); I commented it out because we can use upd range [i, i] with a[i] and it will be still be O(n*log(n))
  for(int i=1; i<=n; i++)
    upd(i, i, a[i], 1, n, 1);
  
  while(q--){
    int t, a, b, c;
    scanf("%d%d", &t, &a);
    if(t == 1){
      scanf("%d%d", &b, &c);
      upd(a, b, c, 1, n, 1);
    }
    else
      printf("%lld\n", get(a, 1, n, 1));
  }
  
  return 0;
}
