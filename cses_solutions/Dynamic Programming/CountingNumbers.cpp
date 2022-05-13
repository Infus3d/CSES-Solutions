/*
 * Problem link: https://cses.fi/problemset/task/2220
 * 
 * The solution uses what's known as digit dp. It is a nice way of solving
 * similar problems where you need to be aware of the digits.
 * 
 * We count the numbers with no two adjacent same digits up to b and a separately, and then
 * subtract ansA from ansB to get the final answer. However, since both a and b are inclusive,
 * we need to calculate up to (a-1) and (b) and take their difference.
 * 
 * To achieve this we maintain a dp with states [position][last Digit][equal so far].
 * On each transition, we check for every possible digit to put at current position
 * by taking advantage of [last Digit] and [equal so far] dimensions of the dp.
 * for every digit 0 <= digit < 10, we make sure that it is not equal to 'last Digit'.
 * To ensure that we are staying lower than a certain number (either a or b), keep track
 * of the equality of the number we've built so far in the dp using [equal so far] attribute.
 * If the current digit is smaller than the digit of the 'upper_bound' number (either a or b)
 * at that position, then proceed with [equal so far = 0], meaning not equal anymore.
 * If the current digit is equal to its respective digit (in either a or b) and we have 
 * [equal so far] == 1 then, proceed with [equal so far = 1] too.
 * For digits that are greater than its respective digit, only proceed with that digit
 * when [equal so far] == 0 for current position, because we can't got above the 'upper_bound'
 * number.
 * */
#include "bits/stdc++.h"

using namespace std;

using ll = long long;

ll dp[20][11][2];

ll rec(int pos, int lastDigit, int equal, vector<int> &num){
  //base case, once the function hits this limit then there is definitely a way
  if(pos >= 19) return 1ll;
  
  //checking if this state has been visited before, if it is, then no further action needed
  ll &ret = dp[pos][lastDigit][equal];
  if(ret != -1) return ret;
  
  //checking every possible digit for current position
  ret = 0ll;
  for(int i=0; i<10; i++){
    if(i > num[pos] && equal) break;
    
    int newEq = (equal && i == num[pos]);
    int newDig = (lastDigit == 10 && i == 0 ? 10 : i); //10 is just a reserved "digit" to indicate the leading zeros
    
    if(i != lastDigit) //make sure no two adjacent digits are the same
      ret += rec(pos+1, newDig, newEq, num);
  }
  return ret;
}

ll getAnsUpTo(ll x){
  if(x < 0) return 0;
  
  vector<int> v;
  while(x > 0){
    v.push_back(x % 10); //extracting digits
    x /= 10;
  }
  
  while((int)v.size() < 19) 
    v.push_back(0); //filling in the leading zeros
  
  reverse(v.begin(), v.end()); //making a simple 123 look like 0000000000000000123 (19 digits)
  
  memset(dp, -1ll, sizeof(dp));
  return rec(0, 10, 1, v);
}

/*
 * 
 * */
int main(){
  ll a, b;
  scanf("%lld%lld", &a, &b);
  
  ll ansUpToA = getAnsUpTo(a-1); //because a is inclusive
  ll ansUpToB = getAnsUpTo(b);
  
  printf("%lld\n", ansUpToB - ansUpToA);
  
  return 0;
}
