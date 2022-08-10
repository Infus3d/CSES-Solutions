/*
 * Problem link : https://cses.fi/problemset/task/2189/
 * 
 * This problem requires a basic understanding of points, lines and cross products of vectors.
 * The following book will be a good place to start if you are not familiar with them:
 * https://cses.fi/book/book.pdf  (Chapter 29)
 * 
 * However, the following video tutorial by Errichto should also be enough to get you started
 * on cross products: https://www.youtube.com/watch?v=G9QTjWtK_TQ
 * 
 * The code below was adapted from Errichto's solution.
 * Runtime O(t)
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

int main(){
  int t;
  scanf("%d", &t);
  while(t--){
    Point p1, p2, p3;
    p1.read(); 
    p2.read(); 
    p3.read();
    long long _sign = p1.triangle(p2, p3);
    if(_sign < 0) puts("RIGHT");
    else if(_sign > 0) puts("LEFT");
    else puts("TOUCH");
  }
  return 0;
}
