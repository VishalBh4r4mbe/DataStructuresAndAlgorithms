#include <bits/stdc++.h>
using namespace std;
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

//<0  if p1-> p2 is cw     , = 0 collinear, >0 if ccw 
template <class F,class T>inline auto ccw (const Point<F> &p1, const Point<T> &p2){return p2^p1;}
template <class F,class T>inline auto ccw (const Point<F> &p1, const Point<T> &p2,const Point<T> &org){return (p2-org)^(p1-org);}
template <class F,class T>inline auto operator == (const Point<F> &p1, const Point<T> &p2){return p1.x==p2.x&&p1.y==p2.y;}
template <class F,class T> inline auto operator !=(const Point<F> &other,const Point<T> &h){return !(h==other);}
template <class F,class T>inline auto operator < (const Point<F> &p1, const Point<T> &p2){return p1.y<p2.y||(p1.y==p2.y)&&p1.x<p2.x;}
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
    Point<F> a, ab;
    Line(): a(),ab(){}
    Line(const Point<F>& a, const Point<F>& b, bool twoPoints = true): a(a), ab(twoPoints ? b - a : b) {}
    Line(const F& xa, const F& ya, const F& xb, const F& yb): a(xa, ya), ab(xb - xa, yb - ya) {}
    void swap(Line& other) { using std::swap; swap(a, other.a); swap(ab, other.ab); }
    template <class F1> explicit operator Line<F1> () const {return Line<F1>(Point<F1>(a), Point<F1>(ab), false); }
    template <class F1> Line& operator = (const Line<F1>& other) {a = other.a; ab = other.ab; return *this; }

    Point<F> b() const { return a + ab; }
    operator bool () const { return ab != Point<F>(); }
};
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

template <class F> using Polygon = vector<Point<F>>;
inline int prev(int i, int n) { return i == 0 ? n-1 : i-1; }
inline int next(int i, int n) { return i == n-1 ? 0 : i+1; }
template <class T> inline int sgn(const T& x) { return (T(0) < x) - (x < T(0)); }

template <class F>
F area(const Polygon<F>& poly) {
  int n = static_cast<int>(poly.size());
  F area = F(0);
  for (int i = 0; i < n; ++i)
    area += poly[i].x * (poly[next(i, n)].y - poly[prev(i, n)].y);
  return area/2;
}
template <class F>
Polygon<F> convexHull(Polygon<F> points) {
  sort(begin(points), end(points));
  Polygon<F> hull;
  hull.reserve(points.size() + 1);
  for (int phase = 0; phase < 2; ++phase) {
    auto start = hull.size();
    for (auto& point : points) {
      while (hull.size() >= start+2 &&
             ccw(point, hull.back(), hull[hull.size()-2]) <= 0)
        hull.pop_back();
      hull.push_back(point);
    }
    hull.pop_back();
    reverse(begin(points), end(points));
  }
  if (hull.size() == 2 && hull[0] == hull[1]) hull.pop_back();
  return hull;
}   
//If Simple    ....   If the polygin is convex then , compare ccw for any 2 adjacent points
template <class F> 
bool orientation(const Polygon<F>& poly) {
  int n = static_cast<int>(poly.size());
  int i = static_cast<int>(min_element(begin(poly), end(poly)) - begin(poly));
  return ccw(poly[prev(i, n)], poly[next(i, n)], poly[i]) > 0;
}
template <class F1, class F2>
int pointVsTriangle(const Point<F1>& point, const Polygon<F2>& triangle) {
  assert(triangle.size() == 3);
  int signs[3];
  for (int i = 0; i < 3; ++i)
    signs[i] = sgn(ccw(point, triangle[next(i, 3)], triangle[i]));
  if (signs[0] == signs[1] && signs[1] == signs[2]) return -1;
  for (int i = 0; i < 3; ++i) if (signs[i] * signs[next(i, 3)] == -1) return 1;
  return 0;
}
//point inclusion in a convex polygon <O(log(n))>
template <class F1, class F2>
int pointVsConvexPolygon(const Point<F1>& point, const Polygon<F2>& poly, int top) {
  if (point < poly[0] || point > poly[top]) return 1;
  auto orientation = ccw(point, poly[top], poly[0]);
  if (orientation == 0) {
    if (point == poly[0] || point == poly[top]) return 0;
    return top == 1 || top + 1 == poly.size() ? 0 : -1;
  } else if (orientation < 0) {
    auto itRight = lower_bound(begin(poly) + 1, begin(poly) + top, point);
    return sgn(ccw(itRight[0], point, itRight[-1]));
  } else {
    auto itLeft = upper_bound(poly.rbegin(), poly.rend() - top-1, point);
    return sgn(ccw(itLeft == poly.rbegin() ? poly[0] : itLeft[-1], point, itLeft[0]));
  }
}

