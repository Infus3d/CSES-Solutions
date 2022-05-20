/*
 * Problem link : https://cses.fi/problemset/task/1643
 * 
 * One of the easiest ways to solve this problem is with prefix sums.
 * As the name suggests, there are n + 1 prefix sums in an array of
 * length n where prefix[i] is the sum of all elements j up to i (j <= i).
 * For ex:
 * array :       1 1 -3 6 -1 7
 * prefix[0] : 0
 * prefix[1] :   1
 * prefix[2] :     2
 * prefix[3] :       -1
 * prefix[4] :          5
 * prefix[5] :             4
 * prefix[6] :               11
 * 
 * With our prefix table set up, we can get the sum of the range [l, r] by
 * prefix[r] - prefix[l-1]. It is recommended that you try some examples
 * and fully understand why this is the case.
 * 
 * if we have sum = prefix[r] - prefix[l-1] and we want to maximize sum
 * then for every r we want an l so that prefix[l-1] is minimum. We can
 * use either priority queue or stl set (balanced binary search tree) to
 * insert and get the minimum element of the elements up to r in O(logn) time.
 * In any case, we can have every j (j <= i) that we passed through pushed/inserted
 * in the set when considering prefix[i]. All we need to do is to get the smallest
 * among them (again either from prio-queue or set) so that we get the maximum possible
 * sum for prefix[i].
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; 
  scanf("%d", &n);
  
  long long ans = -1e18;
  vector<long long> a(n+1);
  set<long long> setik; //setik means 'small&|cute set' in russian
  
  //if we want to make the 1'st index inclusive, we need to add prefix sum at 0'th index, which is 0
  setik.insert(0);
  for(int i=1; i<=n; i++){
    scanf("%lld", &a[i]);
    
    a[i] += a[i-1]; //get the prefix sum of i
    //setik.begin() returns the iterator to the smallest(first) element of the set and * returns the value at that iterator
    ans = max(ans, a[i] - *setik.begin());
    
    setik.insert(a[i]); //insert the prefix sums
  }
  printf("%lld\n", ans);
  
  
  return 0;
}
