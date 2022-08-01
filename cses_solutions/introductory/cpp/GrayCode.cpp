/*
 * Problem link : https://cses.fi/problemset/task/2205
 * 
 * Let's start from the smallest and build our way up.
 * Gray Code for n = 1:
 * 0
 * 1
 * 
 * Gray Code for n = 2 is, 0 appended to the front of gray code for n = 1 followed by
 * 1 appended to the front of gray code for n = 1 but backwards:
 * 00   //0 + 0
 * 01   //0 + 1
 * 11   //1 + 1
 * 10   //1 + 0
 * 
 * Same thing with n = 3:
 * 000  //0 + 00
 * 001  //0 + 01
 * 011  //0 + 11
 * 010  //0 + 10
 * 110  //1 + 10
 * 111  //1 + 11
 * 101  //1 + 01
 * 100  //1 + 00
 * 
 * So just start with the base case of {"0", "1"} and calculate n-length Gray Code gradually.
 * 
 * Runtime O(2^n * n)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  //the following 2 function calls are necessary to make cin/cout as fast as scanf/printf
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;
  
  vector<string> code;
  code.push_back("0"); //gray code
  code.push_back("1"); //for n = 1
  
  for(int i=1; i<n; i++){
    vector<string> temp;
    for(int j=0; j<(int)code.size(); j++) //forwards of previous gray code with 0 appended to the front
      temp.push_back("0" + code[j]);
    
    for(int j=(int)code.size()-1; j>=0; j--) //backwards of previous gray code with 1 appended to the front
      temp.push_back("1" + code[j]);
    
    code = temp; //don't forget to 'save' it
  }
  for(string i : code)
    cout << i << '\n';
  
  return 0;
}
