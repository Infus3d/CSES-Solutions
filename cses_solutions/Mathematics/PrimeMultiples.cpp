#include "bits/stdc++.h"

using namespace std;

long long n, k;
vector<int> primes;

long long rec(long long cur, int pos){
  if(pos >= k) return 0;
  long long ret = rec(cur, pos+1);
  for(int i=0; i<64; i++){
    if(n / primes[pos] < cur)
      break;
    ret += rec(cur * primes[pos], pos+1)+1;
    cur *= primes[pos];
  }
  return ret;
}

int main(){
  scanf("%lld%lld", &n, &k);
  primes.resize(n);
  for(int i=0; i<k; i++)
    scanf("%d", &primes[i]);
  
  printf("%lld\n", rec(1LL, 0));
  return 0;
}
