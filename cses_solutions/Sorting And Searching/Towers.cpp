/*
 * Problem link : https://cses.fi/problemset/task/1073
 * 
 * The greedy idea is to always try to put the cube k
 * on top of the smallest cube bigger than k (as close to k
 * as possible). And if there are no such bigger element, we start
 * a new tower with k: tower-k (tower-k means a tower ending with k) 
 * That way, we ensure the fewest number of towers are present at 
 * any i using k[0...i] cubes, in order.
 * 
 * To see this more clearly, let's say that the smallest cube
 * bigger than k so far is u. Then we have 2 options:
 * -----> Place k on top of u, effectively turning tower-u into tower-k.
 *        When an element v (u < v and v < k) arrives later in the array,
 *        then we will need to either place it onto its own smallest tower
 *        bigger than v or start a new tower with v if there is no such bigger
 *        element. In either case, there will be 2 towers: tower-k and tower-v.
 * 
 * -----> We can choose to start a new tower with k and leave tower-u untouched.
 *        Then, when an element v (u < v && v < k) arrives later in the array,
 *        we can easily put it on top of tower-u. This would leave us with
 *        2 towers, just like in the 1st option: tower-k and tower-v.
 * 
 * Runtime O(n * logn) where logn accounts for finding the smallest element bigger
 * than k using binary search.
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n; scanf("%d", &n);
  vector<int> x;
  for(int i=0; i<n; i++){
    int k; scanf("%d", &k);
    
    //returns iterator to the smallest element in x that is bigger than k using b-search
    auto it = upper_bound(x.begin(), x.end(), k); 
    
    if(it == x.end()) //if there is no bigger element than k, then we start a new tower
      x.push_back(k);
    else
      *it = k; //element at an iterator can be accessed with *
  }
  printf("%d\n", (int)x.size());
  
  return 0;
}
