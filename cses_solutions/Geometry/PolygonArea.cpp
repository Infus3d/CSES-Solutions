/*
 * Problem link : https://cses.fi/problemset/task/2191
 * 
 * This problem requires a basic understanding of points, lines and cross products of vectors.
 * The following book will be a good place to start if you are not familiar with them:
 * https://cses.fi/book/book.pdf  (Chapter 29)
 * 
 * However, the following video tutorial by Errichto should also be enough to get you started
 * on cross products: https://www.youtube.com/watch?v=G9QTjWtK_TQ
 * 
 * The area of a polygon is half of the absolute value of the sum of the cross-products of every
 * neighboring points in the polygon. Please find to the tutorial of the problem in the video above
 * to understand why.
 * 
 * Runtime O(n)
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
  int n;
  scanf("%d", &n);
  vector<Point> polygon(n);
  for(Point &p : polygon)
    p.read();
  
  long long twice_area = 0;
  for(int i=0; i<n; i++)
    twice_area += polygon[i] * polygon[(i+1)%n];
  
  printf("%lld\n", abs(twice_area));
    
  return 0;
}
