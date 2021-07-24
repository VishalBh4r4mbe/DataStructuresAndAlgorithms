#include <bits/stdc++.h>
using namespace std;
typedef long long int  ll;
const long long int is_query = -(1LL<<62);

class line{
    public:
    long long int m, b;
    mutable function<const line*()> succ;
    bool operator<(const line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const line* s = succ();
        if (!s) return 0;
        long long int x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct CHT : public multiset<line> { // will maintain upper hull for maximum
    const long long int inf = LLONG_MAX;
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;

		/* compare two lines by slope, make sure denominator is not 0 */
        long long int v1 = (x->b - y->b);
        if (y->m == x->m) v1 = x->b > y->b ? inf : -inf;
        else v1 /= (y->m - x->m);
        long long int v2 = (y->b - z->b);
        if (z->m == y->m) v2 = y->b > z->b ? inf : -inf;
        else v2 /= (z->m - y->m);
        return v1 >= v2;
    }
    void insert_line(long long int m, long long int b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    long long int eval(long long int x) {
        auto l = *lower_bound((line) { x, is_query });
        return l.m * x + l.b;
    }
};




int main(){
    CHT cht;
    cht.insert_line(-1,4);
    cht.insert_line(0,5);
    cht.insert_line(1,2);
    cout<<cht.eval(1);

}