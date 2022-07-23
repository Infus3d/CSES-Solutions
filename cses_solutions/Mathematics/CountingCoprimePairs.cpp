/*
 * Problem link : https://cses.fi/problemset/task/2417/
 * 
 * The solution below combines the logic of Sieve and Inclusion-Exclusion principle.
 * The following video tutorial explains the solution in pretty nicely:
 * https://www.youtube.com/watch?v=2H65yrmM0wY
 * 
 * Runtime O(N*log(N) + n*(2^f(N))*f(N)) where:
 * --> N is the max x[i] which is 1e6
 * --> f(x) is the maximum number of unique prime 
 *     factors of any number i between 2 <= i <= x.
 *     For reference f(1e6) = 7.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6+1;

int cnt[N];
vector<int> primes[N];

int main(){
  int n; 
  scanf("%d", &n);
  vector<int> a(n);
  for(int i=0; i<n; i++){
    scanf("%d", &a[i]);
  }
  
  for(int i=2; i<N; i++){
    if((int)primes[i].size() > 0) continue;
    for(int j=i; j<N; j+=i)
      primes[j].push_back(i);
  }
  
  long long ans = (1LL * n * (n-1) / 2LL);
  for(int i=0; i<n; i++){
    int m = (int)primes[a[i]].size();
    long long curNonCoprimePairs = 0;
    for(int mask=1; mask<(1<<m); mask++){
      int factor = 1;
      for(int j=0; j<m; j++){
        if((mask>>j)&1)
          factor *= primes[a[i]][j];
      }
      int setSize = __builtin_popcount(mask);
      curNonCoprimePairs += (setSize % 2 ? +1LL : -1LL) * cnt[factor];
      cnt[factor]++;
    }
    ans -= curNonCoprimePairs;
  }
  printf("%lld\n", ans);
  
  return 0;
}
