/*
 * Problem link : https://cses.fi/problemset/task/2428
 * 
 * One of the cleanest ways to solve this problem is by using 2-pointers.
 * We start with l = r = 0 and keep track of curDistinct - the number of 
 * distinct values in our range [l, r]. When increasing r will cause curDistinct
 * go above k, we stop. This r will then be the number of right-ends for our
 * current l, so we simply do ans += r. Whenever we can't increase r, we resort
 * to increasing l and popping numbers from out range [l, r] and updating curDistinct
 * accordingly.
 * 
 * To make it more clear, at any time we will have 2 choices to make with [l, r]:
 * ------> Increase r until our range [l, r] contains more than k distinct numbers:
 *         while(curDistinct <= k). Whenever we increase r, we need to update curDistinct.
 *         We can do it by keeping count of the numbers in our range [l, r]. If count[a[r]]
 *         is zero, then we increase curDistinct. If not, we don't do anything wth curDistinct.
 *         In either case, we increase the count of a[r] : count[a[r]]++;
 * 
 * ------> Increase l when we can't increase r anymore. This helps us by popping the elements
 *         from our range [l, r] that are preventing r from further increasing. When increasing l
 *         we need to update curDistinct accordingly. If count[a[r]] == 1, then popping that element
 *         will decrease curDistinct by 1. If it's bigger than 1, then we don't update curDistinct.
 *         In either case, we decrease the count of a[l] : count[a[l]]--;
 * 
 * It's worth taking some time understanding that every a[l] will be popped at some time during the process,
 * and the r value at that time will be the largest r that contains at most k distinct elements for current l.
 * For answer, we can see that every interval [l, i] with l <= i <= r will be a valid interval (that contains
 * at most k distinct elements) so we simply do ans += r-l+1; (+1 depends on how you handle r, i.e. inclusive or not).
 * 
 * Runtime O(n*log(n)) because numbers are too large to count them with arrays, so we use maps with logarithmic time.
 * */

#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, k;
  scanf("%d%d", &n, &k);
  
  vector<int> a(n);
  for(int i=0; i<n; i++)
    scanf("%d", &a[i]);
  
  int r = 0, curDistinct = 0;
  long long ans = 0;
  map<int, int> cnt;
  
  for(int l=0; l<n; l++){
    while(r < n && curDistinct <= k){
      if(cnt[a[r]] == 0 && curDistinct == k)
        break;
      
      if(cnt[a[r]] == 0)
        curDistinct++;
      
      cnt[a[r]]++;
      r++;
    }
    
    ans += r-l;
    cnt[a[l]]--;
    
    if(cnt[a[l]] == 0)
      curDistinct--;
  }
  printf("%lld\n", ans);
  
  return 0;
}
