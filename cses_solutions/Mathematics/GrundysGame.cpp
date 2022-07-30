/*
 * Problem link : https://cses.fi/problemset/task/2207
 * Prereq:
 * ----> Solid understanding of Sprague-Grundy theorem and Nim game:
 *       https://cses.fi/book/book.pdf   (All of Chapter 25)
 * 
 * This is a well-known game and the solution of it is beautifully explained in the book.
 * However the book does not explain why the Grundy Number of all sizes beyond a certain
 * value (2000 in the code below) is always positive and I haven't found a proof for it
 * yet.
 * But there is this nicely written master's thesis explaining the sprague-grundy
 * theorem in great detail if you are beyond simply-interested in game theory:
 * https://www.universiteitleiden.nl/binaries/content/assets/science/mi/scripties/masterschlebusch.pdf
 * 
 * Runtime O(k^2 * log(k) + t) where k = 2000 in this code
 * */
#include "bits/stdc++.h"

using namespace std;

int mex(vector<int> &v){
  int p = 0;
  sort(v.begin(), v.end());
  for(int i : v){
    if(i == p) 
      p++;
    else if(p < i)
      break;
  }
  return p;
}

int main(){
  int t;
  scanf("%d", &t);
  
  vector<int> dp(2000, 0);
  for(int i=3; i<2000; i++){
    vector<int> v;
    for(int j=1; j<(i-j); j++)
      v.push_back(dp[j] ^ dp[i-j]);
    
    dp[i] = mex(v);
  }
  
  while(t--){
    int n;
    scanf("%d", &n);
    if(n >= 2000 || dp[n] > 0)
      puts("first");
    else
      puts("second");
  }
  
  return 0;
}
