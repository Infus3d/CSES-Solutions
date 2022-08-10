/*
 * Problem link : https://cses.fi/problemset/task/2190
 * 
 * This problem requires a basic understanding of points, lines and cross products of vectors.
 * The following book will be a good place to start if you are not familiar with them:
 * https://cses.fi/book/book.pdf  (Chapter 29)
 * 
 * However, the following video tutorial by Errichto should also give you enough information
 * about cross products: https://www.youtube.com/watch?v=G9QTjWtK_TQ
 * 
 * The code below was adapted from Errichto's solution.
 * Runtime O(t) although the constant is pretty high
 * */
#include "bits/stdc++.h"

using namespace std;

struct Point{
  int x, y;
  Point(int _x = 0, int _y = 0) : x(_x), y(_y) {};
  void read(){
    scanf("%d%d", &x, &y);
  }
  Point operator -(const Point &b) const {
    return Point(x - b.x, y - b.y);
  }
  void operator -=(const Point &b){
    x -= b.x;
    y -= b.y;
  }
  long long operator *(const Point &b) const {
    return (long long)x * b.y - (long long)y * b.x;
  }
  long long triangle(const Point &b, const Point &c) const {
    return (b - *this) * (c - *this);
  }
};

void solve_testcase(){
  Point p1, p2, p3, p4;
  p1.read(), p2.read();
  p3.read(), p4.read();
  if((p2 - p1) * (p4 - p3) == 0){
    if(p1.triangle(p2, p3) != 0){
      puts("NO");
      return;
    }
    for(int i=0; i<2; i++){
      if(max(p1.x, p2.x) < min(p3.x, p4.x) || max(p1.y, p2.y) < min(p3.y, p4.y)){
        puts("NO");
        return;
      }
      swap(p1, p3);
      swap(p2, p4);
    }
    puts("YES");
  }
  else{
    for(int i=0; i<2; i++){
      long long sign1 = p1.triangle(p2, p3);
      long long sign2 = p1.triangle(p2, p4);
      if((sign1 < 0 && sign2 < 0) || (sign1 > 0 && sign2 > 0)){
        puts("NO");
        return;
      }
      swap(p1, p3);
      swap(p2, p4);
    }
    puts("YES");
  }
}

int main(){
  int testcase;
  scanf("%d", &testcase);
  while(testcase--){
    solve_testcase();
  }
  return 0;
}
