/*
 * Problem link : https://cses.fi/problemset/task/1632
 * 
 * A little harder version of the Movie Festival problem because we have to
 * account for k different people now, insteado of just 1.
 * 
 * However the greedy logic still follows, that is, if we have any of the k
 * members free then we assign them the next earliest ending movie (smallest b[i]).
 * To handle all k people at the same time, we can keep track of each of their
 * current movies in a multiset (because of duplicates).
 * 
 * At every iteration i through the sorted movie list, we search for a member who is
 * available to watch this movie. This means that we just need to find any member with
 * its last watched movie ending time <= a[i]. We can do this by simply binary searching
 * the smallest element strictly greater than a[i] (upper_bound) in our set. If this element
 * happens to be the smallest element in the entire set, then we don't have any member j
 * with b[j] <= a[i] at that time, so we have to skip the movie. If the binary searched 
 * element is anything but the first element of the set, then there is at least one member
 * who can watch movie i. We choose that member to be the one exactly 1 index before the binary
 * searched member (you need to see that this person will have its movie end before-or-on a[i])
 * because we want to greedily select and use the least favorible ending time (the maximum time)
 * that still fits into our criteria. So we pop out this member's last movie and insert a new 
 * one into the set (The ending times, to be precise).
 * 
 * Runtime O(n*log(n)) because of sorting and set and binary search.
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, k, ans = 0;
  scanf("%d%d", &n, &k);
  
  vector<pair<int, int>> x(n);
  for(int i=0; i<n; i++){
    int a, b; scanf("%d%d", &a, &b);
    x[i] = {b, a};
  }
  sort(x.begin(), x.end());
  
  multiset<int> members;
  for(int i=0; i<k; i++)
    members.insert(0);
  
  for(int i=0; i<n; i++){
    int a = x[i].second, b = x[i].first;
    
    auto it = members.upper_bound(a);
    if(it != members.begin()){ //if there is at least 1 member who finishes watching before a
      ans++;
      members.erase(--it);
      members.insert(b);
    }
  }
  printf("%d\n", ans);
  
  return 0;
}
