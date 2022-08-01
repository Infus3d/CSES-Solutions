/*
 * Problem link : https://cses.fi/problemset/task/1624
 * 
 * To place 8 Queens on 8x8 chess board we have to put each Queen in its own
 * row and column first because otherwise Queens can clearly attack each other
 * if more than one is placed on the same row or column.
 * Now, Queens also attack diagonally both to the right and to the left. Since
 * it is just an 8x8 board, we can afford to brute-force the placements of the
 * queens on each row and mark the 'threatened' columns and diagonals. We can
 * maintain a recursive function that calls the next row after placing the current
 * row's Queen. Let's say that we are at row i and we want to try placing a Queen
 * in this row at column j. We can only do so if cell[i][j] is not '*' and it is
 * not a threatened column or a diagonal. Let's say that all these conditions were
 * satisfied and we could place the Queen at cell[i][j] then we need to mark column[j]
 * as 'threatened' also both leftDiagonal[i-j+7] and rightDiagonal[i+j] as 'threatened'.
 * Then we can call the recursive function for the next row until we are finally beyond
 * the last row, at which point we will have found a valid placement of 8 Queens so
 * we increase our answer by 1.
 * When backtracking from a recursive call, we need to 'unmark' the column and diagonals
 * so that we can try at a different column j on this row i. Please look at the code below
 * for more detail.
 * Note that for each cell [i, j] we can identify its left and right diagonals by simply
 * i-j+7 and i+j respectively. There are exactly 15 left and 15 right diagonals in
 * an 8x8 board.
 * 
 * Video tutorial (although his code is iterative while ours is recursive):
 * https://www.youtube.com/watch?v=U-zC2blCz5Y
 * 
 * Runtime O(2^n * n) where n = 8 in this problem
 * */
#include "bits/stdc++.h"

using namespace std;

int ans;
char s[9][9];
bool leftDiag[15], rightDiag[15], columns[8];

void rec(int row){
  if(row == 8){ //if we are past the last row, then we have found 1 way to place the queens
    ans++;
    return;
  }
  
  for(int col=0; col<8; col++)
    if(!columns[col] && !leftDiag[row-col+7] && !rightDiag[row+col] && s[row][col] == '.'){
      columns[col] = leftDiag[row-col+7] = rightDiag[row+col] = 1; //mark this column, left and right diagonals of this cell as 'threatened'
      rec(row+1); //go to the next row and get the number of possible arrangements with current 'markings'
      columns[col] = leftDiag[row-col+7] = rightDiag[row+col] = 0; //unmark what's marked before
    }
}

int main(){
  for(int i=0; i<8; i++)
    scanf("%s", s[i]);
  
  rec(0); //start from the first row
  printf("%d\n", ans);
  
  return 0;
}
