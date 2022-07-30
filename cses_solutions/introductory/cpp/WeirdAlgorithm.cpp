/*
 * Problem link : https://cses.fi/problemset/task/1068
 * 
 * We can follow the algorithm described in the problem statement literally.
 * 
 * Runtime - somewhere O(log(n)^2)
 * */
#include "bits/stdc++.h"   //this is a superheader that includes almost all libraries we need in CP

using namespace std; //not necessary but makes life easier: for ex. we can write just sort(...) instead of std::sort(...)

int main(){
  long long n; //64 bit integers (a.k.a long integer) is called 'long long' in cpp
  scanf("%lld", &n); //scanning in a long integer which has "%lld" format specifier. The &n simply passes the address of n to scan the integer into.
  
  while(n > 1){ //as described in the problem statement, we do it until n becomes 1
    printf("%lld ", n); //printing a long integer - same format specifier "%lld". Note that we do not pass the adress when printing, but the value itself
    if(n % 2 == 1)
      n = n*3+1; //if odd then multiply by 3 and add 1
    else
      n = n/2; //if even then halve it
  }
  printf("%lld ", n); //we output the final state of n, which is just 1
  
  return 0;
}
