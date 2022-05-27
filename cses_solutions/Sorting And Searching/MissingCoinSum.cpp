/*
 * Problem link : https://cses.fi/problemset/task/2183
 * 
 * We first sort the given array x in non-decreasing order.
 * We establish the current smallest unattainable sum (ans) 
 * as 1 to start and maintain it when iterating from smallest to highest:
 * 
 * -----> if x[i] is greater than 'ans' then there is no way future
 *        x[j]'s will be able to make the sum 'ans' they are all greater
 *        than x[i] (i <= j && x[i] <= x[j]). So we print out 'ans'.
 * 
 * -----> if x[i] is smaller than or equal to 'ans' then we simply add it
 *        onto 'ans': ans += x[i]. This means that if we are able to make
 *        all sums up to 'ans' (not including) then we can also add x[i] to
 *        those sums to make every integer in the range [ans, ans+x[i]-1].
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<int> x(n);
  for(int i=0; i<n; i++)
    scanf("%d", &x[i]);
  
  sort(x.begin(), x.end());
  long long ans = 1LL;
  for(int i=0; i<n; i++){
    if(ans < x[i])
      break;
    ans += x[i];
  }
  printf("%lld\n", ans);
  
  return 0;
}
