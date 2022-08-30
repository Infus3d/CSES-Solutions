/*
 * Problem link : https://cses.fi/problemset/task/1754
 * 
 * First let's note that in each operation we subtract 1 from one pile and 2 from the other.
 * So we subtract 3 in total from the sum of the 2 piles. This implies that the sum of the piles
 * must be divisible by 3 for answer to exist. If it is not divisible by 3 then there will be
 * either:
 * ---> a remainder 1 with final setting of the piles (3k+1, 0) or (0, 3k+1) for k \in Z
 * ---> or a remainder of 2 with final setting of the piles (0, 3k+2) or (3k+2, 0) or (3k+1, 3t+1) for k, t \in Z
 * 
 * Now, that we made sure the sum is divisible by 3 let's call a = minimum of the 2 piles and
 * b = maximum of the 2 piles. For answer to exist, it is also necessary that a*2 >= b. For example
 * take the input (2, 7). (2+7) is divisible by 3 but after performing 2 operations we will be left
 * with (0, 4) and this happened because 2*2 < 7.
 * You can visualize it this way: when we subtract 1 from a and 2 from b, we are essentially subtracting
 * 1 more from b than a. So on each operation we are getting b closer to a. But we can do so only a limited
 * number of times - namely a times at most. So that's why if a*2 is smaller than b there is no answer.
 * But what happens if b gets closer and closer to a and finally equals it? Then the answer definitely exists
 * because we know that (a+b) is divisible by 3 and they are equal so we can just alternate taking (-1, -2)
 * and (-2, -1) from these piles until both of them reach 0.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  while(n--){
    int a, b;
    scanf("%d%d", &a, &b);
    if(a > b)
      swap(a, b); //make sure a is the smaller one
    
    if((a+b)%3 != 0 || a*2 < b) //as described above
      puts("NO"); //puts("") prints a string and appends a newline at the end
    else
      puts("YES");
  }
  return 0;
}
