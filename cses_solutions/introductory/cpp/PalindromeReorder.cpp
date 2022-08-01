/*
 * Problem link : https://cses.fi/problemset/task/1755
 * 
 * We can classify palindromes into 2 classes: even-length (abba, acbbca) and odd-length (aba, accca).
 * You can see that in even length palindromes, whenever there is a character in the first half of the
 * string, there also must be a copy on its respective second half. In other words, if n - the length
 * of the string - is even, then the number each letters/characters must be divisible by 2, i.e. there
 * can not be any odd-number of characters.
 * Odd-length palindromes are almost like even-length but for the extra middle letter/character. So in
 * odd-length strings, for it to be a palindromes there must be exactly 1 odd-numbered letter and the
 * rest of the letters must be even-numbered.
 * Once we make sure that it is possible to construct a palindrome from the given string, we need to
 * actually print such palindrome. One of the ways to do so will be starting from even-numbered characters
 * and placing one such character at the front [0] and one at the back [n-1] of the string. Then we put
 * another (possibly the same character as before if there are remains of it) character at [1] and at [n-2]
 * positions. We can do this until we run out of even numbered characters. Now if n is odd, then there is
 * exactly one odd numbered character in the string. So we can simply situtate all copies of this letter
 * in the middle of the string.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h"

using namespace std;

char s[1000001]; //this is an array of character which is also a string in C

int main(){
  scanf("%s", s); //the type specifier for a string is '%s' and we pass the address of the first element of the array into scanf
                  //simply passing s is the same as passing &s[0] because s itself is a pointer to the array and s[0] is the actual character
  
  int n = strlen(s); //strlen(s) --> string length
  vector<int> cnt(26); //keeping count of every letter A-Z
  for(int i=0; i<n; i++)
    cnt[s[i]-'A']++; //we can do addition/subtraction on characters: 'A'-'A' = 0, 'C'-'A' = 2, 'Z'-'A' = 25, etc.
  
  int oddCount = 0;
  for(int i=0; i<26; i++)
    if(cnt[i] % 2 == 1)
      oddCount++;
  
  if(n % 2 != oddCount) //if n is odd then there must be exactly 1 letter with odd cnt, and if n is even then exactly 0.
    puts("NO SOLUTION");
  else{
    int p = 0;
    for(int i=0; i<26; i++){ //characters 'A'-'Z' represented by 0-25
      while(cnt[i] > 1){
        s[p] = s[n-p-1] = i+'A'; //putting character i at the front and back of the string
        cnt[i] -= 2; //decrease by 2 because we used 2 characters of i
        p++; //increasing the pointer
      }
      if(cnt[i] % 2 == 1) //then it is the center character of the palindrome
        s[n/2] = i+'A';
    }
    printf("%s\n", s);
  }
  return 0;
}
