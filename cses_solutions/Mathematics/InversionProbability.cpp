/*
 * Problem link : https://cses.fi/problemset/task/1728
 * 
 * We can calculate the expected inversion contribution of each pair (i, j) with i < j
 * and add them to get the total number of expected inversions thanks to linearity.
 * To calculate the probability of inversion for a pair (i, j), i < j we can first count the
 * number of possible/desired cases and divide that amount by total number of cases which is
 * simply r[i]*r[j].
 * We have 2 possible situtaions:
 * -----> If r[i] < r[j] we know that the number of desired cases a[i] > a[j] is (r[i] choose 2).
 *        Because a[i] has to be bigger than a[j] and the maximum it can get is r[i], so any value
 *        of a[j] should be strictly below a[i] and thus r[i].
 * -----> If r[i] >= r[j] the answer is (r[j] choose 2) + ((r[i] - r[j]) * r[j]). The first part
 *        is for when we fix a[i] to be r[j] at max. The second part basically means that beyond
 *        r[j], a[i] can get at most r[i] where for each of these values in between r[j] and r[i]
 *        a[j] is free to cheese any number between 1 and r[j].
 * 
 * Now that we know the desired cases for any pair (i, j) with i < j we can divide it by total possible
 * cases r[i] * r[j] and get the probability of a[i] > a[j]. This same probability will contribute only
 * 1 inversion to the total so we simply add the probability onto the total number of expected inversions.
 * 
 * Runtime O(n^2)
 * */
#include "bits/stdc++.h"

using namespace std;

int main(){
  int n;
  scanf("%d", &n);
  vector<int> r(n);
  for(int i=0; i<n; i++)
    scanf("%d", &r[i]);
  
  double ans = 0.0;
  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      int possibleCases = 0;
      if(r[i] < r[j])
        possibleCases = (r[i] * (r[i]-1)) / 2;
      else{
        possibleCases = (r[j] * (r[j]-1)) / 2;
        possibleCases += r[j] * (r[i] - r[j]);
      }
      
      int totalCases = r[i] * r[j];
      ans += (double)possibleCases / totalCases;
    }
  }
  printf("%.6lf\n", ans);
  
  return 0;
}
