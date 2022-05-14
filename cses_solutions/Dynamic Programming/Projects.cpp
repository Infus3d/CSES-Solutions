/* 
 * Problem link : https://cses.fi/problemset/task/1140
 * 
 * This would be a simple one-dimensional dp problem if the
 * values a_i and b_i were less than 1e6 instead of 1e9.
 * 
 * However, if you notice that n <= 2e5 and that they're only
 * limited a_i's and b_i's, we can take advantage of what's
 * known as 'compression' of the values. Since the values
 * of a_i and b_i are not individually important but only their
 * order is (relative to each other), we can take them all,
 * sort them, get rid of duplicates and assign every number
 * a new number that increases from smallest to highest.
 * For exampel, let's say that we have following a_i's and b_i's:
 * 4
 * 5000 6000
 * 100000 100001
 * 100001 30000000
 * 800000000 900000000
 * 
 * We can get all values and sort and get rid of duplicates:
 * [5000, 6000, 100000, 100001, 30000000, 800000000, 900000000]
 * and assign them their 'order' in this sorted array:
 * [1, 2, 3, 4, 5, 6, 7]
 * 
 * So our 'compressed' a_i's and b_i's would look like:
 * 4
 * 1 2
 * 3 4
 * 4 5
 * 6 7
 * 
 * Since n <= 2e5, this makes sure that the new values are under
 * 4e5 and allows us to use them as 'indices' on the dp array.
 * 
 * The dp itself is pretty straigtforward. It is 1-dimensional array
 * where dp[k] represents the maximum amount of money you can earn
 * by the time k:
 * ---> We iterate through the possible times (in our example above,
 *      the iteration would be from 1 to 7)
 * ---> On every iteration i we process the intervals j that have their
 *      a_j = i and we simply do dp[b_j] = dp[i-1] + p_j;
 * ---> To make sure we get the maximum of all the dp[t] from 1 <= t < i,
 *      we do dp[i] = max(dp[i], dp[i-1] on every iteration.
 * 
 * The final answer is then dp[max_possible_compressed_time]
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 4e5+2;

int n, a[N], b[N], p[N], cnt;
map<int, int> compressor;
vector<int> intervals[N]; //intervals[i] contains all intervals that start at i (with a[j] == i)

long long dp[N];

int main(){
  scanf("%d", &n);
  for(int i=1; i<=n; i++){
    scanf("%d%d%d", &a[i], &b[i], &p[i]);
    compressor[a[i]] = 1;  //we're just storing both
    compressor[b[i]] = 1;  //a_i and b_i in the map
  }
  
  /* Traversing the map from smallest to largest
   * and assigning the counter value each time.
   * For ex, let's say that the map elements are
   * currently as (key, value):
   * (3, 1), (5, 1), (6, 1), (10, 1);
   * Then the for loop below will turn that into:
   * (3, 1), (5, 2), (6, 3), (10, 4)
   * This is what's called 'compressing' the values
   * */
  for(auto &i : compressor) i.second = ++cnt;
  
  for(int i=1; i<=n; i++){
    a[i] = compressor[a[i]];
    b[i] = compressor[b[i]];
    intervals[a[i]].push_back(i);
  }
  
  for(int i=1; i<=cnt; i++){
    for(int j : intervals[i])
      dp[b[j]] = max(dp[b[j]], dp[i-1] + p[j]);
    dp[i] = max(dp[i], dp[i-1]);
  }
  printf("%lld\n", dp[cnt]);
  
  return 0;
}
