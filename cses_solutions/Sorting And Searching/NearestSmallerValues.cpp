/*
 * Problem link : https://cses.fi/problemset/task/1645
 * 
 * We can maintain a stack that contains the smallest numbers to
 * the left of i. At each i we pop from the stack the elements
 * that are not smaller that x[i]. This helps 'clean' the stack
 * from the unnecessary elements as x[i] is clearly the better
 * candidate for the rest of the iteration [i+1...n). After either
 * stack is empty or has it's top element smaller than x[i], we push
 * x[i] to the stack (Please take some time to understand why the
 * elements in the stack are in strictly increasing order).
 * If the stack was empty before push, then the answer for i is 0. If not,
 * the answer would be the topmost element of the stack.
 * 
 * Since we insert every element exactly once and pop each element at most
 * once, the overall runtime is O(n).
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  
  vector<int> x(n), ans(n, 0);
  for(int i=0; i<n; i++)
    scanf("%d", &x[i]);
  
  stack<int> S;
  for(int i=0; i<n; i++){
    while(!S.empty() && x[S.top()] >= x[i])
      S.pop();
    
    if(!S.empty())
      ans[i] = S.top()+1;
    
    S.push(i);
  }
  
  for(int i=0; i<n; i++)
    printf("%d ", ans[i]);
  puts("");
  
  return 0;
}
