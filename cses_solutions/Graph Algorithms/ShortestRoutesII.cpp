/*
 * Problem link : https://cses.fi/problemset/task/1672
 * Prereq: 
 * Floyd-Warshall's Algorithm for finding shortest paths
 * https://cses.fi/book/book.pdf    (Page 129)
 * 
 * In this problem the constraints are quite low for the number of nodes and edges.
 * However we have to answer queries up to 1e5.
 * 
 * Looking at our options for calculating shortest paths from every-node to every single
 * other node in the graph, we can see that Floyd-Warshall's O(n^3) algorithm suits best
 * for our needs. Since n <= 500, we can afford a cubic time complexity to precalculate
 * shorest paths from every node to every other node.
 * Then for each query, we can answer it in O(1) by simply printing out the precalculated
 * dist[a][b] for any two nodes a and b.
 * 
 * Runtime O(n^3 + q) since answering each query is only O(1)
 * 
 * Note that we could also use Dijkstra's Algorithm to find the shorest paths but it will be
 * slightly inefficient as its runtime is O(n + m*log(m)). We need to run Dijkstra's for every
 * node in the graph giving us a total runtime of O(n^2 + n*m*log(m)). This seems like it's 
 * better than O(n^3) but not quite: as shown in the problem set, m can go upto n^2.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 5e2;

int n, m, q;
long long dist[N][N];

int main(){
  scanf("%d%d%d", &n, &m, &q);
  
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      if(i != j)
        dist[i][j] = (long long) 1e13; //setting all distances to infinity, except for self-path [from i, to i]
  
  for(int i=0; i<m; i++){
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    a--, b--;
    dist[a][b] = min((int)dist[a][b], c); //can be multiple-edges between two nodes
    dist[b][a] = min((int)dist[b][a], c); //roads are bi-directional
  }
  
  for(int k=0; k<n; k++)
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    a--, b--;
    if(dist[a][b] == (long long) 1e13)
      printf("-1\n");
    else
      printf("%lld\n", dist[a][b]);
  }
  
  return 0;
}
