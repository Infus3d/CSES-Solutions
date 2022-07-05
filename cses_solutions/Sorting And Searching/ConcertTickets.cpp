/*
 * Problem link : https://cses.fi/problemset/task/1091
 * 
 * Let's assume that we have a special data structure that
 * is essentially a group of elements in a sorted state, all
 * the time. We can add an element or delete an element in O(logn)
 * time. And not surprisingly, we can do binary searches on sorted
 * group of elements.
 * 
 * With this data structure, let's call it S, we can solve the problem
 * in O(m*log(n)) time. 
 * First we insert all tickets into S (remember that it
 * always stays sorted). Then for every customer[j] we process their query
 * by binary searching the needed amount, that is binary searching the
 * largest element smaller than or equal to customer[j] (j's maximum ticket limit).
 * For ex:
 * S : 1, 4, 5, 5, 5, 10, 25
 * customer[j] : 6
 * The binary searched number : 'the-last-copy' of 5 (index 4, 0-based)
 * 
 * But unfortunately standard library does not support such binary-search method so
 * we need to find the answer in a bit different way(in a way that is supported :).
 * The previously mentioned binary search is equivalent to binary searching the 
 * smallest element that is strictly greater than customer[j] in S and taking the 
 * element that is exactly one index before this newly-binary-searched element 
 * in [sorted] S. And we print that value as an answer for every j.
 * For ex:
 * S : 1, 4, 5, 5, 5, 10, 25
 * customer[j] : 6
 * The binary searched number: 10 (index 5, 0-based)
 * The number/element that is one-index before : 5 (index 4, 0-based)
 * 
 * As you can see both methods yield the same result. Whenever we find the desired
 * element, we pop/delete it from the set because customer j purchases it.
 * 
 * Now this S needs to be a balanced binary search tree to guarantee we can do
 * all the operations mentioned above in O(log(n)) time. Luckily, c++ stl has
 * such implemented and ready-to-use data structures called sets and multisets.
 * multiset is the same as set but it allows duplicates in the set.
 * Sets/Multisets support 2 kinds of binary-searches:
 * -----> S.lower_bound(a) finds the smallest element that is greater than or
 *        equal to a in S.
 * 
 * -----> S.upper_bound(a) finds the smallest element that is strictly greater
 *        than a in S. (We use this one in our solution)
 * 
 * Runtime (n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n, m; 
  scanf("%d%d", &n, &m);
  
  vector<int> ticket(n), customer(m);
  for(int i=0; i<n; i++) scanf("%d", &ticket[i]);
  for(int i=0; i<m; i++) scanf("%d", &customer[i]);
  
  //This is the balanced binary-tree from stl, supports duplicate elements
  multiset<int> setik;
  for(int i=0; i<n; i++)
    setik.insert(ticket[i]);
  
  for(int i=0; i<m; i++){
    //upper_bound returns an iterator to the smallest element that is strictly larger than cusomer[i]
    set<int>::iterator it = setik.upper_bound(customer[i]);
    if(it == setik.begin()) //if the strictly larger element is already at the beginning of the [sorted] set
      printf("-1\n");
    else{
      it--; //to get the one right before the upper_bound value (so that it is guaranteed *it value is <= customer[i])
      printf("%d\n", *it); //we use * to get the value at what iterator points to
      setik.erase(it); //we need to delete the ticket after it's purchased
    }
  }
}
