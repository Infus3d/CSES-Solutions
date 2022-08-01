/*
 * Problem link : https://cses.fi/problemset/task/1617
 * 
 * There are n possible bit places and each place can be either 1 or 2 - so two choices.
 * This tells us that we 2^n possible combinations - 2 multiplied by itself n times.
 * In fact, if you look at the bitStrings of any length n, you will see that these are
 * just the binary representations of numbers from 0 to 2^n-1 - so 2^n in total.
 * To find 2^n we can simply multiply a number by 2 n-times. However this will be very
 * big so we take the modulo 1e9+7 every time we multiply by 2.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  int ans = 1;
  for(int i=0; i<n; i++)
    ans = (ans * 2) % (1000000007); //multiply by 2 and take mod 1e9+7
  printf("%d\n", ans); //the newline character '\n' isn't necessary but it is a good practice as some online-judges strictly require it
  
  return 0;
}
