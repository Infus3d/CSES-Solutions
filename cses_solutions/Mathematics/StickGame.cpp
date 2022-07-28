/*
 * Problem link : https://cses.fi/problemset/task/1729/
 * Prereq:
 * -----> Basic understanding of Game theory:
 *        https://cses.fi/book/book.pdf   (Chapter 25, Game States)
 * 
 * Like described in the book above, we can start with noting that the state of 0 sticks
 * is a losing state. Following game theory, any state that can lead to a losing state 
 * is a winning state and any state that leads to only winning states is a losing state.
 * Thus, with the base case 0, we can climb up the states from 1 to n and in each state
 * see if removing any of the allowed number of sticks from current pile i leads to a losing
 * state. If it is then current state is 'W', if not then it is 'L'.
 * 
 * Runtime O(n*k)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> p(k);
  for(int i=0; i<k; i++)
    scanf("%d", &p[i]);
  
  vector<int> states(n+1);
  for(int i=1; i<=n; i++){
    int curstate = 0;
    for(int j : p)
      if(i-j >= 0 && states[i-j] == 0){
        curstate = 1;
        break;
      }
    
    printf("%c", curstate ? 'W' : 'L');
    states[i] = curstate;
  }
  
  return 0;
}
