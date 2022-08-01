/*
 * Problem link : https://cses.fi/problemset/task/2431
 * 
 * The digits sequence has a special form:
 * ---> 9 1-digit numbers 1, 2, 3, 4, .. , 8, 9
 * ---> 90 2-digit numbers 10, 11, 12, ..., 98, 99
 * ---> 900 3-digit numbers 100, 101, ..., 998, 999
 * ---> 9000 4-digit numbers 1000, 1001, ..., 9998, 9999
 * ---> and so on...
 * 
 * So to get the k'th digit, we can just first subtract (from k) 9*1, then 90*2, then 900*3,
 * until such i where k <= 9*(10^i)*i. Because if it is smaller than the latter quantity,
 * then we know for sure that k'th digit must be one of i-digit numbers.
 * Now we know the lower bound of i-digit numbers - it is simply 10^i and our k now points
 * to the digit needed digit in the sequence only among i-digit numbers. By taking ceil(k / i)
 * and adding (10^i - 1) onto it we get exactly what number the k'th digit is from in the sequence.
 * Once we know what number it belongs to, we just print the ((k-1)%i)'th digit of this number
 * as an answer.
 * 
 * Runtime O(log_base_10(k) * q)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int q;
  scanf("%d", &q);
  while(q--){
    long long k;
    scanf("%lld", &k);
    long long tenpow = 1, dig = -1;
    for(int i=1; i<=18; i++){
      if(k <= tenpow * 9 * i){
        dig = i;
        break;
      }
      k -= tenpow * 9 * i;
      tenpow *= 10;
    }
    
    assert(dig != -1);
    long long n = tenpow - 1 + ((k + dig - 1) / dig);
    vector<int> digits;
    while(n > 0){
      digits.push_back(n % 10);
      n /= 10;
    }
    k = (k-1) % dig;
    printf("%d\n", digits[dig-k-1]);
  }
  return 0;
}