template <class F1, class F2>
int pointVsPolygon(const Point<F1>& point, const Polygon<F2>& poly) {
  int n = static_cast<int>(poly.size()), windingNumber = 0;
  for (int i = 0; i < n; ++i) {
    if (point == poly[i]) return 0;
    int j = next(i, n);
    if (poly[i].y == point.y && poly[j].y == point.y) {
      if (min(poly[i].x, poly[j].x) <= point.x &&
          point.x <= max(poly[i].x, poly[j].x)) return 0;
    } else {
      bool below = poly[i].y < point.y;
      if (below != (poly[j].y < point.y)) {
        auto orientation = ccw(point, poly[j], poly[i]);
        if (orientation == 0) return 0;
        if (below == (orientation > 0)) windingNumber += below ? 1 : -1;
      }
    }
  }
  return windingNumber == 0 ? 1 : -1;
}


template <class F, class Function>
int extremeVertex(const Polygon<F>& poly, Function direction) {
  int n = static_cast<int>(poly.size()), left = 0, leftSgn;
  auto vertexCmp = [&poly, direction](int i, int j) {
    return sgn(ccw(direction(poly[j]), poly[j] - poly[i])); };
  auto isExtreme = [n, vertexCmp](int i, int& iSgn) {
    return (iSgn = vertexCmp(next(i, n), i)) >= 0 && vertexCmp(i, prev(i, n)) < 0; };
  for (int right = isExtreme(0, leftSgn) ? 1 : n; left + 1 < right;) {
    int middle = (left + right) / 2, middleSgn;
    if (isExtreme(middle, middleSgn)) return middle;
    if (leftSgn != middleSgn ? leftSgn < middleSgn
        : leftSgn == vertexCmp(left, middle)) right = middle;
    else left = middle, leftSgn = middleSgn;
  }
  return left;
}

template <class F1, class F2>
pair<int, int> tangentsConvex(const Point<F1>& point, const Polygon<F2>& poly) {
  return {
    extremeVertex(poly, [&point](const Point<F2>& q) { return q - point; }),
    extremeVertex(poly, [&point](const Point<F2>& q) { return point - q; })};
}


//ccw direction onli
//Polygon Stabbing
//if(orientation)reverse
template <class F1, class F2, class F3>
bool stabConvexPolygon(const Line<F1>& line, const Polygon<F2>& poly, Line<F3>& res) {
  assert(line);
  int right = extremeVertex(poly, [&line](const Point<F2>&) { return line.ab; });
  int left = extremeVertex(poly, [&line](const Point<F2>&) { return -line.ab; });
  auto vertexCmp = [&line](const Point<F2>& vertex) {
    return sgn(ccw(line.ab, vertex - line.a)); };
  int rightSgn = vertexCmp(poly[right]), leftSgn = vertexCmp(poly[left]);
  if (rightSgn < 0 || leftSgn > 0) return false;
  auto intersectChain = [&line, &poly, vertexCmp](int first, int last,
                                                  int firstSgn, Point<F3>& res) {
    int n = static_cast<int>(poly.size());
    while (next(first, n) != last) {
      int middle = (first + last + (first < last ? 0 : n)) / 2;
      if (middle >= n) middle -= n;
      if (vertexCmp(poly[middle]) == firstSgn) first = middle;
      else last = middle;
    }
    intersectLines<0, 0, 0, 0>(line, Line<F1>(poly[first], poly[last]), res);
  };
  intersectChain(left, right, leftSgn, res.a);
  intersectChain(right, left, rightSgn, res.ab);
  //res.ab = res.a;
  return true;
}


