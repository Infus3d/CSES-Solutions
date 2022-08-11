/*
 * Problem link : https://cses.fi/problemset/task/2192
 * 
 * This problem requires a basic understanding of points, lines and cross products of vectors.
 * The following book will be a good place to start if you are not familiar with them:
 * https://cses.fi/book/book.pdf  (Chapter 29)
 * 
 * However, the following video tutorial by Errichto should also be enough to get you started
 * on cross products: https://www.youtube.com/watch?v=G9QTjWtK_TQ
 * 
 * Since the given polygon is not self-intersecting, we can determine if a point is inside a polygon
 * by counting the intersections of segment (between the given point and an 'infinity' point) with 
 * polygon segments. If the count is divisible by 2, then the point is outisde the polygon, if not
 * it is inside a polygon.
 * 
 * To determine whether the point is on boundary, it is enough to go over all segments of the
 * polygon and check if the point lies on any of these segments/lines.
 * 
 * Please refer to the video tutorial above for better understanding.
 * 
 * Runtime O(n*m)
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
};

//Copy pasted from Problem 'Line Segment Intersection'
bool intersection(Point p1, Point p2, Point p3, Point p4){
  if((p2 - p1) * (p4 - p3) == 0){
    if(p1.triangle(p2, p3) != 0){
      return false;
    }
    for(int i=0; i<2; i++){
      if(max(p1.x, p2.x) < min(p3.x, p4.x) || max(p1.y, p2.y) < min(p3.y, p4.y)){
        return false;
      }
      swap(p1, p3);
      swap(p2, p4);
    }
    return true;
  }
  else{
    for(int i=0; i<2; i++){
      long long sign1 = p1.triangle(p2, p3);
      long long sign2 = p1.triangle(p2, p4);
      if((sign1 < 0 && sign2 < 0) || (sign1 > 0 && sign2 > 0)){
        return false;
      }
      swap(p1, p3);
      swap(p2, p4);
    }
    return true;
  }
}

//Checking intersection of the segment [p, inf] with segment [a, b] without actually needing the point inf
bool safe_intersection(Point p, Point a, Point b){
  if(a.x <= p.x && p.x < b.x && p.triangle(a, b) < 0LL)
    return true;
  if(b.x <= p.x && p.x < a.x && p.triangle(a, b) > 0LL)
    return true;
  return false;
}

//First check if they are collinear, and then check the bounding-boxes and see if they contain p
bool is_point_inside_segment(Point &a, Point &b, Point &p){
  if(a.triangle(b, p) != 0)
    return false;
  return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  vector<Point> polygon(n);
  for(Point &p : polygon)
    p.read();
  
  for(int i=0; i<m; i++){
    Point p; p.read();
    //~ Point inf = Point(p.x+1, (long long)3e9+1);
    
    bool on_boundary = false;
    int count = 0;
    for(int j=0; j<n; j++){
      Point &A = polygon[j], &B = polygon[(j+1)%n];
      if(is_point_inside_segment(A, B, p)){
        on_boundary = true;
        break;
      }
      //~ if(intersection(p, inf, A, B))
        //~ count++;
      
      if(safe_intersection(p, A, B))
        count++;
    }
    if(on_boundary) puts("BOUNDARY");
    else if(count % 2 == 0) puts("OUTSIDE");
    else puts("INSIDE");
  }
  
  return 0;
}
