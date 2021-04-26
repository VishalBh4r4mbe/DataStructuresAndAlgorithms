/*
for different SegmentTree functions change the tree[v] wala line in Build and Update
and in a similar manner, use which Utility is suitable for the purpose of use
*/


#include <bits/stdc++.h>

using namespace std;
#define forn(i, n) for (ll i = 0; i < (ll)(n); ++i)
template <typename T> istream & operator>>(istream &in, vector<T> & v){for(auto &x: v){in>>x;} return in;}
  template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) {for (int i = 0; i < v.size(); ++i) { os << v[i]; if (i != v.size() - 1) os << " "; } os << "\n"; return os; } 

struct SegmentTree{
    int MAXN=1e9;
    int n;
    vector<long long int> tree;
    SegmentTree(int noOfElements){
        n=noOfElements;
        vector<long long int> x(4*n);
        tree = x;
    }
    void build(const vector<long long int>&a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } 
        else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            tree[v] = min(tree[2*v],tree[2*v+1]); 
        }
    }
    long long sumUtil(int l, int r){
      return sum(1,1,n,l,r);
    }
    long long int sum(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return 0;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return sum(v*2, tl, tm, l, min(r, tm))+sum(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
    long long int minUtil(int l , int r){
      return minST(1,1,n,l,r);
    }
    long long int minST(int v, int tl, int tr, int l, int r) {
        if (l > r) 
            return MAXN;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return min(minST(v*2, tl, tm, l, min(r, tm)),minST(v*2+1, tm+1, tr, max(l, tm+1), r));
    }
    void updateUtil(int position, int value) {
        update(1,1,n,position,value);
    }
    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } 
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, new_val);
            else
                update(v*2+1, tm+1, tr, pos, new_val);
            tree[v] = min(tree[v*2],tree[v*2+1]);
        }
    }
};


int main(){
  
}