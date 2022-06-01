/*
 * Problem link : https://cses.fi/problemset/task/1192
 * 
 * This is a very basic dfs (or bfs) problem where we need to maintain the visited
 * states, or cells in this specific problem.
 * For every cell in the grid, we check if we can start traversing around from that
 * cell that is, if it is not visited and it's not '#'. If yes, we increase the answer
 * as just found a new 'room' to traverse and initiate a dfs
 * from that position and reach every cell we can while also marking the cells 'visited'
 * to guarantee linear time.
 * 
 * Runtime O(n*m) as we visit each cell at most once and don't come to the visited cell ever again.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e3;

int n, m, vis[N][N];
char s[N][N];

int dx[] = {-1, 0, +1, 0};
int dy[] = {0, -1, 0, +1};

bool isOk(int x, int y){
  return (0 <= x && x < n && 0 <= y && y < m && s[x][y] == '.' && !vis[x][y]);
}

void dfs(int x, int y){
  vis[x][y] = 1;
  
  for(int i=0; i<4; i++){
    int newX = x + dx[i];
    int newY = y + dy[i];
    
    if(isOk(newX, newY))
      dfs(newX, newY);
  }
}

int main(){
  scanf("%d%d", &n, &m);
  for(int i=0; i<n; i++)
    scanf("%s", s[i]);
  
  int ans = 0;
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++)
      if(isOk(i, j)){
        dfs(i, j);
        ans++;
      }
  
  printf("%d\n", ans);
  
  return 0;
}
