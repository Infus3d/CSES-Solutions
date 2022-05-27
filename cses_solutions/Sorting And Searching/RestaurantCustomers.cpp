/*
 * Problem link : https://cses.fi/problemset/task/1619
 * 
 * Let's assume that both a[i] and b[i] are <= 2e5 for now.
 * This enables us to use them as array indices, which is awesome.
 * An interval [a[i], b[i]] means that the customer i is in restaurant
 * starting from a[i] through b[i] which makes us think that maybe we 
 * can somehow simulate that. Let's do it with the sample:
 * 3
 * 5 8
 * 2 4
 * 3 9
 * 
 * Imagine we have a timeline as an array. Then for each interval, we can
 * simulate the time spent by customer i in the restaurant by incrementing
 * the left end timeline[a[i]]++ and decrementing the instance right after
 * the right end timeline[b[i]+1]-- (because it's inclusive). This way we can
 * get the number of customers that were in the restaurant at any given time
 * through the timeline by adding the numbers in timeline array from left to 
 * right. For example, the above intervals would produce:
 * 
 * index:       0 1 2 3 4 5 6 7 8 9 10 ...
 * timeline[] : 0 0 1 2 2 2 2 2 2 1  0 ...
 * 
 * Because each interval would contribute as:
 * 
 * ----> interval [5, 8]
 *                            +1          -1
 * index:       0  1  2  3  4  5  6  7  8  9  10 ...
 * timeline[] : 0  0  0  0  0  1  1  1  1  0   0 ...
 * 
 * ----> interval [2, 4]
 *                   +1       -1
 * index:       0  1  2  3  4  5  6  7  8  9  10 ...
 * timeline[]:  0  0  1  1  1  0  0  0  0  0   0 ...
 * 
 * ----> interval [3, 9]
 *                      +1                    -1
 * index:       0  1  2  3  4  5  6  7  8  9  10 ...
 * timeline[]:  0  0  0  1  1  1  1  1  1  1   0 ...
 * 
 * Adding all these intervals is the same as doing timeline[a[i]]++, timeline[b[i]+1]--
 * first and accumulating the sums all together from left to right because addition 
 * is commutative and associative.
 * 
 * The answer will then be the maximum timeline[i] over all i.
 * 
 * Now since the numbers a[i] and b[i] are <= 1e9 in the problem (unlike what we assumed)
 * we need to do 'compressing' on them. Since in this problem only the order of the intervals
 * matters, we can replace the big numbers with smaller numbers while still maintaining the
 * order. We can do it by gathering all a[i]'s and b[i]'s and chosing only the distinct numbers
 * among them and assigning those numbers a new value in the increasing order(sorted order). 
 * Please look at the code below where an std map is used as the compressor. Map automatically
 * orders (sorts) the (key, value) pairs according to their keys.
 * (You can also look into Projects.cpp in 'Dynamic Programming' section/folder to learn more
 * about compression. Or just google 'value compression competitive programming')
 * 
 * Total runtime: O(n*log(n)) because of map -> insertion is logn
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<int> a(n), b(n);
  map<int, int> compressor;
  
  for(int i=0; i<n; i++){
    scanf("%d%d", &a[i], &b[i]);
    compressor[a[i]] = compressor[b[i]] = 1; //inserting into map
  }
  
  int cnt = 0;
  for(auto &i : compressor)
    i.second = ++cnt; //'compressing' the values
  
  vector<int> timeline(cnt+1);
  for(int i=0; i<n; i++){
    int aa = compressor[a[i]];
    int bb = compressor[b[i]];
    timeline[aa]++, timeline[bb+1]--;
  }
  for(int i=1; i<=cnt; i++)
    timeline[i] += timeline[i-1];
  
  int ans = 0;
  for(int i=0; i<=cnt; i++)
    ans = max(ans, timeline[i]);
  printf("%d\n", ans);
  
  return 0;
}
