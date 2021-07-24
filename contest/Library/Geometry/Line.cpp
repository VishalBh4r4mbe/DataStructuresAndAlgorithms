#include <bits/stdc++.h>
using namespace std;
template < class T > struct Point{
    T x, y;
    Point(){}
    Point(const T &x, const T &y):x(x), y(y){}
    void swap(Point &other){using std::swap; swap(x,other.x); swap(y,other.y);}
    template < class S > explicit operator Point<S> () const{
        return Point<S>(static_cast<S>(x),static_cast<S>(y));       
    }
    template <class S > Point& operator = (const Point &other){
        x = other.x; y = other.y; return *this;
    }
    template <class S > Point& operator += (const Point &other){
        x+=other.x; y+=other.y;return *this;
    }
    template <class S > Point& operator -= (const Point &other){
        x-=other.x; y-=other.y; return *this;
    }
    template <class S > Point& operator *= (const S &other){
        x*=other;y*=other;return *this;
    }
    template <class S > Point& operator /= (const S &other){
        x/=other;y/=other;return *this;
    }
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



template <class F> struct Line{
    Point<S> a, ab;
    Line(): a(),ab(){}
    Line(const Point<F>& a, const Point<F>& b, bool twoPoints = true): a(a), ab(twoPoints ? b - a : b) {}
    Line(const F& xa, const F& ya, const F& xb, const F& yb): a(xa, ya), ab(xb - xa, yb - ya) {}
    void swap(Line& other) { using std::swap; swap(a, other.a); swap(ab, other.ab); }
    template <class F1> explicit operator Line<F1> () const {return Line<F1>(Point<F1>(a), Point<F1>(ab), false); }
    template <class F1> Line& operator = (const Line<F1>& other) {a = other.a; ab = other.ab; return *this; }

    Point<F> b() const { return a + ab; }
    operator bool () const { return ab != Point<F>(); }
}
template <class F> void swap(Line<F>& lhs, Line<F>& rhs) { lhs.swap(rhs);}
template <class F1, class F2>bool onLine(const Point<F1>& point, const Line<F2>& line) {if (!line) return point == line.a;return ((point - line.a) ^ line.ab) == 0;}
//Assuming the line stores endpoints
template <class F1, class F2>bool onSegment(const Point<F1>& point, const Line<F2>& seg) {if (!seg) return point == seg.a;auto vecta = seg.a - point, vectb = seg.b() - point;return (vecta ^ vectb) == 0 && (vecta * vectb) <= 0;}

template <class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

template <class F1, class F2> distF<F1, F2> distLine(const Point<F1>& point, const Line<F2>& line) {
  if (!line) return dist(point, line.a);
  return abs((point - line.a) ^ line.ab) / norm(line.ab);
}
template <class F1, class F2>
distF<F1, F2> distSegment(const Point<F1>& point, const Line<F2>& seg) {
  if (((point - seg.a) * seg.ab) <= 0) return dist(point, seg.a);
  if (((point - seg.b()) * seg.ab) >= 0) return dist(point, seg.b());
  return distLine(point, seg);
}
template <class F1, class F2, class F3> void projection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
    res = line.a;
    if (line) res += line.ab * static_cast<F3>((point - line.a) * line.ab) / abs(line.ab);
}

template <class F1, class F2, class F3> void reflection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
    projection(point, line, res);
    res = 2 * res - point;
}
template <class F1, class F2, class F3> void closest(const Point<F1>& point, const Line<F2>& seg, Point<F3>& res) {
  if (((point - seg.a) * seg.ab) <= 0) res = seg.a;
  else if (((point - seg.b()) * seg.ab) >= 0) res = seg.b();
  else projection(point, seg, res);
}
template <int TYPE> struct EndpointChecker {};
template <> struct EndpointChecker<0> {  // no endpoint (ray)
  template <class F> bool operator ()(const F& a, const F& b) const { return true; }};
template <> struct EndpointChecker<1> {  // closed endpoint
  template <class F> bool operator ()(const F& a, const F& b) const { return a <= b; }};
template <> struct EndpointChecker<2> {  // open endpoint
  template <class F> bool operator ()(const F& a, const F& b) const { return a < b; }};

template <int LA, int LB, int RA, int RB, class F1, class F2, class F3>
bool intersectLines(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
  assert(lhs && rhs);
  auto s = lhs.ab ^ rhs.ab;
  if (s == 0) return false;
  auto ls = (rhs.a - lhs.a) ^ rhs.ab;
  auto rs = (rhs.a - lhs.a) ^ lhs.ab;
  if (s < 0) s = -s, ls = -ls, rs = -rs;
  bool intersect =
    EndpointChecker<LA>()(decltype(ls)(0), ls) && EndpointChecker<LB>()(ls, s) &&
    EndpointChecker<RA>()(decltype(rs)(0), rs) && EndpointChecker<RB>()(rs, s);
  if (intersect) res = lhs.a + lhs.ab * static_cast<F3>(ls) / s;
  return intersect;
}

template <class F1, class F2, class F3>
bool intersectClosedSegments(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
  return intersectLines<1, 1, 1, 1>(lhs, rhs, res);
}
template <class F1, class F2, class F3>
bool intersectSegments(const Line<F1>& lhs, const Line<F2>& rhs, Line<F3>& res) {
  auto s = lhs.ab ^ rhs.ab;
  auto ls = (rhs.a - lhs.a) ^ rhs.ab;
  if (s == 0) {
    if (ls != 0) return false;
    auto lhsa = lhs.a, lhsb = lhs.b();
    auto rhsa = rhs.a, rhsb = rhs.b();
    if (lhsa > lhsb) swap(lhsa, lhsb);
    if (rhsa > rhsb) swap(rhsa, rhsb);
    res = Line<F3>(max(lhsa, rhsa), min(lhsb, rhsb));
    return res.ab >= Point<F3>();
  }
  auto rs = (rhs.a - lhs.a) ^ lhs.ab;
  if (s < 0) s = -s, ls = -ls, rs = -rs;
  bool intersect = 0 <= ls && ls <= s && 0 <= rs && rs <= s;
  if (intersect)
    res = Line<F3>(lhs.a + lhs.ab * static_cast<F3>(ls) / s, Point<F3>());
  return intersect;
}