/*
 * Problem link : https://cses.fi/problemset/task/1077
 * 
 * Very first thing to note here is that the minimal cost to make all elements
 * equal in the range [l, r] will always be the cost of making them equal to
 * the median of the range. If there are two medians - that is, if (r-l+1)%2
 * is 0 - then any of the 2 medians will be the minimal cost, which makes things simpler.
 * 
 * With that being said, this problem now turns into finding the median of the
 * sliding window and keeping track of the sum of differences of every single element
 * inside the window with its median. In Sliding Median problem, we learned how
 * to find the median of every window of size k when sliding through them.
 * Now in this problem, when calculating the initial median (of the first k elements) 
 * we also calculate the cost (the sum of the differences of each element with median) 
 * for that window which we later will update with every window slide, just like we 
 * update the median of the window.
 * 
 * Case 1 --> k is odd: This is an easy case as we will have only 1 median to worry about
 * with each window update. When a window slides, we can add the new element and pop the
 * left-most element as if the old median is maintained during the process:
 * curWindowCost = -|x[i-k] - median| + |x[i] - median|. We can then simply 'simulate'
 * fixing the median to its new position (newMedian) : curWindowCost += |median - newMedian|.
 * Please take some time to understand why this works.
 * 
 * Case 2 --> k is even: This case involves 2 medians at all times in our window. But fear not,
 * as it is not so difficult to handle. So when k is even, it turns out that after inserting
 * and popping the elements (curWindowCost = -|x[i-k] - median| + |x[i] - median|) we only
 * need to worry about about the position of the old median relative to the newMedian. We always
 * consider the smaller one of the 2 medians as our 'median', that is the element indexed (k-1)/2
 * in our ordered_set.
 * ------> If newMedian <= median, that is if old median is to the 'right' of the new median, we don't
 *         need to update curWindowCost since the cost of adjusting the elements [to the newMedian] on 
 *         the right of the old median equals the cost of the left-side elements of old median, they
 *         cancel each other out.
 * 
 * ------> If median < newMedian, that is if old median is to the left of the new median the cost of
 *         fixing the median is exactly twice the difference of the medians: curWindowCost -= 2*|median - newMedian|.
 *         This is because the difference of the elements on the left of the old median with the elements on the right
 *         is exactly -2.
 * 
 * Runtime O(n*log(n)) thanks to the wonderful policy-based data structure ordered_set :)
 * */
#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp" //need to build our indexed_set

using namespace std;
using namespace __gnu_pbds; //also required

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
          tree_order_statistics_node_update> indexed_set; //defining our own type

int main(){
  int n, k;
  scanf("%d%d", &n, &k);
  
  vector<int> x(n);
  for(int i=0; i<n; i++)
    scanf("%d", &x[i]);
  
  //calculating answer for initial k-size window
  indexed_set window;
  for(int i=0; i<k; i++)
    window.insert({x[i], i});
  
  int median = window.find_by_order((k-1)/2)->first;
  long long curWindowCost = 0;
  for(int i=0; i<k; i++)
    curWindowCost += abs(median - x[i]);
  
  printf("%lld ", curWindowCost); //printing answer of the 1st window, then sliding begins
  for(int i=k; i<n; i++){
    curWindowCost -= abs(x[i-k] - median); //deleting left-element with old median
    curWindowCost += abs(x[i] - median); //inserting right-element with old median
    
    window.erase({x[i-k], i-k});
    window.insert({x[i], i});
    
    //fixing old median to new median
    int newMedian = window.find_by_order((k-1)/2)->first;
    if(k % 2 == 1)
      curWindowCost -= abs(median - newMedian);
    else if(median < newMedian)
      curWindowCost -= 2*abs(median - newMedian);
    
    median = newMedian;
    printf("%lld ", curWindowCost);
  }
  puts("");
  
  return 0;
}
