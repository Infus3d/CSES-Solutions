/*
 * Problem link : https://cses.fi/problemset/task/1076
 * 
 * To keep things simpler, we take advantage of the pbds data structure - 
 * idexed set - also sometimes known as ordered set. To learn about it,
 * please refer to page 44 of this awesome book : https://cses.fi/book/book.pdf
 * 
 * We can use the 'sliding-window' technique in this problem. First, we evaluate
 * the intial median (of the first k elements) and setup the window to slide.
 * Then, for every i (k <= i < n) we 'slide' the window by inserting the new element
 * x[i] and deleting the left-most element x[i-k]. We can then simply access the median
 * by ordered_set.find_by_order(index_of_median). index_of_median can vary on whether
 * k is even or odd, but since in even cases we're allowed to print any of the 2 median,
 * we choose the first one always : index_of_median = (k-1)/2
 * 
 * Runtime O(n*log(n)) thanks to the wonderful data structure :)
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
  
  //calculate median for initial window
  indexed_set window;
  for(int i=0; i<k; i++)
    window.insert({x[i], i}); //we store them in pairs because x[i] can have duplicates
  
  int median = window.find_by_order((k-1)/2)->first; //we take the first of the pair as it stores x[i]'s
  
  printf("%d ", median); //print median of the initial window
  for(int i=k; i<n; i++){
    window.erase({x[i-k], i-k}); //delete the left-most element
    window.insert({x[i], i}); //insert a new right-most element
    
    median = window.find_by_order((k-1)/2)->first; //get the new median of the window, yes it's just this simple :)
    printf("%d ", median);
  }
  puts("");
  
  return 0;
}
