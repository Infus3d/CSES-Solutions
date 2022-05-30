/*
 * Problem link : https://cses.fi/problemset/task/1661
 * 
 * Since this version of the problem contains negative numbers, our
 * previous 2-pointer approach will not work because incrementing r
 * can mean both increase and decrease in the sum [of the range].
 * 
 * We can instead use the pref-sum technique. Let pref[i] contain
 * the sum of all a[j] with 0 <= j <= i. Then the sum of a[l...r]
 * will be (pref[r] - pref[l-1]). We need this sum to be equal to x.
 * We turn (pref[r] - pref[l-1]) = x into pref[r] - x = pref[l-1].
 * This tells us that for every r, the number of intervals [l, r]
 * with a[l...r] == x is the count of prefix sums to the left of r
 * that equal to (pref[r] - x).
 * We can store the count of prefix sums to the left of r in hashmap
 * while iterating over r (0 <= r < n). Everytime then we just need
 * to add that count onto the answer: ans += hashmap[pref[r] - x].
 * 
 * Since c++ stl map uses rb-tree as its data structure, the runtime
 * of the below solution is O(n*log(n)).
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, x;
  scanf("%d%d", &n, &x);
  
  vector<int> a(n);
  vector<long long> pref(n);
  for(int i=0; i<n; i++){
    scanf("%d", &a[i]);
    pref[i] = a[i];
    if(i > 0)
      pref[i] += pref[i-1];
  }
  
  map<long long, int> seen;
  seen[0]++;
  
  long long ans = 0;
  for(int i=0; i<n; i++){
    long long theSum = pref[i] - x;
    ans += seen[theSum];
    seen[pref[i]]++;
  }
  printf("%lld\n", ans);
  
  return 0;
}
