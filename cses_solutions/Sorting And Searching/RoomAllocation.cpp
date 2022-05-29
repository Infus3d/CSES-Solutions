/*
 * Problem link : https://cses.fi/problemset/task/1164
 * 
 * It is not too hard to see that the minimum number of rooms required
 * will be the maximum number (ans) of overlapping intervals at any give point.
 * Once we have ans many rooms, it will always be possible to accomodate
 * all customers using those ans rooms at any given time.
 * 
 * To calculate ans, we first sort the intervals according to their left ends (and
 * then right ends, if l[i] == l[j]). We call an interval j 'open' at position i if
 * it's left end is smaller-than-or-equal-to the left end of interval i (l[j] < l[i])
 * but its right end is bigger-than-or-equal-to it (l[i] <= r[j]).
 * Let's now store all 'open' intervals j (j < i) in a set S along with their assigned
 * room number. Then on iteration i from smallest to largest:
 * -----> We close (or pop) the intervals j with their r[j] < l[i] from S because they
 *        are clearly not overlapping with any intervals from now on. By doing this, we
 *        also free the room assigned to that interval (customer).
 * -----> Remaining intervals in S are the ones that overlap with interval i so we maximize
 *        ans with S.size() + 1 (+1 is current customer i) because we clearly need to
 *        accomodate all intervals in S and i at the same time.
 * -----> We push interval i to the set S by assigning it any of the available (free) rooms.
 *        To keep things simple, we always choose to assign the smallest room number (though
 *        it doesn't matter).
 * 
 * As an output we print ans and the rooms we assigned to every interval when we pushed them into
 * the set S.
 * 
 * Overall runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; 
  scanf("%d", &n);
  
  set<int> room;
  multiset<pair<int, int>> sofar;
  vector<pair<int, int>> x(n);
  vector<int> id(n);
  
  for(int i=0; i<n; i++){
    scanf("%d%d", &x[i].first, &x[i].second);
    id[i] = i;
    room.insert(i+1);
  }
  sort(id.begin(), id.end(), [&](int a, int b){
      if(x[a].first == x[b].first)
        return x[a].second < x[b].second;
      return x[a].first < x[b].first;
  });
  
  int ans = 0;
  vector<int> v(n);
  for(int j=0; j<n; j++){
    int i = id[j];
    while(!sofar.empty() && (sofar.begin()->first) < x[i].first){ //we pop the non-intersecting intervals
      room.insert(sofar.begin()->second); //and restore their room numbers (make those rooms available)
      sofar.erase(sofar.begin());
    }
    
    sofar.insert({x[i].second, *room.begin()});
    v[i] = (*room.begin()); //we take the smallest available room #
    room.erase(room.begin());
    ans = max(ans, (int)sofar.size());
  }
  
  printf("%d\n", ans);
  for(int i : v)
    printf("%d ", i);
  puts("");
  
  return 0;
}
