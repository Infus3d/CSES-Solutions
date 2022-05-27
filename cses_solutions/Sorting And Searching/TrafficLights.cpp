/*
 * Problem link : https://cses.fi/problemset/task/1163
 * 
 * We start with the whole interval that covers the entire street [0, x]
 * and the initial answer x-0 as there is no traffic lights installed yet.
 * Then for each p[i] there will be exactly one interval [l, r] that covers that
 * point (l < p[i] && p[i] < r). When a traffic light is installed at p[i]
 * we essentially take that interval [l, r] and split into two new intervals:
 * [l, p[i]] and [p[i], r]. Size-wise, the size of the whole interval r-l is no more
 * but there are new 2 sizes: p[i]-l and r-p[i].
 * 
 * We do the splitting process n times where each time we add only 1 new interval.
 * We can maintain the traffic light positions in a set and the sizes of those intervals
 * in multiset (as there can be duplicate sizes). Inserting to and erasing from the set
 * costs log(n) operation.
 * 
 * Overall runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int x, n;
  scanf("%d%d", &x, &n);
  
  set<int> trafficLights;
  multiset<int>intervalSizes;
  
  //we automatically 'assume' that endpoints contain traffic lights as it makes life easier
  trafficLights.insert(0);
  trafficLights.insert(x);
  
  intervalSizes.insert(x-0); //there is only 1 interval at the start
  
  for(int i=0; i<n; i++){
    int p; scanf("%d", &p);
    
    auto it = trafficLights.upper_bound(p);
    int r = *it, l = *(--it);
    
    intervalSizes.erase(intervalSizes.find(r-l)); //we erase this whole interval
    intervalSizes.insert(p-l); //adding two new chopped interval sizes
    intervalSizes.insert(r-p);
    
    trafficLights.insert(p); //adding the new traffic light
    
    printf("%d ", *intervalSizes.rbegin()); //rbegin -> reverse begin -> largest element in the set
  }
  puts("");
  
  return 0;
}
