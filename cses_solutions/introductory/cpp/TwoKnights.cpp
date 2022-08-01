/*
 * Problem link : https://cses.fi/problemset/task/1072
 * 
 * This is a pure observational problem where we can come up with a mathematical formula
 * of the answer in terms of given n - the size of n x n chessboard.
 * Since it is a lot easier to count the number of ways to place two knights so that they
 * attack each other, we can take this number and subtract it from total number of placements
 * to get the answer.
 * Here are the 8 moves a knight can do (shown on 7x7 board):
 * *******
 * **1*2**
 * *3***4*
 * ***X***
 * *5***6*
 * **7*8**
 * *******
 * 
 * X is where the knight is and the numbers are its possible moves.
 * From this we can see that if we put knight1 on X we have 8 possible places to put knight2 on.
 * However, pay attention to the symmetries and avoid double counting:
 * Let's say that we put knight1 on X and knight2 on move 4 (the cell where there is a number 4).
 * Then knight1 'sees' knight2 in its 4'th move, however from knight2's perspective, knight1 is
 * also on one of its possible moves - move 5. So instead of counting all 8 possible moves of every
 * cell, we count only the upper 4 as remaining lower 4 moves will be counted from their respective
 * perspecives as if they were 'upper 4 moves'.
 * Now, for move 1 to exist for a cell X, that cell must have at least 2 rows above it and at least 1
 * column to the left. So if the size of the board is n, then there are (n-2)*(n-1) possible cells that
 * have move 1. For move 2 to exist, there must be at least 2 rows above and at least 1 column to the right
 * of cell X, so again (n-2)*(n-1) possible X cells. The same goes for moves 3 and 4, so we have in total
 * (n-2)*(n-1)*4 possible placements of cell X and its moves, meaning these are the number of 'bad' placements
 * of knight1 and knight2 where they attack each other. We can just subtract this number from the total
 * placements to get the answer to the problem.
 * Since there are n*n cells on the board and we are trying to place 2 knights, the total number of placements
 * will be ((n^2) choose 2) = (n^2) * (n^2-1) / 2.
 * 
 * Runtime O(n) 
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  for(int i=1; i<=n; i++){
    long long cells = (long long)(i * i); ////we can cast the product to a long long integer
    long long total = (long long)(cells * (cells-1)) / 2;
    long long badmoves = 4LL * (i-2) * (i-1); //or we can just multiply it with a long long integer (4LL) at the start of all operations
    printf("%lld\n", total - badmoves);
  }
  
  return 0;
}
