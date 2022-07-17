/*
 * Problem link : https://cses.fi/problemset/task/2416
 * Prereq:
 * -----> Segment tree with lazy propagation (or BIT with range update/sum)
 *        https://cses.fi/book/book.pdf  (Section 20.1)
 *        https://cp-algorithms.com/data_structures/segment_tree.html#range-updates-lazy-propagation
 * 
 * Using the word 'increasing' for the purpose of this assignment does not quite feel right as it should 
 * be called 'non-decreasing' if numbers are allowed to be <= next number. So from now on, we will refer
 * to it as non-decreasing.
 * 
 * Let's take the input array a[] = {2, 10, 4, 2, 5, 3} and try to answer the query for [1, 6] : what is 
 * the minimum number of operations to make the entire array non-decreasing. To answer this, let's start
 * from the end of the array and move towards left, processing each index i one-by-one, at each step trying
 * to make the range [i, n] non-decreasing with minimal cost. Let's also keep an empty array b[] with all
 * 0 initially:
 * ----> i = 6 with a[i] = 3, here the subarray [3] is already non-decreasing.
 * 
 * ----> i = 5 with a[i] = 5. We look to the right of index i and try to make the elements equal at least
 *       a[i]. We see that 3 < 5 so we add the cost 5-3 = 2 onto b[6]. 
 *       b is now equal to [0, 0, 0, 0, 0, 2].
 *       a is now equal to [2, 10, 4, 2, 5, 5]
 * 
 * ----> i = 4 with a[i] = 2. We look to the right and try to find an element that smaller that a[i] = 2.
 *       There isn't any so a[] is already non-decreasing with no updates.
 * 
 * ----> i = 3 with a[i] = 4. Again we look to the right and try to find an element smaller than 4. We find
 *       a[4] = 2 and so add the cost of operations (4-2 = 2) onto array b. Note that when we look for smaller
 *       elemnts we can start from the nearest right index and go until we find greater element than a[i].
 *       Because once we find such greater element a[j], we can be sure that anything beyond [to the right of]
 *       j is gonna be greater than a[i].
 *       b[] = [0, 0, 0, 2, 0, 2]
 *       a[] = [2, 10, 4, 4, 5, 5]
 * 
 * ----> i = 2 with a[i] = 10. We look to the right of i and modify elements to be at least 10 until we find
 *       an element greater than 10. We add the costs of modification onto array b[].
 *       b[] = [0, 0, 6, 8, 5, 7]
 *       a[] = [2, 10, 10, 10, 10, 10]
 * 
 * ----> i = 1 with a[i] = 2. We look to the right and can't find any smaller element than 2. No updates.
 *       a[] = [2, 10, 10, 10, 10, 10] is non-decreasing as is.
 * 
 * Now if you noticed above, at index i once you modify elements a[j] to the right of i to be at least a[i],
 * we form a 'pile' of equal elements (all equal to a[i]) until we find another such greater pile. We can store
 * such piles/intervals in a stack with tuples {a[i], l, r} where a[i] will be the element/value of this interval
 * and [l, r] will be its range. Then when we 'look to the right' at each index i, we can simply look to the
 * top of the stack and pop from it as long as the interval at the top has a smaller value than a[i]. Let's take
 * one such interval {val, l, r} with val < a[i]. Note that the modification cost of making elements in this
 * interval at least a[i] is the same for all elements of this range[l, r]: it is (a[i] - val) for each of them.
 * So we use lazy propagation to add (a[i] - val) into the range [l, r] of the segment tree. Here the segment tree
 * will be the b[] array described above.
 * 
 * Note that the size of the stack can increase by at most 1 on each iteration making the total amortized runtime
 * of this lazy-addition operations n*log(n).
 * 
 * To process the queries, we can sort them according to their left ends. For example, if we have queries count q = 4
 * with queries [{5, 5}, {2, 3}, {1, 4}, {2, 6}]  in the input, the sorted order will be
 * [{1, 4}, {2, 3}, {2, 6}, {5, 5}].
 * 
 * Then we start from the end of this sorted list and process the elements of the array a[] as described above,
 * starting from the end until we hit the l[i] of the current query i. This guarantees that the range [l[i], n]
 * of the array a[] is made non-decreasing and all costs were added into the segment tree (array b[] above)
 * before we process current query i. To process the query, we simply take the sum of the range [l[i], r[i]] of
 * the segment tree. 
 * 
 * After we're done with query i, we move to the next query i-1 and again process the range of the array from
 * the last processed index (in query i for example) until we hit the left end of qurrent query, which is l[i-1]
 * so that subarray a[l[i-1], n] will be non-decreasing.
 * 
 * Note that we also need to keep track of the order of the queries in the intial format to avoid
 * mixing them in the output.
 * 
 * Runtime O((n+q)*log(n))
 * */
#include "bits/stdc++.h"

#define mid(x, y)  ((x+y)/2)

using namespace std;

const int N = 2e5+1;

int n, q, a[N];
long long T[N<<2], lz[N<<2], ans[N];
vector<pair<int, int>> Queries[N];

void push(int l, int r, int v){
  if(lz[v] == 0) return;
  T[v<<1] += lz[v] * (mid(l, r)-l+1);
  T[v<<1|1] += lz[v] * (r-mid(l, r));
  
  lz[v<<1] += lz[v];
  lz[v<<1|1] += lz[v];
  lz[v] = 0;
}

void upd(int x, int y, long long val, int l, int r, int v){
  if(r < x || y < l)
    return;
  if(x <= l && r <= y){
    T[v] += val*(r-l+1);
    lz[v] += val;
    return;
  }
  
  push(l, r, v);
  upd(x, y, val, l, mid(l, r), v<<1);
  upd(x, y, val, mid(l, r)+1, r, v<<1|1);
  
  T[v] = T[v<<1] + T[v<<1|1];
}

long long sum(int x, int y, int l, int r, int v){
  if(r < x || y < l)
    return 0;
  if(x <= l && r <= y)
    return T[v];
    
  push(l, r, v);
  return sum(x, y, l, mid(l, r), v<<1) + sum(x, y, mid(l, r)+1, r, v<<1|1);
}

struct interval{
  long long val;
  int l, r;
};

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++)
    scanf("%d", &a[i]);
  
  for(int i=1; i<=q; i++){
    int l, r;
    scanf("%d%d", &l, &r);
    Queries[l].push_back({r, i});
  }
  
  vector<interval> v;
  for(int i=n; i>=1; i--){
    interval cur = {a[i], i, i};
    while(!v.empty() && v.back().val < a[i]){
      interval temp = v.back();
      v.pop_back();
      
      upd(temp.l, temp.r, a[i]-temp.val, 1, n, 1);
      cur.r = max(cur.r, temp.r);
    }
    v.push_back(cur);
    
    for(auto [j, idx] : Queries[i])
      ans[idx] = sum(i, j, 1, n, 1);
  }
  
  for(int i=1; i<=q; i++)
    printf("%lld\n", ans[i]);
  
  return 0;
}
