/*
 * Problem link : https://cses.fi/problemset/task/1618/
 * 
 * Let's re-write the n factorial as n! = m * 10^p where m will have no trailing
 * zeros and p is the number of trailing zeros in n!. Now we can rewrite this
 * 10^p as 2^p * 5^p - two prime numbers raised to power p multiplied by each other.
 * Now we can already tell one 2 and one 5 multiplied in n! will make one trailing 0.
 * So we just need to count the number of 2s and 5s as factors of n! and take the minimum
 * of the two because (2 * 2 * 2 * 5 * 5) will produce only 2 trailing zeros not 3.
 * Let's look at n! from a new perspective:
 * n! = 1 * 2 * 3 * (2 * 2) * 5 * (2 * 3) * 7 * (2 * 2 * 2) * 9 * (2 * 5) * ...
 * We can see that in every other number there will be at least 1 factor of 2 and in
 * every 5'th number there will be at least 1 factor of 5. So we can kind of see how
 * 5 is a lot rarer than 2 so the minimum number of the factor counts of these values
 * will be the number of 5s. Thus we just need to count the number of 5s in n! and this
 * will equal the number of trailing zeros.
 * Now, we already said that every 5'th number will contribute one 5 our counter
 * because of the numbers (5, 10, 15, 20, 25, 30, ... until n). So we can increase
 * our answer by n/5 as there are this many numbers that are divisible by 5 until n.
 * Further, we can see that every 25'th number will contribute another factor of 5
 * with numbers (25, 50, 75, ..., until n). So we increase our answer by n/25. You can
 * probably see the pattern here: we increase the answer by n/(5^p) until such p makes
 * 5^p bigger than n.
 * 
 * Runtime O(log_base_5(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  int five = 5, ans = 0;
  while(five <= n){
    ans += n/five;
    five *= 5;
  }
  printf("%d\n", ans);
  
  return 0;
}
