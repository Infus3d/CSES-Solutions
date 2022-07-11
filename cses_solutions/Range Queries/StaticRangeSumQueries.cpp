/*
 * Problem link : https://cses.fi/problemset/task/1646
 * 
 * We can use partial/prefix sums in this problem. We can take the given array a[] and
 * turn it into a prefix sum array by just doing a[i] += a[i-1]. Then a[i] would contain
 * the sum of the range [1, i].
 * Now to answer the queries and get the sum of range [l, r] we note that:
 * sum[l, r] = sum[1, r] - sum[1, l-1].
 * 
 * Since we have both values on the right hand side of the equation already precomputed,
 * we can just print the difference.
 * 
 * Runtime O(n+q)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q;
long long a[N];

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%lld", &a[i]);
    a[i] += a[i-1];
  }
  
  while(q--){
    int l, r;
    scanf("%d%d", &l, &r);
    printf("%lld\n", a[r]-a[l-1]);
  }
  return 0;
}
