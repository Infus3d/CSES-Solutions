/*
 * Problem link : https://cses.fi/problemset/task/1689
 * 
 * The solution below uses the Warnsdorf's rule as a heuristic to optimize
 * the brute-force solution of the problem.
 * Please refer to this book to learn about it:
 * https://cses.fi/book/book.pdf   (Chapter 19, Knight's Tour)
 * 
 * Runtime idk as it varies.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 8;

const int dx[]={-2, -2, -1, -1,  1,  1,  2,  2};
const int dy[]={-1,  1, -2,  2, -2,  2, -1,  1};

int vis[N][N];

bool ok(int x, int y){
  return (0 <= x && x < 8 && 0 <= y && y < 8 && vis[x][y] == 0);
}

int moveCount(int x, int y){
  int cnt = 0;
  for(int i=0; i<8; i++)
    if(ok(x+dx[i], y+dy[i]))
      cnt++;
  return cnt;
}

int rec(int x, int y, int step){
  vis[x][y] = step;
  
  if(step == 8*8)
    return 1;
  
  vector<pair<int, int>> options;
  for(int i=0; i<8; i++){
    int newx = x + dx[i];
    int newy = y + dy[i];
    if(ok(newx, newy)){
      int cnt = moveCount(newx, newy);
      options.push_back({cnt, i});
    }
  }
  
  sort(options.begin(), options.end());
  for(auto i : options){
    int newx = x + dx[i.second];
    int newy = y + dy[i.second];
    
    if(rec(newx, newy, step+1) == 1)
      return 1;
  }
  
  vis[x][y] = 0;
  return 0;
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  
  rec(m-1, n-1, 1); //0-based
  
  for(int i=0; i<8; i++)
    for(int j=0; j<8; j++)
      printf("%d%c", vis[i][j], " \n"[j==7]);
  
  return 0;
}
