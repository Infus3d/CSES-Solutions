/*
 * Problem link : https://cses.fi/problemset/task/2182
 * Video tutorial: https://www.youtube.com/watch?v=__21DNroCLo
 * 
 * We will be referring to the following book for all three of the quantities we need to find:
 * https://cses.fi/book/book.pdf   (Chapter 21, Primes and factors)
 * 
 * Number of Divisors:
 * This one is the easiest to find out of three. The number of divisors of any number n is
 * tau(n) = product of (k[i]+1) over all i where k[i] is the power of the i'th prime factor.
 * 
 * 
 * Sum of Divisors:
 * As explained in the textbook, the sum of the divisors can be obtained using formula:
 * lowercase_sigma(n) = product of (x[i]^(k[i]+1) - 1) / (x[i] - 1) over all i where x[i] is the
 * i'th prime factor and k[i] is its power. We can easily find the value (x[i] ^ (k[i]+1))
 * using binary exponentiation modulo 1e9+7 and we can also take (x[i] - 1) modulo 1e9+7. However
 * (a / b) % mod does not equal ((a % mod) / (b%mod)) % mod. We need to use modular inverse to
 * calculate the ratio modulo mod. To learn the concept please refer to:
 * https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 * Using this, we can turn ratio (a/b) % mod into ((a % mod) * (b^(mod-2) % mod)) % mod.
 * In the above formula we need to multiply the numerator with (x[i]-1) ^ (1e9+5) % mod.
 * 
 * 
 * Product of divisors:
 * It is explained in the book that the product of divisors of the number n is:
 * lowercase_mu(n) = n ^ (tau(n)/2) where tau(n) is defined as the number of divisors of n (see above).
 * Now the number of divisors is even for all numbers except perfect squares; so for such numbers we
 * can just divide the power (tau(n)) by 2. But for perfect squares we can notice that n^(tau(n)/2)
 * equals (n^(1/2))^tau(n) so we can just take the square root of the number first then take its tau(n)'th
 * power. Now in either case, we need to know the actual n (mod 1e9+7) itself before we can take its power.
 * n = product of (x[i] ^ k[i]) % mod over all i which we can easily calculate using binary exponentiation.
 * n is a perfect square if all of the powers of its prime factors are even. Once we know that n is a perfect
 * square, to take the square root of n we can simply take sqrt(n) = (x[i] ^ (k[i]/2)) % mod over all i.
 * 
 * Now that we have our n or sqrt(n) calculated, it is time to take tau(n)'th power of it. We have 2 cases:
 * ---> n is a perfect square. In this case, since we already have our sqrt(n) at hand, we can just take
 *      tau(n)'th power of it. To do that, we see that tau(n) = (k[0]+1) * (k[1]+1) * (k[2]+1) * ... (k[m-1]+1)
 *      where k[i] is the power of the i'th prime factor. So taking that as an exponent of sqrt(n) will make it
 *      sqrt(n) ^ tau(n) = (((sqrt(n)^(k[0]+1))^(k[1]+1))^(k[2]+1))^... and so on. So we can first take 
 *      current = sqrt(n)^(k[0]+1) and then raise current = current ^ (k[1]+1) after which raise current = current ^ (k[2]+1)
 *      and so on. Each of such exponentiation will take log(k[i]) time to calculate modulo 1e9+7.
 * 
 * ---> n is not a perfect square. In this case, to calculate n ^ (tau(n)/2) we mentioned that we can just divide
 *      tau(n) by 2. Since tau(n) is just the product of powers and we know that it is even, we can find one of its
 *      even factors (k[i]+1) and divide that by 2 (but only one of them, only once!). And then we can calculate the
 *      rest like in the prior case.
 * 
 * Runtime (n * (log(k[i]) + log(MOD))) where k[i] <= 1e9 and MOD = 1e9+7
 * */
#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9+7;

long long bmod(int x, int deg){
  if(deg == 0)
    return 1;
  
  long long half = bmod(x, deg/2);
  long long full = (half * half) % MOD;
  if(deg % 2 == 1)
    full = (full * x) % MOD;
  
  return full;
}

int main(){
  int n; 
  scanf("%d", &n);
  
  long long divNum = 1, divSum = 1, parity = 0;
  
  vector<int> x(n), k(n);
  for(int i=0; i<n; i++){
    scanf("%d%d", &x[i], &k[i]);
    divNum = (divNum * (k[i]+1)) % MOD; //number of divisors is easy to calculate
    divSum = (divSum * (((bmod(x[i], k[i]+1)-1) * bmod(x[i]-1, MOD-2)) % MOD)) % MOD; //this also follows the formula for sum of divisors
    parity += (k[i] % 2); //we need to know the partiy of the factors' powers to determine whether our omega-huge number is a perfect square or not
  }
  
  long long theN = 1;
  for(int i=0; i<n; i++){
    if(parity == 0)
      theN = (theN * bmod(x[i], k[i]/2)) % MOD;
    else
      theN = (theN * bmod(x[i], k[i])) % MOD;
  }
  
  long long divProd = theN, still = 1;
  for(int i=0; i<n; i++){
    if(k[i] % 2 == 1 && still != 0){
      divProd = bmod(divProd, (k[i]+1)/2);
      still = 0;
    }
    else
      divProd = bmod(divProd, k[i]+1);
  }
  printf("%lld %lld %lld\n", divNum, divSum, divProd);
  
  return 0;
}
