/*
 * Problem link : https://cses.fi/problemset/task/1069
 * 
 * We keep a counter 'cnt' that keeps track of current size the repetition.
 * In the given string, on every index i with 0 < i < n we increase cnt by
 * 1 if string[i] == string[i-1] or we set it to 1 if they are not equal.
 * To get the maximum of length of such repetitions we just take maximum
 * of cnt with current answer on every iteration i.
 * 
 * The code below uses cin/cout of C++ instead of scanf/printf of C because
 * we can not scan a 'string' object with C methods.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  //the following 2 function calls are needed to make cin/cout of C++ as fast as scanf/printf of C
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  string s;
  cin >> s; //scan in the input string
  int cnt = 0, ans = 0;
  for(int i=0; i<(int)s.length(); i++){ //we cast s.length() to (int) to stop compiler from complaining
    if(i == 0 || s[i] != s[i-1]) //if it is the very first character or a new charactor that is not the same as previous character
      cnt = 1;
    else //if the previous and current character are the same
      cnt++;
    
    ans = max(ans, cnt); //take maximum everytime we update cnt
  }
  cout << ans << endl; //endl --> end line
  
  return 0;
}
