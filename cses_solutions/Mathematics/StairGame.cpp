/*
 * Problem link : https://cses.fi/problemset/task/1099
 * Prereq:
 * -----> Basic understanding of Game theory and Nim game:
 *        https://cses.fi/book/book.pdf   (Chapter 25, first 2 sections)
 * 
 * In this problem the first player wins the game if and only if the Nim-sum (or XOR) of the
 * numbers at the even indexed positions is positive. Otherwise, the second player wins.
 * 
 * The following comment explains why it works pretty elegantly:
 * https://codeforces.com/blog/entry/82103?#comment-824949
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
      if(i % 2 == 1)
        exort ^= a;
    }
    printf("%s\n", exort ? "first" : "second");
  }
  
  return 0;
}
