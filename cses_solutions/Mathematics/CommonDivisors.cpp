/*
 * Problem link : https://cses.fi/problemset/task/1081
 * Video tutorial : https://www.youtube.com/watch?v=Z8Fj3pcHXDs
 * 
 * We can store the numbers in a cnt[] array where cnt[i] will be the count of numbers i
 * in the input array.
 * To find the greatest GCD of 2 numbers, we can use the Sieve logic to start from the greatest
 * potential GCD which is 1e6, and go downwards until we find the actual greatest gcd. On each
 * iteration i, we know that only the numbers i, 2*i, 3*i, ..., etc will have i as their gcd
 * so we can jump by i and sum up the cnt[] values of the numbers on the way. If the sum is at
 * least 2, the answer is i.
 * 
 * Runtime O(n + a[i]*log(a[i])) where a[i] <= 1e6.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6+1;

int cnt[N];

int main(){
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    int a; scanf("%d", &a);
    cnt[a]++;
  }
  
  for(int i=N-1; i>=1; i--){
    int sofar = 0;
    for(int j=i; j<N; j+=i){
      sofar += cnt[j];
      if(sofar > 1){
        printf("%d\n", i);
        return 0;
      }
    }
  }
  
  return 0;
}
