/*
 * Problem link : https://cses.fi/problemset/task/1652
 * 
 * One could use 2D segment trees to solve the problem but that would
 * be an overkill. We can extend our idea of prefix sums to 2-dimensions!
 * 
 * Let b[i][j] contain the sum of the elements in the rectange with upper-left
 * corner at (1, 1) and lower-right corner at (i, j).
 * 
 * When we want to calculate the sum in the rectangle [x1, y1, x2, y2] - the rectangle
 * that starts at (x1, y1) and ends at (x2, y2) - we can take b[x2][y2] and subtract
 * the unnecessary elements that are inside the rectangles strictly above and to the left
 * of our desired range [x1, y1, x2, y2]. These rectangles that we need to subtract are
 * b[x2][y1-1] and b[x1-1][y2]. 
 * So we do sum[x1, y1, x2, y2] = b[x2][y2] - b[x2][y1-1] - b[x1-1][y2]. 
 * However, when we do this we subtract the the rectange b[x1-1][y1-1] twice as it is present
 * in both b[x2][y1-1] and b[x1-1][y2]. So we just add it to the answer:
 * sum[x1, y1, x2, y2] = b[x2][y2] - b[x2][y1-1] - b[x1-1][y2] + b[x1-1][y1-1].
 * 
 * We can answer each query in O(1) if we have b[i][j] calculated for every (i, j).
 * Runtime O(n^2 + q)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e3+1;

int n, q, a[N][N];
char s[N];

//we need to define to be something else because it is a reserved keyword in C/C++
#define y1 anything_you_want 

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%s", s);
    for(int j=1; j<=n; j++){
      if(s[j-1] == '*')
        a[i][j] = 1;
      a[i][j] += a[i][j-1];
    }
    for(int j=1; j<=n; j++)
      a[i][j] += a[i-1][j];
  }
  
  while(q--){
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    int ans = a[x2][y2] - a[x2][y1-1] - a[x1-1][y2] + a[x1-1][y1-1];
    printf("%d\n", ans);
  }
    
  return 0;
}
