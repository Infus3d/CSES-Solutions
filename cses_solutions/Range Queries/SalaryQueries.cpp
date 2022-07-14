/*
 * Problem link : https://cses.fi/problemset/task/1144
 * Prereq: 
 * BIT or Segment-tree
 * -----> https://cses.fi/book/book.pdf    (Chapter 9)
 * 
 * Let's assume that salaries are only upto 1e6 and that we can build a segment
 * or binary-indexed tree over it, for now.
 * The trees will contain the number of employees with certain amount of salary
 * for every possible salary in the input. When updating the salary of an employee
 * i with previous salary salary[i], to new_salary:
 * -----> We decrease the previous salary (salary[i]) count in the tree by 1 because
 *        there is 1 less employee with that salary now.
 * 
 * -----> Simply do salary[i] = new_salary.
 * 
 * -----> We increase the new salary (salary[i] again, but updated) count in the tree
 *        by 1 because there is 1 more employee with that salary.
 * 
 * To answer the query of the 2nd type, where we need to count the number of employees
 * with salary range [a, b], we simply output the sum of the range [a, b] from our tree.
 * 
 * Now since actual salaries can go up to 1e9 in the problem, we need to compress these
 * into smaller values but still achieve our purpose. The maximum mutually distinct number
 * of salaries in the input can be n initial salaries + q updating salaries = 4e5. So we
 * simply take these salaries, sort them, get rid of the duplicates and assign a new compressed
 * value to each salary: their indices in the sorted array.
 * 
 * To learn more about compression please check out:
 * https://cses.fi/book/book.pdf   (Section 9.4, Index Compression)
 * 
 * Runtime O((n+q)*log(n+q))
 * */
#include "bits/stdc++.h"

using namespace std;

const int N = 4e5+5;

int n, q, h[N], fen[N];
vector<int> vals, t;
vector<pair<char, pair<int, int>>> allqueries;

void add(int k, int val) {
  while (k < N) {
    fen[k] += val;
    k += k&-k;
  }
}

void upd(int x, int val){
  int idx = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
  add(idx, val);
}

int sum(int k) {
  int s = 0;
  while (k >= 1) {
    s += fen[k];
    k -= k&-k;
  }
  return s;
}

int query(int x){
  int idx = upper_bound(vals.begin(), vals.end(), x) - vals.begin();
  return sum(idx);
}

int main(){
  scanf("%d%d", &n, &q);
  for(int i=1; i<=n; i++){
    scanf("%d", &h[i]);
    vals.push_back(h[i]);
  }
  
  for(int i=1; i<=q; i++){
    char c;
    int a, b;
    scanf(" %c%d%d", &c, &a, &b);
    allqueries.push_back({c, {a, b}});
    if(c == '!')
      vals.push_back(b);
  }
  
  sort(vals.begin(), vals.end()); //sort for compression
  vals.erase(unique(vals.begin(), vals.end()), vals.end()); //delete duplicates
  
  for(int i=1; i<=n; i++)
    upd(h[i], 1);
  
  for(int i=0; i<q; i++){
    auto [a, b] = allqueries[i].second;
    if(allqueries[i].first == '!'){
      upd(h[a], -1);
      h[a] = b;
      upd(h[a], +1);
    }
    else
      printf("%d\n", query(b) - query(a-1));
  }
    
  
  return 0;
}
