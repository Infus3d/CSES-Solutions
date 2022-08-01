/*
 * Problem link : https://cses.fi/problemset/task/2165
 * 
 * We can solve this famous problem with very short recursive method but I don't think
 * I'll get anything across by some text here if I were to explain it. There are nice
 * visual tutorials out there and the following is my favorite:
 * https://www.youtube.com/watch?v=rf6uf3jNjbo
 * 
 * Runtime (2^n)
 * */
#include "bits/stdc++.h"

using namespace std;

void towerOfHanoi(int n, int source, int intermediate, int destination){
  if(n == 0)
    return;
  
  towerOfHanoi(n-1, source, destination, intermediate); //first move top n-1 disks from source to intermediate using destination
  
  printf("%d %d\n", source, destination); //move the biggest disk from source to destination
  
  towerOfHanoi(n-1, intermediate, source, destination); //move top n-1 disks from intermediate to destination using source
}

int main(){
  int n;
  scanf("%d", &n);
  
  printf("%d\n", (1<<n)-1); //1<<n is 2^n
  towerOfHanoi(n, 1, 2, 3);
  
  return 0;
}
