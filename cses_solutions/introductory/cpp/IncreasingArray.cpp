/*
 * Problem link : https://cses.fi/problemset/task/1094
 * 
 * We do not want to increase the first number in the array because the rest of
 * them need to be at least as big as the first one. So for every index i between
 * 2 and n, if a[i] > a[i-1] then we do not increase current a[i]. If a[i] < a[i-1]
 * then we need to increase a[i] by exactly (a[i-1] - a[i]) so we just add this number
 * onto the cumulative answer and also increase a[i] to be the same as a[i-1].
 * 
 * Runtime O(n) as we just loop through the array once
 * */
#include "bits/stdc++.h" //superheader containing all useful libraries for CP

using namespace std; //not necessary but makes life easier

int main(){
  int n;
  scanf("%d", &n); //scanning the size of the array by passing the address of n with '&n'
  
  long long ans = 0; //we need to take a long long integer because values can go beyond 32 bits
  vector<int> a(n); //just an array of n integers, all initialized to 0
  for(int i=0; i<n; i++){
    scanf("%d", &a[i]); //scanning current array element
    if(i > 0 && a[i] < a[i-1]){
      ans += (a[i-1] - a[i]); //the cost of increasing a[i] until it is the same as a[i-1]
      a[i] = a[i-1]; //actually increasing a[i]
    }
  }
  printf("%lld\n", ans); //format specifier for 'int' is '%d' and for long long int it is '%lld'
  
  return 0;
}

