/*
 * Problem link : https://cses.fi/problemset/task/1098
 * Prereq:
 * -----> Basic understanding of Game theory and Nim game:
 *        https://cses.fi/book/book.pdf   (Chapter 25, first 2 sections)
 * 
 * This problem is a variation of the original Nim problem with only varying k
 * where k is the maximum number of sticks you can remove from any heap at a time
 * (k = 3 in this problem).
 * The game can be optimally played just like the original Nim game but with all 
 * pile sizes reduced mod (k+1) - which is 4 for this task. So when we can just get
 * the XOR of all pile sizes mod (k+1) and see if the value is positive.
 * The following is not an official proof but will help you see why this works:
 * ----> Imagine that we have 4 piles with {3, 3, 3, 3} stones. Since every pile is smaller
 *       than 4, we can proceed with regular Nim game strategy. The theorem tells us that the
 *       first player loses this game because XOR of four 3's is obviously 0. This is true
 *       no matter how the game is played as long as the second player plays it optimally.
 *       For, ex. imagine the following gameplay: player 1 removes 3 from a pile leaving {3, 3, 3}.
 *       Then player 2 also removes a pile of 3 because it will make xor of remaining {3, 3} equal 0.
 *       Then whatever move player 1 does will result in a loss because player 2 can always make a move
 *       that will make the xor of the remaining piles 0.
 * 
 * ----> The above is true (obviously, because it is just a regular Nim game) for a winning initial game
 *       state. Let's say that we have 3 piles of {3, 3, 3} and you can see that this is a winning state.
 * 
 * ----> Now imagine that we have 4 piles of {7, 7, 7, 7} which you can already see that results in {3, 3, 3, 3}
 *       when taken mod 4. So according to our assumption, {7, 7, 7, 7} is a losing game state. And this is true!
 *       Because no matter how player 1 removes the stones from these piles, player 2 can always 'adjust' that
 *       updated pile to match its state in its mode 4 setting. For example, if player 1 removes 1 stone from the 
 *       1st pile making it {6, 7, 7, 7} then player 2 can remove 3 stones from the same pile to turn it to {3, 7, 7, 7}.
 *       So when player 1 removes x (x < 4) stones then player 2 can remove the 'cancelling' (4-x) stones so that the 
 *       pile will eventually reach its mod 4 state which is 3.
 * 
 * ----> The above is also true for initial winning game state, let's say {7, 7, 7}. To keep its winning state till
 *       the end, player 1 can on the first move choose a move that will turn the piles into a losing state in their
 *       mode 4 setting and then the following moves it can just 'round' the piles as to cancel player 2's move.
 *       For {7, 7, 7} its mod 4 setting is {3, 3, 3} and player 1 can just remove 3 piles from it to turn it to a losing
 *       state. So player 1 can just remove 3 from any pile making it {4, 7, 7} and from then on try to keep the game
 *       in losing state for player 2 by removing (4-x) stones when player 2 removes x stones.
 * 
 * For more info: https://en.wikipedia.org/wiki/Nim#The_subtraction_game
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    int n;
    scanf("%d", &n);
    
    int exort = 0;
    for(int i=0; i<n; i++){
      int a; scanf("%d", &a);
      exort ^= a % 4;
    }
    printf("%s\n", exort ? "first" : "second");
  }
  
  return 0;
}
