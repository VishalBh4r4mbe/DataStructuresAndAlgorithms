#include <bits/stdc++.h>
using namespace std;
//2D point Definition.
template <class F>
struct Point {
  F x, y;
  Point() : x(0), y(0) {}
  Point(const F& x, const F& y) : x(x), y(y) {}

  void swap(Point& other) { using std::swap; swap(x, other.x); swap(y, other.y); }
  template <class F1> explicit operator Point<F1> () const {
    return Point<F1>(static_cast<F1>(x), static_cast<F1>(y)); }
  template <class F1> Point& operator = (const Point<F1>& other) {
    x = other.x; y = other.y; return *this; }
  template <class F1> Point& operator += (const Point<F1>& other) {
    x += other.x; y += other.y; return *this; }
  template <class F1> Point& operator -= (const Point<F1>& other) {
    x -= other.x; y -= other.y; return *this; }
  template <class F1> Point& operator *= (const F1& factor) {
    x *= factor; y *= factor; return *this; }
  template <class F1> Point& operator /= (const F1& factor) {
    x /= factor; y /= factor; return *this; }
};
template <class F> istream& operator >> (istream& is, Point<F>& point) {
  return is >> point.x >> point.y; }
template <class F> ostream& operator << (ostream& os, const Point<F>& point) {
  return os << point.x << ' ' << point.y; }

template <class F> void swap(Point<F>& lhs, Point<F>& rhs) { lhs.swap(rhs); }


template <class F> inline auto operator - (const Point<F>& point){ return Point<F>(-point.x, -point.y); }
template <class F,class T>inline auto operator + (const Point<F> &p1, const Point<T> &p2){return Point<F>(p1.x+p2.x, p1.y+p2.y);}
template <class F,class T>inline auto operator - (const Point<F> &p1, const Point<T> &p2){return Point<F>(p1.x-p2.x, p1.y-p2.y);}
template <class F,class T>inline auto operator * (const F &p1, const Point<T> &p2){return Point<T>(p1*p2.x, p1*p2.y);}
template <class F,class T>inline auto operator * (const Point<F> &p1, const T &p2){return Point<F>(p1.x*p2, p1.y*p2);}
template <class F,class T>inline auto operator / (const Point<F> &p1, const T &p2){return Point<F>(p1.x/p2, p1.y/p2);}
template <class F,class T>inline auto operator * (const Point<F> &p1, const Point<T> &p2){return p1.x*p2.x + p1.y*p2.y;}
template <class F,class T>inline auto operator ^ (const Point<F> &p1, const Point<T> &p2){return p1.x*p2.y-p2.x*p1.y;}

//<0  if p1-> p2 is ccw     , = 0 collinear, >0 if cw 
template <class F,class T>inline auto ccw (const Point<F> &p1, const Point<T> &p2){return p2^p1;}
template <class F,class T>inline auto ccw (const Point<F> &p1, const Point<T> &p2,const Point<T> &org){return (p1-org)^(p2-org);}
template <class F,class T>inline auto operator == (const Point<F> &p1, const Point<T> &p2){return p1.x==p2.x&&p1.y==p2.y;}
template <class F,class T> inline auto operator !=(const Point<F> &other,const Point<T> &h){return !(h==other);}
template <class F,class T>inline auto operator < (const Point<F> &p1, const Point<T> &p2){return p1.x<p2.x||(p1.x==p2.x)&&p1.y<p2.y;}
template <class F,class T>inline auto operator > (const Point<F> &p1, const Point<T> &p2){return p2<p1;}
template <class F,class T>inline auto operator <= (const Point<F> &p1, const Point<T> &p2){return !(p1>p2);}
template <class F,class T>inline auto operator >= (const Point<F> &p1, const Point<T>& p2){return !(p1<p2);}

//Angle and rotations;
//ccw measures
template <class S> inline auto angle(const Point<S> &p){return atan2(p.y,p.x);} //radians
template <class S,class T> inline auto angle(const Point<S> &p1, const Point<T> &p2){return atan2(p1^p2,p1*p2);}
template <class S,class T,class F> inline auto angle(const Point<S> &p1, const Point<T> &p2,const Point<F> org){return angle(p1-org,p2-org);}
template <class S,class T ,class F> inline auto rotate(const Point<S> &p1,const T angleSin, const F angleCos){return Point<S>(angleCos*p1.x - angleSin*p1.y,angleSin*p1.x + angleCos*p1.y);}
template <class S , class T> inline auto rotate(const Point<S> &p , T angle){return rotate(p,sin(angle),cos(angle));}
template <class S, class T,class F> inline auto rotate(const Point<S> &p,const T angle, const Point<F> org){return org + rotate(p-org,angle);}
template <class S> inline auto perp(const Point<S> &p){return Point<S>(-p.y,p.x);}


//Distances
template <class S> inline auto abs(const Point<S> &p){return p*p;} 
template <class S> inline auto norm(const Point<S> &p){return sqrt(abs(p));}
template <class S,class T> inline auto dist(const Point<S> &p, const Point<T> &p2){return(norm(p-p2));}
template <class S,class T> inline auto dist2(const Point<S> &p, const Point<T> &p2){return(abs(p-p2));}
template <class S,class T> inline auto bisector(const Point<S> &p, const Point<T> &p2){return (p*norm(p2)+p2*norm(p));}
template <class F>
struct AngleCompare {
  const Point<F> origin;
  const bool zero;

  AngleCompare(const Point<F>& origin = Point<F>())
    : origin(origin), zero(origin == Point<F>()) {}

  template <class F1, class F2>
  bool operator () (const Point<F1>& lhs, const Point<F2>& rhs) const {
    return zero ? ccw(lhs, rhs) < 0 : ccw(lhs, rhs, origin) < 0;
  }
};

template <class Iterator, class F>
void sortByAngle(Iterator first, Iterator last, const Point<F>& origin) {
  first = partition(first, last, [&origin](const decltype(*first)& point) {
    return point == origin; });
  auto pivot = partition(first, last, [&origin](const decltype(*first)& point) {
    return point > origin; });
  AngleCompare<F> acmp(origin);
  sort(first, pivot, acmp);
  sort(pivot, last, acmp);
}
int main(){
    vector<Point<int>> arr;
    int n;
    cin>>n;
    for(int i = 0; i < n;i++){
        int x,y;
        cin>>x>>y;
        arr.push_back(Point<int>(x,y));
    }
    sortByAngle(arr.begin(), arr.end(),Point<int>(0,0));
    for(auto x:arr){
        cout<<x<<endl;
    }
    //cout<<atan2(3,4)<<endl;
    //cout<<bisector(hi,Point<int>(0,5));
}
