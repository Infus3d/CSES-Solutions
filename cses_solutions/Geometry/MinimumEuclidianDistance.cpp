/*
 * Problem link : https://cses.fi/problemset/task/2194
 * 
 * This is a well known problem in Computational Geometry and there are 2 efficient
 * solutions to it as of yet: one with divide and conquer approach and the other uses
 * sweep-line technique.
 * 
 * Both are O(n*log(n)) time and both are quite tedious to implement. Thankfully, the following
 * blog post author came up with a nice implementation of the sweep-line method:
 * https://codeforces.com/blog/entry/58747
 * 
 * To understand the solution, please refer to the following link:
 * https://www.topcoder.com/thrive/articles/Line%20Sweep%20Algorithms  (Closest Pair)
 * 
 * Runtime O(n*log(n))
 * */
#include "bits/stdc++.h"

using namespace std;

//copy pasted from previous problem solutions
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
  set<pair<long long, long long>> setik;
  
  int l = 0;
  unsigned long long best_dist = 8e18; //we have to take unsigned long long because the square of the distance can go upto 8e18
  for(int r=0; r<n; r++){
    long long d = ceil(sqrt(best_dist));
    while(l < n && (points[r].x - points[l].x) >= d){
      setik.erase({points[l].y, points[l].x});
      l++;
    }
    
    auto it1 = setik.lower_bound({points[r].y - d, points[r].x});
    auto it2 = setik.upper_bound({points[r].y + d, points[r].x});
    for(auto it = it1; it != it2; it++){
      unsigned long long dx = abs(points[r].x - (it->second));
      unsigned long long dy = abs(points[r].y - (it->first));
      best_dist = min(best_dist, (dx * dx) + (dy * dy));
    }
    setik.insert({points[r].y, points[r].x});
  }
  
  printf("%llu\n", best_dist);
  
  return 0;
}
