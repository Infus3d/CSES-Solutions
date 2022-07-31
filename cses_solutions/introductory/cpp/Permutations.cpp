/*
 * Problem link : https://cses.fi/problemset/task/1070
 * 
 * If n is 2 or 3 then there is no solution, obviously.
 * If n is even, then we can print all even numbers first, then all odd numbers.
 * That way we guarantee that the difference between the numbers of the same parity
 * is 2 and the difference between the last even number (n) and the first odd number (1)
 * is more than 1.
 * If n is odd, then we can print all odd numbers first, then even numbers. The reason
 * is analogous to when n is even.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h" //superheader containing all useful libraries for CP

using namespace std; //not necessary but makes life easier

int main(){
  int n;
  scanf("%d", &n); //scanning the size by passing the address of n (&n) to scan the number into
  if(n == 2 || n == 3){ //it is impossible when n is 2 or 3
    puts("NO SOLUTION");
    return 0;
  }
  
  for(int i=1; i<=n; i++)
    if(i % 2 == n % 2) //we first print either odd or even numbers depending on parity of n
      printf("%d ", i);
  
  for(int i=1; i<=n; i++)
    if(i % 2 != n % 2) //we then print either odd or even numbers again depending on parity of n
      printf("%d ", i);
  
  return 0;
}
