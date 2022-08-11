/*
 * Problem link : https://cses.fi/problemset/task/2193
 * 
 * This problem requires a basic understanding of points, lines and cross products of vectors.
 * The following book will be a good place to start if you are not familiar with them:
 * https://cses.fi/book/book.pdf  (Chapter 29)
 * 
 * However, the following video tutorial by Errichto should also be enough to get you started
 * on cross products: https://www.youtube.com/watch?v=G9QTjWtK_TQ
 * 
 * It is not hard to see that the number of lattice ponits on one segment [i, j] of the polygon
 * is the greatest common divisor of two quantities abs(i.x - j.x), abs(i.y - j.y). The video
 * provides the needed insight on this. Given this, the total number of lattice points on the
 * boundary of the polygon will simply be the sum of such points over all segments.
 * 
 * From Pick's theorem (https://en.wikipedia.org/wiki/Pick%27s_theorem) we know that the number
 * of lattice points inside the polygon equals (area - boundary_lattice_points/2 + 1). We already
 * know the value of bounary_lattice_points and we also know how to calculate the area of the
 * polygon from earlier problems in CSES problemset.
 * 
 * Please refer to the video tutorial above for better understanding.
 * 
 * Runtime O(n)
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

int main(){
  int n;
  scanf("%d", &n);
  vector<Point> polygon(n);
  for(Point &p : polygon)
    p.read();
  
  long long boundary = 0;
  for(int i=0; i<n; i++){
    Point diff = polygon[i] - polygon[(i+1)%n];
    boundary += __gcd(abs(diff.x), abs(diff.y));
  }
  
  long long twice_area = 0;
  for(int i=0; i<n; i++)
    twice_area += polygon[i] * polygon[(i+1)%n];
  
  long long inside = (abs(twice_area) - boundary + 2) / 2LL;
  printf("%lld %lld\n", inside, boundary);
  
  return 0;
}
