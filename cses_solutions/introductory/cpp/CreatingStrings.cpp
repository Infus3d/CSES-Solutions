/*
 * Problem link : https://cses.fi/problemset/task/1622
 * 
 * We can take advantage of the next_permutation functions from C++ STL.
 * When given an array/vector of integers, it 'permutes' the input onto the next
 * permutation. Special property of the function is that it only generates the
 * unique permutations of the provided input, which is exactly what we need.
 * We can also feed in a string into the function, it still generates all possible
 * unique permutations of it.
 * 
 * Here is a nice video editorial: https://www.youtube.com/watch?v=9iIbVMovBZ4
 * 
 * Runtime O(n!)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  string s;
  cin >> s;
  sort(s.begin(), s.end()); //first we need to sort the string so that the permutations start from lexicographically smallest
  
  vector<string> ans;
  //we use do-while because we also need to get the very first permutation - the string itself
  do{
    ans.push_back(s);
  } while(next_permutation(s.begin(), s.end()));
  
  cout << (int)ans.size() << '\n';
  for(string i : ans)
    cout << i << '\n';
  
  return 0;
}
