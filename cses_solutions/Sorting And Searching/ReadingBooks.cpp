/*
 * Problem link : https://cses.fi/problemset/task/1631
 * 
 * The solution is rather simple in this problem. Let mx be
 * the maximum element and sum be the total sum of the array a[]:
 * 
 * ------> If mx >= sum-mx, then the answer is mx*2. This is because
 *         while A is reading the mx-book, B can read through the 
 *         rest of the books and still has to wait for A to finish 
 *         the last book. Then, A will read through the rest of the
 *         books while B is reading the mx-book. So a total of mx*2
 *         time is needed.
 * 
 * ------> If mx < sum-mx then the answer is simply sum. To see this,
 *         first note that the condition implies there are at least 3
 *         books to read. Also imagine that the books are sorted in
 *         non-decreasing order. Then, B starts to read from the highest (a[n]),
 *         that is, B reads mx-book first. A starts from the smallest (a[1])
 *         and reads throuh the books until B finishes reading the book a[n]. 
 * ----------------> If A is reading book a[n-1] at this time then B starts reading from a[n-2]
 *                  towards a[1] and reads a[n-1] at the end when A is reading its last book a[n].
 *                  This evidently takes sum amount of time for both A and B.
 * 
 * ----------------> If A is reading the book a[m] with m < n-1 at the time B finishes reading a[n],
 *                  B will simply switch to the next highest book (a[n-1]) and continue on towards a[1].
 *                  During that time A finishes reading its current book (a[m]) and starts reading 
 *                  from the a[n] backwards (towards the smaller books) until it reaches the book a[m].
 *                  This way, each of them can read all books in sum amount of time.
 * 
 * Runtime O(n) as we don't really need to sort to find mx and sum.
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, mx = 0; 
  scanf("%d", &n);
  
  long long sum = 0;
  for(int i=0; i<n; i++){
    int a; 
    scanf("%d", &a);
    mx = max(mx, a);
    sum += a;
  }
  if(mx > sum-mx)
    printf("%lld\n", mx*2LL);
  else
    printf("%lld\n", sum);
  
  return 0;
}
