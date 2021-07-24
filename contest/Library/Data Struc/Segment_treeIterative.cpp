#include<bits/stdc++.h>
using namespace std;

class SegmentTree{
    public:
    vector<long long int> tree;
    SegmentTree(int n){
        this->n = n;
        tree.resize(2*n,0);
    }
    SegmentTree(vector<long long int> &x){
        this->n=x.size();
        tree.resize(2*n,0);
        for(int i=n;i<2*n;i++)tree[i] = x[i-n];
        for (int i = n - 1; i > 0; --i) tree[i] = max(tree[i<<1] , tree[i<<1|1]);
    }
    void build(vector<long long int> &x){
        for(int i=n;i<2*n;i++)tree[i] = x[i-n];
        for (int i = n - 1; i > 0; --i) tree[i] = max(tree[i<<1] , tree[i<<1|1]);
    }
    void set(int p, int value) {for (tree[p += n] = value; p > 1; p >>= 1) tree[p>>1] = max(tree[p] , tree[p^1]);}
    void add(int p, int value){for (tree[p += n] += value; p > 1; p >>= 1) tree[p>>1] = max(tree[p] , tree[p^1]);}
    // all on interval [l, r)
    int query(int l, int r) {long long int res = 0;for (l += n, r += n; l < r; l >>= 1, r >>= 1) {if (l&1) res = max(res,tree[l++]);if (r&1) res = max(res,tree[--r]);}return res;}
    // void prangeAdd(int l,int r, int value) {for (l += n, r += n; l < r; l >>= 1, r >>= 1) {if (l&1) tree[l++] += value;if (r&1) tree[--r] += value;}}       //Use to see the increase for a particulare element
    // int pQuery(int l){long long int res = 0;for (l += n;l > 0; l >>= 1) res += tree[l];return res;}

};

int main(){
    vector<int> x{0,0,0,0,0,0,0};
    SegmentTree seg(x);
    //seg.set(2,0);
    seg.prangeAdd(2,4,2);
    seg.prangeAdd(2,6,4);
    cout<<seg.pQuery(4);
}