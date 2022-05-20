/*
 * Problem link : https://cses.fi/problemset/task/1640
 * 
 * This is a well known 'leetcode' problem where we need
 * to find 2 numbers in the array that sum up to x.
 * We could easily sort the given array maintain 2 pointers
 * l = 0 and r = n-1:
 * -----> if a[l] + a[r] > x then we definitely need to go lower
 *        so we do r--.
 * 
 * -----> if a[l] + a[r] < x then we definitely need to go higher
 *        so we do l++.
 * 
 * -----> if a[l] + a[r] == x then print the answer.
 * 
 * One thing though this problem requires you to print the indices
 * of the two numbers in the initial (unsorted) array. To do that we
 * could just 'attach' the initial indices to the array values (making
 * them pair) and sort them together.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, x; 
  scanf("%d%d", &n, &x);
  
  vector<pair<int, int>> a(n);
  for(int i=0; i<n; i++){
    scanf("%d", &a[i].first);
    a[i].second = i+1;
  }
  
  sort(a.begin(), a.end());
  
  int l = 0, r = n-1;
  while(l < r){
    if(a[l].first + a[r].first > x) r--;
    else if(a[l].first + a[r].first < x) l++;
    else{
      printf("%d %d\n", a[l].second, a[r].second);
      return 0;
    }
  }
  printf("IMPOSSIBLE\n");
  
  return 0;
}
