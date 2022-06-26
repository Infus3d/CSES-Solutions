/*
 * Problem link : https://cses.fi/problemset/task/1194
 * Prereq : BFS -> https://cses.fi/book/book.pdf (page 119)
 * 
 * We have several monsters in a maze and one person that wants to escape
 * the maze by reaching any of the border cells (border cell needs to be empty '.').
 * 
 * We can take all monsters and the person and run BFS to determine who reaches
 * any of the cells first. This is also sometimes referred to as multiple-source
 * shortest path where there are multiple starting nodes/cells and the shortest
 * path algorithm (either BFS or Dijkstra most of the time) is run to simulate 
 * the 'spreading' of those nodes/cells.
 * 
 * The only thing that needs to be added into the queue along with positions of the
 * monsters/person is that their type: we need to know who reached the cell first,
 * monster or the person. Because if person reaches a cell, we need to mark that cell
 * as 'reachable' by the person. If both the person and a monster reach the cell at the
 * same time, then the monster takes priority (as described in the problem statement).
 * For this reason, we need to make sure that we push all starting monsters into the
 * queue before we push the person.
 * 
 * When a cell is marked 'reachable' we just make sure to remember which cell it was reached
 * from (up, left, down or right) in order to be able to print the path at the end. To print
 * the answer, we find any border cell that is marked 'reachable' by the person and trace back
 * the path.
 * 
 * Runtime O(n*m) or in other words linear with regards to the total size of the input
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e3;

char s[N][N];
int n, m, times[N][N], from[N][N];

int dx[] = {-1, 0, +1, 0};
int dy[] = {0, -1, 0, +1};
char dir[] = {'U', 'L', 'D', 'R'};

bool ok(int x, int y){
  return (0 <= x && x < n && 0 <= y && y < m && s[x][y] != '#');
}

int main(){
  scanf("%d%d", &n, &m);
  
  queue<pair<pair<int, int>, int>> Q;
  for(int i=0; i<n; i++){
    scanf("%s", s[i]);
    for(int j=0; j<m; j++){
      times[i][j] = INT_MAX;
      from[i][j] = -1;
      
      if(s[i][j] == 'M'){
        Q.push({{i, j}, 0}); //0 to indicate that this is a monster
        times[i][j] = 0;
      }
    }
  }
  for(int i=0; i<n; i++)   //it is important that we push the person after all monsters are pushed to give monsters priority
    for(int j=0; j<m; j++)
      if(s[i][j] == 'A'){
        Q.push({{i, j}, 1}); //1 to indicate that this is a person
        times[i][j] = 0;
        from[i][j] = 0;
      }
  
  while(!Q.empty()){
    auto cur = Q.front();
    Q.pop();
    
    int x = cur.first.first, y = cur.first.second, t = cur.second;
    for(int i=0; i<4; i++){
      int newx = x + dx[i];
      int newy = y + dy[i];
      
      if(ok(newx, newy) && times[newx][newy] > times[x][y] + 1){
        times[newx][newy] = times[x][y] + 1;
        Q.push({{newx, newy}, t});
        
        if(t == 1) //if person
          from[newx][newy] = i;
      }
    }
  }
  
  int x = -1, y = -1;
  for(int i=0; i<n; i++){ //check the first and last columns (borders)
    if(from[i][0] != -1)
      x = i, y = 0;
    if(from[i][m-1] != -1)
      x = i, y = m-1;
  }
  for(int i=0; i<m; i++){ //check the first and last rows (borders)
    if(from[0][i] != -1)
      x = 0, y = i;
    if(from[n-1][i] != -1)
      x = n-1, y = i;
  }
  
  if(x == -1)
    printf("NO\n");
  else{
    vector<char> ans;
    while(times[x][y] > 0){ //while we are not at the initial position of the person
      int temp = from[x][y];
      ans.push_back(dir[temp]);
      
      x -= dx[temp];
      y -= dy[temp];
    }
    
    printf("YES\n%d\n", (int)ans.size());
    for(int i=ans.size()-1; i>=0; i--)
      printf("%c", ans[i]);
    puts("");
  }
  
  return 0;
}
