/*
 * Problem link: https://cses.fi/problemset/task/1653/
 * 
 * This can be solved by basic application of bitmasks in dp.
 * Consider an n bit number where i'th bit represents the 
 * 'chosen' state of the i'th person. If it is set, then that
 * person has alread taken a ride.
 * 
 * With this logic, we can maintain a dp that keeps track of
 * people that have already ridden the elevator in a bitmask.
 * For example, let's say that out of 5 people, 4'th and 1'st
 * indexed are already at the top of the building, then the
 * bitmask for them will be 10010 [18 in decimal].
 * 
 * On each iteration of the dp we will have the current state
 * as a bitmask, and we can choose the next person to take the ride.
 * Note that for a given bitmask, we can only choose a person i
 * if that i'th bit of the bitmask is not set [0].
 * Then we have two possibilities:
 * -----> The person's weight fits into x and can get into
 *        current ride, in which case we just increase the weight
 *        of the current ride.
 * -----> The person's weight overflows the max limit. Then we
 *        initiate a new ride with only w[i] in it (so far).
 * 
 * This requires us keep track of two values, minimum number of rides
 * done so far and the minimum number of weight in the current ride
 * over a particular bitmask (of people). So we construct our dp
 * array as a 'pair'.
 * Runtime O(n * 2^n)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 20;

int n, x, w[N];
pair<int, int> dp[(1 << 20)];

int main(){
  scanf("%d%d", &n, &x);
  for(int i=0; i<n; i++) 
    scanf("%d", &w[i]);
  
  for(int mask=0; mask<(1<<n); mask++) dp[mask] = {21, (int)1e9+1}; //fill the table with max possible values
  
  dp[0] = {1, 0}; //first ride, 0 weight initially
  for(int mask=0; mask<(1<<n); mask++)
    for(int i=0; i<n; i++)
      if(((mask >> i) & 1) == 0){ //if i'th person is not already 'taken'
        pair<int, int> current = dp[mask];
        
        if(current.second + w[i] > x){ //if he/she doesn't fit into current ride, 'create' a new ride
          current.first++;
          current.second = w[i];
        }
        else
          current.second += w[i];     //if he/she fits then just get them into current ride
        
        /**
         * update the corresponding bitmask of the 'selected' people.
         * min on pair<int, int> objects compares them by their .first,
         * then by their .second if their .first are equal.
         * */
        dp[mask | (1 << i)] = min(dp[mask | (1 << i)], current);
      }
  
  printf("%d\n", dp[(1 << n)-1].first);
  
  return 0;
}
