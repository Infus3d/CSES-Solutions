/*
 * Problem link : https://cses.fi/problemset/task/2164
 * 
 * Let's see what happens in each iteration of the circle of 14 people:
 * Initially   ----> 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 * 
 * Iteration 1 ----> 1, 3, 5, 7, 9, 11, 13      (2, 4, 6, 8, 10, and 14 are removed)
 * Iteration 2 ----> 1, 5, 9, 13                (3, 7, and 11 are removed)
 * Iteration 3 ----> 5, 13                      (1 and 9 are removed)
 * Iteration 4 ----> 13                         (5 is removed)
 * 
 * You can see that there is a certain pattern. Let's say that n[i] is the number of people in
 * the end of i'th iteration (n[0] = 14, n[1] = 7, etc). There are 3 main quantities that can change
 * in each round/iteration:
 * -----> n[i] or the number of people, obviously. It is halved everytime, so the maximum number 
 *        of iterations will be log(n[0]).
 * -----> The difference between each neighboring people. Initially it is 2^0, then it becomes 2^1,
 *        then 2^2, and so on. So basically diff[i] = 2^i (for ex. diff[1] = 2 because 1, 3, 5, 7, 9, 11, 13).
 * -----> The starting number st[i] of the sequence. This one does not always change but it has the potential to change.
 *        For example, the starting number is 1 for iterations 1 and 2, and 5 for 3rd iteration and finally 13 for 4th.
 * 
 * If there was a way to maintain/keep track of these 3 values for each iteration we could easily find the k'th
 * person to be removes from the circle. On each iteration i we know the number of people to be removed: n[i-1] / 2.
 * So if k > n[i-1]/2 we move onto the next iteration by doing k -= n[i-1]/2 because we need to find (k - n[i-1]/2)'th
 * number to removed in the next iteration (iteration i+1).
 * But if k <= n[i-1]/2 then we know that the removal of the k'th person definitely happens in this i'th iteration.
 * Since we know the starting number at i'th iteration and the difference between the numbers, it is not hard to find
 * the k'th element of the arithmetic progression: (st[i] + (k-1)*diff[i]).
 * 
 * Now the only thing left to do is to actually keep track of these 3 values:
 * -----> n[i] is easy to know when n[i-1] is even: n[i] = n[i-1]/2. However when n[i-1] is odd, we need to know
 *        whether the removal started from the first person of these n[i-1] people or the second. If it started
 *        from the first, then n[i] = n[i-1]/2. If not, then n[i] = n[i-1]/2 + 1.
 * 
 * -----> diff[i] is simple diff[i] = diff[i-1] * 2
 * 
 * -----> st[i] changes from st[i-1] only when the removal of (i-1)'th iteration started from the 1st person in the sequence.
 *        And that depends on whether the removal of (i-2)'th iteration ended in n[i-2]'th person. If it did, then the next
 *        iteration's removal starts from the 2nd person. But if (i-2)'th iteration ended in (n[i-2]-1)'th person, then removal
 *        of (i-1)'th iteration starts from 1st person and st[i] becomes st[i-1] + diff[i-1] instead of staying as st[i-1].
 * 
 * There is also a recursive explanation in this blog but I personally could not understand it:
 * https://codeforces.com/blog/entry/82103
 * 
 * Runtime O(q*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int q; 
  scanf("%d", &q);
  while(q--){
    int n, k;
    scanf("%d%d", &n, &k);
    int prev = 0, deg = 1, st = 1;
    while(k > 0){
      int cur = n % 2;
      int half = n/2 + (prev & cur);
      if(k <= half){
        if(!prev) st += deg;
        printf("%d\n", st+((k-1)*deg*2));
        break;
      }
      k -= half;
      n -= half;
      if(prev == 1)
        st += deg;
      prev = (prev ^ cur);
      deg *= 2;
    }
  }
  
  return 0;
}
