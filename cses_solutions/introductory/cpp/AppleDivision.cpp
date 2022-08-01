/*
 * Problem link : https://cses.fi/problemset/task/1623
 * 
 * This problem requires you to know how to generate subsets over the given set.
 * Note that the n in the problem is very small, it is 20 so we can go over all
 * 2^n subsets of n apples and give that subset to person 1 and give the rest to
 * person 2 and simply subtract their sum for each subset.
 * To learn how to generate subset please refer to the book:
 * https://cses.fi/book/book.pdf  (Chapter 5, Generating Subsets - Method 2).
 * 
 * Also nice video editorial of this problem: https://www.youtube.com/watch?v=raGn3saVfa8
 * 
 * Runtime O(2^n * n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  vector<int> a(n); //the array for apples
  for(int i=0; i<n; i++)
    scanf("%d", &a[i]);
  
  long long ans = LLONG_MAX; //set to infinity
  for(int subset=0; subset<(1<<n); subset++){
    long long personA = 0, personB = 0;
    for(int i=0; i<n; i++){
      if((1<<i) & subset)
        personA += a[i];
      else
        personB += a[i];
    }
    ans = min(ans, abs(personA - personB)); //abs(a) = |a|
  }
  printf("%lld\n", ans);
  
  return 0;
}
