/*
 * Problem link : https://cses.fi/problemset/task/1749
 * 
 * Let's take the input array a[] = {2, 6, 1, 10, 2} and imagine a concurrent array
 * b[] = {1, 1, 1, 1, 1} that is all 1 initially. b[i] = 1 indicates that a[i] is
 * still in the list, i.e. it has not been removed yet.
 * 
 * Initially, when we want to find and pop the 3'rd element from the list, we just
 * get the element {1} and print it out while also making b[3] = 0. Now, again if we
 * were to pop the 3'rd element from the list, we would need to start from index 1
 * and start counting the number of 1's in b[] array until we hit 3. Once we hit 3,
 * we know that the corresponding element in a[] array is the 3'rd element in our dynamic
 * list - which is element {10}. So after we print it out, we do b[4] = 0 and proceed to
 * next query.
 * Now the gist here is that when we want to pop idx'th element from the dynamic list,
 * we need to find the smallest index i in b[] array such that the sum b[1, ... , i] = idx.
 * We can do this with segment trees by 'walking' till we hit the needed sum. Let's build
 * a sum segment tree over array b[] which is initially all 1.
 * Now when querying for idx'th element, we start from root and proceed downward to find
 * the static index of the idx'th element in dynamic list. We first look into the value
 * of the left child, which is the count of the remaining elements in the dynamic list.
 * If this count is bigger-than-or-equal to idx, then go into the left child because clearly
 * what we're looking for is in there. If the value of the left-child is smaller than idx,
 * then we proceed to the right child but this time with idx = idx - value_of_left_child.
 * Once we hit singularity - when (l == r) - we update the value at this node from 1 to 0
 * (because we pop it from the list) and return the corresponding index of this node in the
 * static (initial) list, which is just l (or r, they're equal).
 * 
 * Once we get the static index of the idx'th element in dynamic list, we can just print
 * a[static_index].
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y) ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, a[N], T[N<<2];

void build_tree(int l, int r, int v){
  if(l == r){
    T[v] = 1;
    return;
  }
  build_tree(l, mid(l, r), v<<1);
  build_tree(mid(l, r)+1, r, v<<1|1);
  T[v] = T[v<<1] + T[v<<1|1];
}

int find_and_update(int idx, int l, int r, int v){
  if(l == r){
    T[v] = 0;
    return l; //we return the element index as if the initial array was untouched
  }
  
  int ret = 0;
  if(idx <= T[v<<1]) //if the count of remaining elements in the left child is <= than our idx
    ret = find_and_update(idx, l, mid(l, r), v<<1);
  else //if not
    ret = find_and_update(idx-T[v<<1], mid(l, r)+1, r, v<<1|1); //we look for (idx-element_count_of_left_child)'th index in the right child
  
  T[v] = T[v<<1] + T[v<<1|1];
  return ret;
}

int main(){
  scanf("%d", &n);
  for(int i=1; i<=n; i++)
    scanf("%d", a+i); //this is fancy way of getting int into a[i] :)
  
  build_tree(1, n, 1);
  for(int i=1; i<=n; i++){
    int idx; scanf("%d", &idx);
    int actual_idx = find_and_update(idx, 1, n, 1);
    printf("%d ", a[actual_idx]);
  }
  
  return 0;
}
