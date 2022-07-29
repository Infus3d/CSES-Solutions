/*
 * Problem link : https://cses.fi/problemset/task/2208/
 * Prereq:
 * ----> Solid understanding of Sprague-Grundy theorem and Nim game:
 *       https://cses.fi/book/book.pdf   (All of Chapter 25)
 * 
 * The game is winnable for 1st player if and only if there is at least 1 odd numbered pile
 * of coins. If all piles have even number of coins then the 2nd player wins.
 * 
 * The following comment explains why this is the case:
 * https://codeforces.com/blog/entry/82103?#comment-824949
 * 
 * In case the page is unavailable here is the copy-pasted comment:
 * """
 * For Another Game, the first player wins iff there is at least one heap with an odd number of coins.
 * If all heaps have an even number of coins, the second player can win, by taking coins from the same set
 * of piles as the first player on the previous turn. This ensures that all heaps have an even number of piles
 * at the end of the second player's turn, so the strategy can continue.
 * 
 * If at least one heap has an odd number of coins, the first player can win by taking one coin from each pile
 * with an odd number of coins, reducing the game to the first scenario.
 * 
 * Credits: https://codeforces.com/profile/Thienu
 * """
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
    bool odd = false;
    for(int i=0; i<n; i++){
      int a; scanf("%d", &a);
      if(a % 2 == 1)
        odd = true;
    }
    printf("%s\n", odd ? "first" : "second");
  }
  
  return 0;
}