template <class F1, class F2, class F = distF<F1, F2>>
F stabPolygonLength(const Line<F1>& line, const Polygon<F2>& poly) {
  assert(line);
  F tSum = F(0);
  int n = static_cast<int>(poly.size());
  auto vertexSgn = [&line, &poly](int i) { return sgn(line.ab ^ (poly[i] - line.a)); };
  int prevSgn = vertexSgn(n - 1), iSgn = vertexSgn(0), nextSgn;
  for (int i = 0; i < n; ++i, prevSgn = iSgn, iSgn = nextSgn) {
    nextSgn = vertexSgn(next(i, n));
    if (iSgn == 0) {
      if (prevSgn == 0) {
        if (nextSgn != 0 && nextSgn == sgn((poly[i] - poly[prev(i, n)]) * line.ab))
          tSum += nextSgn * static_cast<F>((poly[i] - line.a) * line.ab) / abs(line.ab);
      } else {
        if ((nextSgn != 0 && nextSgn != prevSgn) ||
            (nextSgn == 0 && prevSgn == sgn((poly[next(i, n)] - poly[i]) * line.ab)))
          tSum -= prevSgn * static_cast<F>((poly[i] - line.a) * line.ab) / abs(line.ab);
      }
    } else if (nextSgn == -iSgn) {
      auto vect = poly[next(i, n)] - poly[i];
      tSum += nextSgn * static_cast<F>((poly[i] - line.a) ^ vect) / (line.ab ^ vect);
    }
  }
  return tSum * norm(line.ab);
}
template <class F>
F maxDist2(const Polygon<F>& poly) {
  int n = static_cast<int>(poly.size());
  F res = F(0);
  for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
    for (;; j = next(j, n)) {
      res = max(res, dist2(poly[i], poly[j]));
      if (ccw(poly[i+1] - poly[i], poly[next(j, n)] - poly[j]) >= 0) break;
    }
  return res;
}
//if the polygon is not convex, call ConvecHull;  
template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1)^(e2 - s2);
	if (d == 0) // if parallel
		return {(-((e1-s1)^(s2-s1)) == 0), P(0, 0)};
	auto p = ((e1-s1)^(e2-s1)), q = ((e2-s2)^(s1-s2));
	return {1, (s1 * p + e1 * q) / d};
}
 //Everything clockwise
typedef Point<long double> P;
vector<P> polygonCut(const vector<P>& poly, P s, P e) {
  if(ccw(s,e)<0)swap(s,e);
	vector<P> res;
	for(int i=0;i<(poly.size());i++) {
		P cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = ((e-s)^(cur-s)) < 0;
		if (side != ((e-s)^(prev-s)) < 0)
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side)
			res.push_back(cur);
	}
	return res;
}
 
int main(){
  
    Polygon<long double> poly;
    int n,m;
    cin>>n>>m;
    for(int i = 0; i < n; ++i){
      long double x,y;
      cin>>x>>y;
      poly.push_back(P(x,y));
    }
    Point<long double> s(0,2),e(1,0);
    
    auto ans = polygonCut(poly,s,e);
    for(auto x:ans){
      cout<<x;
      cout<<endl;
    }
    cout<<area(ans);
    //cout<<ccw(Point<double>(1,1),Point<double>(0,1));
    //if(!orientation(poly))reverse(poly.begin(),poly.end());
    
    //   cout<<fixed<<setprecision(20);
    //   for(int i=0;i<m;i++){
    //     double x1,y1,x2,y2;
    //     cin>>x1>>y1>>x2>>y2;
    //     Point<double> x(x1,y1),y(x2,y2);
    //     Line<double> cur (y,x);
    //     cout<<abs(stabPolygonLength(cur,poly))<<endl;
    //   }
}