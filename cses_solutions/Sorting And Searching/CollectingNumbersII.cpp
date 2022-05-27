/*
 * Problem link : https://cses.fi/problemset/task/2217
 * 
 * We continue to build upon the idea for the 1st version
 * of the problem. However in this version, we have to
 * update and print the answer m times, one for each query.
 * 
 * x[] :  ... x[a-1], x[a], x[a+1], ... , x[b-1], x[b], x[b+1], ...
 * 
 * Assume that we have the initial answer calculated for array x[] in 'ans'.
 * If we need to swap numbers at indices a and b then we would
 * only need to update the answer according to x[a] and x[b]. To be specific,
 * we will need to detect the change that happens to positions of (x[a]-1, x[a]),
 * (x[a], x[a]+1), (x[b]-1, x[b]), (x[b], x[b]+1) becase we calculated the answer
 * by checking if pos[x[i]] was smaller than pos[x[i-1]].
 * 
 * Now let's detect the change in one of them, (x[a]-1, x[a]) as the others follow
 * the same exact method. Let's also mark the new positions of the elements as newpos[]:
 * ------> pos[x[a]-1] < pos[x[a]] meaning they could be taken in the same 'swipe' or
 *         'round' before the change. Then after change (swap of x[a] and x[b]) there can
 *         be 2 possibilities:
 *         -------> newpos[x[a]-1] < newpos[x[a]] meaning they are still 'in-order' after change.
 *                  Then we need to update the ans by 0, as there is no change.
 *         -------> newpos[x[a]-1] > newpos[x[a]] meaning they can not be taken in the same 'swipe'
 *                  after change. So we need to increase the ans by 1.
 * 
 * ------> pos[x[a]-1] > pos[x[a]] meaning a new 'swipe' or 'round' is needed to take x[a] after
 *         x[a]-1 before the change. Then after change (swap of x[a] and x[b]) there can be 2
 *         possibilities:
 *         -------> newpos[x[a]-1] < newpos[x[a]] meaning they are 'in-order' after change. Then we need
 *                  to subtract 1 from the ans because we are making 1 less 'swipe' after change.
 *         -------> newpos[x[a]-1] > newpos[x[a]] meaning they are not 'in-order' even after the change.
 *                  As they were like this before the change too, we update the ans by 0.
 * 
 * We do the above for every single of those 4 pairs mentioned earlier.
 * However there is one last thing to keep in mind, and that is the case x[a] == x[b]-1 as we do not
 * want to double count the change that happens to this pair { (x[a], x[a]+1) and (x[b]-1, x[b]) are the
 * same in this context). To handle this, we just include a single if statement and calculate either of the
 * latter pairs.
 * 
 * Runtime O(n+m)
 * */
#include "bits/stdc++.h"

using namespace std;

int get(int a, int b){
  return (a > b ? 1 : 0);
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  
  vector<int> x(n+2), pos(n+2);
  for(int i=1; i<=n; i++){
    scanf("%d", &x[i]);
    pos[x[i]] = i;
  }
  pos[n+1] = n+1;
  
  int ans = 1;
  for(int i=2; i<=n; i++)
    ans += get(pos[i-1], pos[i]);
  
  while(m--){
    int a, b;
    scanf("%d%d", &a, &b);
    if(x[a] > x[b]) 
      swap(a, b);
    
    int oldPosA = pos[x[a]];
    int oldPosB = pos[x[b]];
    int newPosA = oldPosB;
    int newPosB = oldPosA;
    
    //these differences can be either 1, 0, or -1 depending on the change
    ans += get(pos[x[a]-1], newPosA) - get(pos[x[a]-1], oldPosA);
    ans += get(newPosB, pos[x[b]+1]) - get(oldPosB, pos[x[b]+1]);
    
    if(x[a] != x[b]-1){
      ans += get(newPosA, pos[x[a]+1]) - get(oldPosA, pos[x[a]+1]);
      ans += get(pos[x[b]-1], newPosB) - get(pos[x[b]-1], oldPosB);
    }
    else
      ans += get(newPosA, newPosB) - get(oldPosA, oldPosB);
    
    //we actually do the swapping
    pos[x[a]] = newPosA;
    pos[x[b]] = newPosB;
    swap(x[a], x[b]);
    
    printf("%d\n", ans);
  }
  
  return 0;
}
