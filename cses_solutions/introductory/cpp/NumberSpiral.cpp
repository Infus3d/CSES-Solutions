/*
 * Problem link : https://cses.fi/problemset/task/1071
 * 
 * First we can see that the spiral consists of several shells where i'th shell
 * contains all numbers from (i-1)^2+1 till i^2.
 * When we want to find the number at (y, x), the maximum of the two determines
 * what shell the cell (y, x) is in. For example, for the cell (2, 3) is in shell
 * 3 and has a value 8.
 * We have 2 scenarios:
 * ----> y <= x, then we are looking at y'th shell. These shells can either be increasing or decreasing
 *       starting from the first column to the right:
 *       ----> if y % 2 == 0 then the shell is decreasing at y'th row from 1st column to the right. So the
 *             cell value at (y, x) is y^2 - (x-1).
 *       ----> if y % 2 == 1 then the shell is increasing at y'th row from 1st column to the right. So the
 *             cell value at (y, x) is (y-1)^2 + x
 * 
 * ----> x < y, then we are looking at x'th shell. These shells can either be increasing or decreasing
 *       starting from the first row downwards:
 *       ----> if x % 2 == 0 then the shell is increasing at x'th column from 1st row downwards. So the
 *             cell value at (y, x) is (x-1)^2 + y.
 *       ----> if x % 2 == 1 then the shell is decreasing at x'th column from 1st row downwards. So the
 *             cell value at (y, x) is x^2 - (y-1)
 * 
 * Runtime O(t)
 * */
#include "bits/stdc++.h" //superheader containing all useful libraries for CP

using namespace std; //not necessary but makes life easier

int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    long long y, x;
    scanf("%lld%lld", &y, &x);
    int maxi = max(y, x); //maximum of the two is the shell number
    long long ans = 0;
    if(maxi == y){
      if(y % 2 == 0) //if it is a 'decreasing-shell' then it starts at y^2 and decreases by 1 for each column to the right
        ans = y * y - (x-1);
      else  //if it is an 'increasing-shell' then it starts at (y-1)^2+1 and increases by 1 for each column to the right
        ans = (y-1) * (y-1) + x;
    }
    else{
      if(x % 2 == 0) //if it is an 'increasing-shell' then it starts at (x-1)^2+1 and increases by 1 for each row downwards
        ans = (x-1) * (x-1) + y;
      else  //if it is a 'decreasing-shell' then it starts at x^2 and decreases by 1 for each row downwards
        ans = x * x - (y-1);
    }
    printf("%lld\n", ans); //format specifier for long long int is '%lld'
  }
  
  
  return 0;
}
