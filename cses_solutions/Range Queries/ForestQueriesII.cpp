/*
 * Problem link : https://cses.fi/problemset/task/1739
 * 
 * Prereq: 2D Binary Indexed Tree or Segment Tree
 * ------> https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees
 *         https://cp-algorithms.com/data_structures/fenwick.html#finding-sum-in-two-dimensional-array
 * 
 * We can extend the idea of range queries into 2 dimensions. The code below uses the 2D
 * Binary Indexed Tree where the time of each upd and sum query is O(log(n)^2) which is still
 * pretty fast.
 * 
 * Just like how with 1D BIT we can get prefix-sum of the range [1, i] in a dynamic array,
 * with 2D BIT we can get the prefix-sum of the rectange [1, 1, i, j] efficiently. To get the
 * sum of the specific rectange [x1, y1, x2, y2] like in this problem, we use the 2D partial
 * sum logic that was introduced in Forest Queries problem version I:
 * sum[x1, y1, x2, y2] = sum[1, 1, x2, y2] - sum[1, 1, x2, y1-1] - sum[1, 1, x1-1, y2] + sum[1, 1, x1-1, y1-1].
 * 
 * Runtime O((n^2 + q) * log(n)^2)
 * */
#include "bits/stdc++.h"

#define y1 literally_anything_you_want

using namespace std;

const int N = 1e3+1;

int n, q, a[N][N], fen[N][N];
char s[N];

void upd(int x, int y, int val){ //just adding val to [x, y] in 2D BIT
  while(x <= n){
    int y1 = y;
    while(y1 <= n){
      fen[x][y1] += val;
      y1 += (y1 & -y1);
    }
    x += (x & -x);
  }
}

int sum(int x, int y){ //getting the sum of the rect [1, 1, x, y]
  int ret = 0;
  while(x > 0){
    int y1 = y;
    while(y1 > 0){
      ret += fen[x][y1];
      y1 -= (y1 & -y1);
    }
    x -= (x & -x);
  }
  return ret;
}

int sumOfRect(int x1, int y1, int x2, int y2){
  int a = sum(x2, y2);
  int b = sum(x2, y1-1);
  int c = sum(x1-1, y2);
  int d = sum(x1-1, y1-1);
  
  return a - b - c + d; //2-dimensional partial/prefix sum
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%s", s+1);
    for(int j=1; j<=n; j++)
      if(s[j] == '*'){
        a[i][j] = 1;
        upd(i, j, 1);
      }
  }
  
  while(q--){
    int t, x1, y1, x2, y2;
    scanf("%d%d%d", &t, &x1, &y1);
    if(t == 1){
      upd(x1, y1, -a[x1][y1]+(a[x1][y1]^1));
      a[x1][y1] ^= 1; //xor simply switches between 0 and 1
    }
    else{
      scanf("%d%d", &x2, &y2);
      printf("%d\n", sumOfRect(x1, y1, x2, y2));
    }
  }
  
  return 0;
}
