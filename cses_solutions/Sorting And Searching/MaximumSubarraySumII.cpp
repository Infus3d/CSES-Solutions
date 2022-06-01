/*
 * Problem link : https://cses.fi/problemset/task/1644
 * 
 * Improving upon the 1st version of the problem.
 * This time, we have a specific range [a, b] that the size of subarray x[l, r]
 * can be: a <= (r-l+1) <= b. Let's take the 1st half (a <= (r-l+1)) and move things
 * around to get (l <= r-a+1). This tells that the l values for every r can must be
 * smaller than r-a+1. Let's take the 2nd half and do the same thing to get
 * (r-b+1 <= l) which in turn tells us to not consider any l values < r-b+1 for our
 * current r.
 * 
 * When calculating the answer (pref[r] - pref[l-1]) for every r, we need to include
 * l-prefixes with the above criteria. This is easy as all we need to do is insert
 * pref[r-a] and delete pref[i-b-1] (since b is inclusive) from the set. And just like
 * before, we take the minimum available/allowed prefix sum as our (pref[l-1]) to get
 * the maximum sum. Since there can be duplicate prefix sums, we need to maintain a multiset.
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  
  vector<long long> x(n+1);
  for(int i=1; i<=n; i++){
    scanf("%lld", &x[i]);
    x[i] += x[i-1];
  }
  
  long long ans = -1e18;
  multiset<long long> prefixes;
  for(int i=1; i<=n; i++){
    if(i-a >= 0)                //we insert the minimum range left-end of prefixsum
      prefixes.insert(x[i-a]);
    if(i-b-1 >= 0)              //need to erase anything further than the allowed maximum b
      prefixes.erase(prefixes.find(x[i-b-1]));
    
    if(!prefixes.empty())
      ans = max(ans, x[i] - *prefixes.begin());
  }
  printf("%lld\n", ans);
  
  return 0;
}
