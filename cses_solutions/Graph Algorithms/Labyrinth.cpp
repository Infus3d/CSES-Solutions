/*
 * Problem link : https://cses.fi/problemset/task/1193
 * 
 * Prereq:
 * BFS : https://cses.fi/book/book.pdf (page 119)
 * 
 * This problem is easy to solve but heavy to implement. We are guaranteed
 * that there is exactly 1 starting and 1 ending point in the labyrinth so
 * we just need to initiate the shortest path from A to any other cell it
 * can reach. Finally we just output the cost of reaching cell B. 
 * 
 * When calculating the shortest path and transitioning from cell u to cell v
 * we store not only the cost but also where it came from in the cell v (from[v] = u).
 * Though it is implemented slightly differently below, the idea still stands. We can
 * then use this from[] values to trace back the actual path and print it out.
 * 
 * Finding shortest path normally requires Dijkstra's Algorithm but in this problem
 * we can opt-in to finding it with BFS. We can use BFS because the cost of transition
 * from one cell to the other is constant over the entire map; if the costs varied among
 * the cells, we would need to use Dijkstra's. It is worth some time trying to see/understand
 * why this is the case.
 * 
 * I tried to employ the best implementation methods for this type of 'maze' problems
 * below so please take your time to fully understand it as it will be useful in many more problems
 * to come.
 * 
 * Runtime O(n*m) - linear time [in terms of total # of cells] because of BFS.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e3;

int n, m;
int cost[N][N], from[N][N];
char s[N][N];

int dx[] = {-1, 0, +1, 0};
int dy[] = {0, -1, 0, +1};
char dir[] = {'U', 'L', 'D', 'R'};

bool isOk(int x, int y){
  return (0 <= x && x < n && 0 <= y && y < m && s[x][y] != '#');
}

int main(){
  scanf("%d%d", &n, &m);
  
  int ax, ay, bx, by;
  for(int i=0; i<n; i++){
    scanf("%s", s[i]);
    for(int j=0; j<m; j++){
      if(s[i][j] == 'A')
        ax = i, ay = j;
      if(s[i][j] == 'B')
        bx = i, by = j;
    }
  }
  
  queue<pair<int, int>> Q;
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++)
      cost[i][j] = INT_MAX;
  
  cost[ax][ay] = 0; Q.push({ax, ay});
  while(!Q.empty()){
    auto [x, y] = Q.front();
    Q.pop();
    
    for(int i=0; i<4; i++){ //4 directions
      int newX = x + dx[i];
      int newY = y + dy[i];
      
      if(isOk(newX, newY) && cost[newX][newY] > cost[x][y] + 1){
        cost[newX][newY] = cost[x][y] + 1;
        from[newX][newY] = i;
        Q.push({newX, newY});
      }
    }
  }
  
  if(cost[bx][by] == INT_MAX)
    printf("NO\n");
  else{
    printf("YES\n%d\n", cost[bx][by]);
    vector<char> trace;
    
    while(bx != ax || by != ay){
      int temp = from[bx][by];
      trace.push_back(dir[temp]);
      
      bx = bx - dx[temp];
      by = by - dy[temp];
    }
    
    reverse(trace.begin(), trace.end());
    for(char i : trace)
      printf("%c", i);
    puts("");
  }
  
  return 0;
}
