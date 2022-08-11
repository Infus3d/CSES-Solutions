/*
 * Problem link : https://cses.fi/problemset/task/2195
 * 
 * This problem requires a basic understanding of points, lines and cross products of vectors.
 * The following book will be a good place to start if you are not familiar with them:
 * https://cses.fi/book/book.pdf  (Chapter 29)
 * 
 * However, the following video tutorial by Errichto should also be enough to get you started
 * on cross products: https://www.youtube.com/watch?v=G9QTjWtK_TQ
 * 
 * This is probably the most classical and beautiful problem in CP Geometry and there are many
 * ways of finding the convex hull of the points. Please refer to the video tutorial above for 
 * for n*log(n) solution.
 * 
 * Runtime O(n*log(n)) because of sorting
 * */
#include "bits/stdc++.h"

using namespace std;

struct Point{
  long long x, y;
  Point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {};
  void read(){
    scanf("%lld%lld", &x, &y);
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
  //here we use the special operator '<' that is defined for pair objects. It first checks for x values, then if x's are equal checks for y values
  bool operator <(const Point &b) const {
    return make_pair(x, y) < make_pair(b.x, b.y);
  }
};

int main(){
  int n;
  scanf("%d", &n);
  vector<Point> points(n);
  for(Point &p : points)
    p.read();
  
  sort(points.begin(), points.end());
  vector<Point> hull;
  for(int rep=0; rep<2; rep++){
    const int S = hull.size();
    for(Point &C : points){
      while((int)hull.size() >= S + 2){
        Point A = hull.end()[-2];
        Point B = hull.end()[-1];
        if(A.triangle(B, C) <= 0) break; //point C makes a convex angle with points B and A (B in the middle)
        hull.pop_back(); //the angle (A, B, C) is concave so we pop it from stack
      }
      hull.push_back(C); //now we can assume that either C makes a convex angle with last 2 points in the stack or the stack size is < 2
    }
    hull.pop_back(); //remove the last point to avoid double counting on the way back
    reverse(points.begin(), points.end()); //we reverse to get the 'bottom-half' of the convex hull
  }
  
  printf("%d\n", (int)hull.size());
  for(Point &p : hull)
    printf("%lld %lld\n", p.x, p.y);
  
  return 0;
}
