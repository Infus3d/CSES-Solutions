/*
 * Problem link : https://cses.fi/problemset/task/1662
 * 
 * First, for the purpose of this problem let's make every number
 * modulus n. Also let's turn negative numbers into positive by just
 * adding n, as this will not change its 'modulo-n' value.
 * 
 * Now we have an array a[] with 0 <= a[i] < n and we need to find a
 * range with a[l...r] = n*k for some non-negative integer k. This is 
 * equivalent to maintaining prefix sums and checking for 
 * (pref[r] - pref[l-1]) = n*k. We can then manipulate the equation as:
 * 
 * (pref[r] - pref[l-1]) = n*k                   (for some non-negative integer k)
 * (pref[r] - pref[l-1]) % n = 0                 (taking %n of both sides)
 * ((pref[r] % n) - (pref[l-1] % n)) % n = 0
 * (pref[r] % n) - (pref[l-1] % n) = 0           (we can eliminate outer % n because we're looking for 0 anyways)
 * pref[r] % n = pref[l-1] % n
 * 
 * The last equation basically tells us that for every r (0 <= r < n) when iterating
 * over all prefix sums, we just need to count the number of l (0 <= l < r) with the same
 * prefix moludo n.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; 
  scanf("%d", &n);
  
  vector<int> a(n);
  for(int i=0; i<n; i++){
    scanf("%d", &a[i]);
    a[i] = ((a[i] % n) + n) % n;
    if(i > 0)
      a[i] = (a[i] + a[i-1]) % n;
  }
  
  long long ans = 0;
  vector<int> seen(n);
  
  seen[0] = 1;
  for(int i=0; i<n; i++){
    ans += seen[a[i]];
    seen[a[i]]++;
  }
  printf("%lld\n", ans);
  
  return 0;
}
