/*
 * Problem link : https://cses.fi/problemset/task/1713
 * 
 * Since the numbers are only upto 1e6, we can maintain a cnt[] array where cnt[i]
 * will contain the number of divisors of i. 
 * To do this we can use the sieve of eratosthenes logic where we iterate over the
 * divisors k, and increment all the cnt[val] with val = k, 2*k, 3*k, ..., etc. by 1.
 * Doing so for all k between 1...1e6 will cost us n/1 increments/jumps for the
 * first iteration, n/2 for the second, n/3 for third, and so on up until n/n.
 * So the total runtime will be O(n/1 + n/2 + n/3 + ... + n/n) which we can modify
 * to be O(n * (1/1 + 1/2 + 1/3 + ... + 1/n)) which is the harmonic sum multiplied by n.
 * This approximately equals O(n * log(n)) about which you can read more in this book:
 * https://cses.fi/book/book.pdf    (Chapter 1, Mathematics)
 * 
 * There is also another way to solve the problem in O(n*sqrt(x)) which also passes
 * under the 1 sec. time limit. This approach is to simply iterate through all values
 * i with i <= sqrt(x) for each input number x and see if x % i == 0. If it is, then
 * increase the answer by 2 (because x/i also divides x) or by 1 if (i*i == x) to avoid
 * double counting.
 * 
 * Runtime O(x*log(x)) where x <= 1e6.
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 1e6+1;

int cnt[N];

int main(){
  int n;
  scanf("%d", &n);
  
  for(int i=1; i<N; i++)
    for(int j=i; j<N; j+=i)
      cnt[j]++;
  
  while(n--){
    int x;
    scanf("%d", &x);
    printf("%d\n", cnt[x]);
  }
  
  return 0;
}
