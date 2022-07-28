/*
 * Problem link : https://cses.fi/problemset/task/1726
 * Prereq: 
 * ---> Basic understanding of probabilities and expected value:
 *      https://cses.fi/book/book.pdf   (Chapter 24, first 3 sections)
 * 
 * It is a brute-force + simple dp solution that takes advantage of linearity of
 * expected values. The below code was adapted from the blog:
 * https://codeforces.com/blog/entry/82103
 * The following also might be helpful:
 * https://math.stackexchange.com/questions/4269867/cses-moving-robots-how-can-we-solve-this-expected-value-problem
 * 
 * Runtime O(8^4 * k);
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 8;
const int K = 1e2+1;

double dp[K][N][N];

int dx[] = {-1, 0, +1, 0};
int dy[] = {0, -1, 0, +1};

bool ok(int x, int y){
  return (0 <= x && x < N && 0 <= y && y < N);
}

int main(){
  int k; scanf("%d", &k);
  vector<vector<double>> ans(N, vector<double>(N));
  
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      ans[i][j] = 1.0;
  
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      for(int t=0; t<=k; t++){
        for(int u=0; u<N; u++){
          for(int v=0; v<N; v++){
            dp[t][u][v] = 0.0;
          }
        }
      }
      
      dp[0][i][j] = 1.0;
      for(int t=1; t<=k; t++){
        for(int u=0; u<N; u++){
          for(int v=0; v<N; v++){
            int dir = 0;
            for(int it=0; it<4; it++)
              if(ok(u+dx[it], v+dy[it]))
                dir++;
            
            for(int it=0; it<4; it++){
              int x = u + dx[it];
              int y = v + dy[it];
              if(ok(x, y))
                dp[t][x][y] += dp[t-1][u][v] / dir;
            }
          }
        }
      }
      
      for(int u=0; u<N; u++)
        for(int v=0; v<N; v++)
          ans[u][v] *= (1 - dp[k][u][v]);
    }
  }
  
  double tot = 0.0;
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      tot += ans[i][j];
  printf("%.6lf\n", tot);
  
  return 0;
}
