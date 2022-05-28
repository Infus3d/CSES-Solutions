/*
 * Problem link : https://cses.fi/problemset/task/2163
 * 
 * Though a little harder than its first version, the solution
 * to this problem also involves implementing what the problem
 * directly says but only this time we need to do it with the
 * right data structure. We will be using policy-based data
 * structure called indexed_set (also known as ordered_set) that
 * essentially behaves like a set<int> in std but also allows
 * accessing the elements by their indices in the set (in sorted
 * order, obviously). The data structure itself is an implementation
 * of red-black-tree which we can use by including the following:
 * 
 * ```
 * #include "ext/pb_ds/assoc_container.hpp"
 * 
 * using namespace std;
 * 
 * typedef tree<int, null_type, less<int>, rb_tree_tag,
          tree_order_statistics_node_update> indexed_set;
 * ```
 * 
 * Please refer to the following to learn more about the data structure:
 * G4G tutorial (7 min estimated) : https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/
 * From the book (Page 44) : https://cses.fi/book/book.pdf
 * 
 * Solution:
 * We initially fill the set with all the numbers in the circle. We then find the next
 * number and print it out one by one until there is nothing left in the circle. Let n
 * be the current size of the cirlce and idx be the index of the next number to remove
 * from the circle (note that it is the index, not the number itself).
 * 
 * Then we can simply print out the idx'th number from the set. Delete that 
 * number from the set and update the idx to point to the next index of the 
 * number to remove: idx = (idx + k) % n;
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp" //need to build our indexed_set

using namespace std;
using namespace __gnu_pbds; //also required

typedef tree<int, null_type, less<int>, rb_tree_tag,
          tree_order_statistics_node_update> indexed_set; //defining our own type

int main(){
  int n, k;
  scanf("%d%d", &n, &k);
  
  indexed_set circle;
  for(int i=1; i<=n; i++)
    circle.insert(i);
  
  int idx = k % n;
  for(int i=1; i<=n; i++){
    int nextNumber = *circle.find_by_order(idx);
    
    printf("%d ", nextNumber);
    
    circle.erase(nextNumber);
    if(i < n)
      idx = (idx + k) % circle.size();
  }
  puts("");
  
  return 0;
}
