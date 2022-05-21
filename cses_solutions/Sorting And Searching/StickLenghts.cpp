/*
 * Problem link : https://cses.fi/problemset/task/1074
 * 
 * We can sort all elements in give array p and for each
 * p[i] find out cost of making sticks that are smaller than
 * p[i] (to the left of i) and sticks that are larger than p[i]
 * (to the right of i) equal to p[i].
 * Let's first find the cost making sticks p[j] (j <= i) equal to p[i]
 * (the right side follows analogously) and store it in a[i] :
 * ----> Assume that all p[j] (j <= i-1) are already equal to p[i-1] and
 *       the cost of doing so is stored in a[i-1]. Then to 'raise' all
 *       i-1 number of sticks from p[i-1] to p[i] it will cost
 *       (p[i] - p[i-1]) * (i-1). So a[i] would be the sum of the latter
 *       and a[i-1] : a[i] = a[i-1] + (p[i] - p[i-1]) * (i-1).
 * 
 * We can do the right side analogously and store the cost of making sticks
 * p[j] (i <= j) equal to p[i] in b[i].
 * The answer would then be the minimum (a[i] + b[i]) over all i (1 <= i <= n)
 * 
 * Runtime O(n*log(n))
 **/
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<long long> p(n+2), a(n+2), b(n+2);
  for(int i=1; i<=n; i++) 
    scanf("%lld", &p[i]);
  sort(p.begin()+1, p.end()-1);
  
  for(int i=2; i<=n; i++)
    a[i] = a[i-1] + (p[i] - p[i-1]) * (i-1);
  for(int i=n-1; i>=1; i--)
    b[i] = b[i+1] + (p[i+1] - p[i]) * (n-i);
  
  long long ans = 1e18;
  for(int i=1; i<=n; i++)
    ans = min(ans, a[i] + b[i]);
  printf("%lld\n", ans);
  
  return 0;
}
