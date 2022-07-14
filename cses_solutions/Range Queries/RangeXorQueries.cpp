/*
 * Problem link : https://cses.fi/problemset/task/1650
 * 
 * The problem can definitely be solved with a segment tree where
 * transition between the parent node and its 2 children is like
 * T[parent] = T[child1] ^ T[child2]
 * ----> The character '^' is the xor operator
 * 
 * However there are special properties of xor that makes segment trees
 * reduntant.
 * Xor is associative ---> a ^ (b ^ c) = (a ^ b) ^ c
 * Xor is commutative ---> a ^ b = b ^ a
 * Xor of the value with itself is 0 ----> a ^ a = 0
 * Xor of any integer with 0 is itself ----> a ^ 0 = a
 * 
 * Now, combining all these lets us understand: a ^ b ^ a = b
 *
 * The properties above hints that we can take xor's of the range just like we did with sums!
 * That is, if we want xor of the range [a, b] we just need (xor[1, b] ^ xor[1, a-1]). Because:
 * 
 * xor[1, b]   : xor[1, 2, 3, ... , a-1, a, a+1, ..., b-1, b]
 * xor[1, a-1] : xor[1, 2, 3, ... , a-1]
 * 
 * Taking xor of the intervals nullifies the range [1, a-1] and leaves us with only [a, b].
 * We can calculate the prefix-xors before all queries and answer them each in O(1)
 * 
 * Runtime O(n + q)
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 2e5+1;

int n, q, pref[N];

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%d", &pref[i]);
    pref[i] ^= pref[i-1];
  }
  
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", (pref[b] ^ pref[a-1]));
  }
  return 0;
}
