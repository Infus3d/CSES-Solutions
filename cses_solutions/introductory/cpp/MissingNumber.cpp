/*
 * Problem link : https://cses.fi/problemset/task/1083
 * 
 * We can maintain a visited[] array where visited[i] is 1 if the number i
 * is among the given numbers and visited[i] is 0 otherwise. So when scanning
 * the numbers we can simply mark that number as 'visited' and later go through
 * this array and detect a single unvisited number - the missing number.
 * 
 * In c++, vectors are seen as almost equivalent of an actual array.
 * Many competitive programmers use vectors instead of static arrays because they are very flexible
 * and easy to understand as they have an 'object' form. Below code also uses a vector.
 * 
 * Runtime O(n)
 * */
#include "bits/stdc++.h" //superheader that inclues almost all useful libraries for CP

using namespace std; //not necessary but makes lives easier

int main(){
 int n;
 scanf("%d", &n); //we scan the size of the input array with format specifier of int -> "%d" and by passing the address of n with &n
 
 //initialize a vector of integers with size n+1 because it is 0-indexed and we need to access the index n. Initially, all elements of the vector are 0.
 vector<int> visited(n+1); 
 for(int i=0; i<n-1; i++){ //we scan n-1 more integers
   int a;
   scanf("%d", &a); //scan the number
   visited[a] = 1; //mark the number as 'visited'
 }
 
 for(int i=1; i<=n; i++){
   if(visited[i] == 0){ //then we have found the missing number
     printf("%d\n", i); //"%d" is the format specifier of integers and "\n" is a newline character
   }
 }
 
 return 0;
}
