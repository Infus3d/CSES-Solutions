#include "bits/stdc++.h"

using namespace std;

int main(){
  int q; 
  scanf("%d", &q);
  while(q--){
    int n, k;
    scanf("%d%d", &n, &k);
    int prev = 0, deg = 1, st = 1;
    while(k > 0){
      int cur = n % 2;
      int half = n/2 + (prev & cur);
      if(k <= half){
        if(!prev) st += deg;
        printf("%d\n", st+((k-1)*deg*2));
        break;
      }
      k -= half;
      n -= half;
      if(prev == 1)
        st += deg;
      prev = (prev ^ cur);
      deg *= 2;
    }
  }
  
  return 0;
}
