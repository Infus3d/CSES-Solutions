/*
 * Problem link : https://cses.fi/problemset/task/1625/
 * 
 * This problem tests how well you can optimize your code. To output the paths
 * we can go by the brute-force recursive way where we just keep track of cells
 * visited so far and go to the next available cell. When we leave a cell, we
 * unmark it so that other paths can continue their way through this cell. Whenever
 * we reach a the bottom-left cell after visiting all cells in the grid, we increase
 * the answer by 1.
 * The above brute-force has a bit of a runtime as it is not optimized in any way.
 * One smart optimization that significantly reduces the runtime is reaching a dead-end
 * with 2 available cells to on the sides. This optimization (and many others) are
 * visually described in the book: https://cses.fi/book/book.pdf  (Chapter 5, Pruning the Search).
 * 
 * The following tutorial adds another optimization should your program run slower:
 * https://usaco.guide/problems/cses-1625-grid-paths/solution
 * This video tutorial explains another optimization if you program still does not fit into time limit:
 * https://www.youtube.com/watch?v=wWUWA70drAY
 * 
 * Runtime - unknown. We can estimate it to be around O(2^48) initially but depending on your optimization
 * and searching skills, the complexity varies.
 * */
#include "bits/stdc++.h"

using namespace std;

vector<int> v(4);
int n, a[49], ans, vis[9][9];
char s[49];
char t[] = {'U', 'L', 'D', 'R'};

int dx[] = {-1, 0, +1, 0};
int dy[] = {0, -1, 0, +1};

void search(int x, int y, int step){
  if(x == n && y == 1){
    if(step == 48)
      ans++;
    return;
  }
  for(int i=0; i<4; i++){
    int newx = x + dx[i];
    int newy = y + dy[i];
    v[i] = !vis[newx][newy];
  }
  if(v[0] == v[2] && v[1] == v[3] && v[0] != v[1])
    return;
  
  vis[x][y] = 1;
  if(a[step] < 4){
    int newx = x + dx[a[step]];
    int newy = y + dy[a[step]];
    if(!vis[newx][newy])
      search(newx, newy, step+1);
  }
  else{
    for(int i=0; i<4; i++){
      int newx = x + dx[i];
      int newy = y + dy[i];
      if(!vis[newx][newy])
        search(newx, newy, step+1);
    }
  }
  vis[x][y] = 0;
}

int main(){
  n = 7;
  scanf("%s", s);
  for(int i=0; i<48; i++){
    a[i] = 4;
    for(int j=0; j<4; j++)
      if(s[i] == t[j])
        a[i] = j;
  }
  
  for(int i=0; i<=8; i++){
    vis[0][i] = vis[8][i] = 1;
    vis[i][0] = vis[i][8] = 1;
  }
  
  search(1, 1, 0);
  printf("%d\n", ans);
  
  return 0;
}
