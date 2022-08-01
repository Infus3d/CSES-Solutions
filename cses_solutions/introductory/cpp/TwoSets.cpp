/*
 * Problem link : https://cses.fi/problemset/task/1092/
 * 
 * The sum of first n integers is n*(n+1)/2 so lets mark this quantity as 'Sum'.
 * Now we need to make sure that Sum % 2 is 0 if we were to split it into 2 equal
 * sum sets. If Sum % 2 is 1, then there is no solution.
 * Half of Sum - 'halfSum' - is the sum of one of the sets. Let's greedily add numbers
 * from n to 1 into this set and subtract what we add from halfSum. We need to stop
 * when halfSum reaches 0. So if current i (starting from n, till 1) is smaller than
 * or equal to halfSum, then we can afford to add it into the set and we subtract halfum -= i.
 * You can probably see that we decrease halfSum everytime we add a new element into the set
 * so it will eventually be equal to 0 because the sum of all elements 1 to n are equal to
 * Sum which is twice as big as (initial) halfSum. In fact by adding numbers 1 through n we can
 * construct any sum between 1 and n*(n+1)/2 = Sum.
 * After we know what elements belong to set1 we can see that the remaining elements belong
 * to set2.
 * Video tutorial: https://www.youtube.com/watch?v=bTMyqDH6cUA
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  long long sum = (long long)n * (n+1) / 2; //sum of 1+2+3+...+n
  if(sum % 2 != 0)
    puts("NO");
  else{
    long long halfsum = sum/2; //sum of set1 (and set2)
    vector<int> set1, set2;
    for(int i=n; i>=1; i--){
      if(halfsum >= i){ //if we can 'afford' to take i into set1
        set1.push_back(i);
        halfsum -= i;
      }
      else
        set2.push_back(i);
    }
    
    puts("YES");
    //output first set
    printf("%d\n", (int)set1.size());
    for(int i : set1)
      printf("%d ", i);
    puts("");
    //output second set
    printf("%d\n", (int)set2.size());
    for(int i : set2)
      printf("%d ", i);
    puts("");
  }
  return 0;
}
