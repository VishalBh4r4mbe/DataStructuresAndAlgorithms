/*
for different SegmentTree functions change the tree[v] wala line in Build and Update
and in a similar manner, use which Utility is suitable for the purpose of use
*/

#include <bits/stdc++.h>

using namespace std;
#define ll long long int
#define forn(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define vi vector<long long int>
template <typename T> istream & operator>>(istream &in, vector<T> & v){for(auto &x: v){in>>x;} return in;}
  template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) {for (int i = 0; i < v.size(); ++i) { os << v[i]; if (i != v.size() - 1) os << " "; } os << "\n"; return os; } 

struct LazySegmentTreeMin{
    int MAXN=1e9;
    int n;
    vector<long long int> tree;
    vector<long long int> lazyUpdate;
    vector<bool> shouldUpdate;
    LazySegmentTreeMin(int noOfElements){
        n=noOfElements;
        tree.assign(4*n,0);
        lazyUpdate.assign(4*n,0);
        shouldUpdate.assign(4*n,false);
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
    void propagate(int node, int L, int R)
	{
		if(L != R)
		{
			shouldUpdate[node*2] = true;
			shouldUpdate[node*2 + 1] = true;
			lazyUpdate[node*2] += lazyUpdate[node];
			lazyUpdate[node*2 + 1] += lazyUpdate[node]; 
		}
		tree[node] += lazyUpdate[node];
		lazyUpdate[node] = 0;
		shouldUpdate[node] = false;
	}


    long long int minST(int node, int L, int R, int i, int j)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return MAXN;
		if(i<=L && R<=j)return tree[node];
		int M = (L + R)/2;
		long long int left=minST(node*2, L, M, i, j);
		long long int right=minST(node*2 + 1, M + 1, R, i, j);
		return min(left,right);
	}
    
    void Update(int node, int L, int R, int i, int j, int mn)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return;
		if(i<=L && R<=j)
		{
			shouldUpdate[node] = 1;
			lazyUpdate[node] = mn;
			propagate(node, L, R);
			return;
		}
		int M = (L + R)/2;
		Update(node*2, L, M, i, j, mn);
		Update(node*2 + 1, M + 1, R, i, j, mn);
		tree[node]=min(tree[node*2], tree[node*2 + 1]);
	}
    void updateUtil(int l,int r, int value) {
        Update(1,1,n,l,r,value);
    }
    long long int minUtil(int l , int r){
      return minST(1,1,n,l,r);
    }
};
struct LazySegmentTreeMax{
    int MINN=-1*1e9;
    int n;
    vector<long long int> tree;
    vector<long long int> lazyUpdate;
    vector<bool> shouldUpdate;
    LazySegmentTreeMax(int noOfElements){
        n=noOfElements;
        tree.assign(4*n,0);
        lazyUpdate.assign(4*n,0);
        shouldUpdate.assign(4*n,false);
    }
    
    void build(const vector<long long int>&a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } 
        else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            tree[v] = max(tree[2*v],tree[2*v+1]); 
        }
    }
    void propagate(int node, int l, int r)
	{
		if(l != r)
		{
			shouldUpdate[node*2] = true;
			shouldUpdate[node*2 + 1] = true;
			lazyUpdate[node*2] += lazyUpdate[node];
			lazyUpdate[node*2 + 1] += lazyUpdate[node]; 
		}
		tree[node] += lazyUpdate[node];
		lazyUpdate[node] = 0;
		shouldUpdate[node] = false;
	}

    
    long long int maxST(int node, int L, int R, int i, int j)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return MINN;
		if(i<=L && R<=j)return tree[node];
		int M = (L + R)/2;
		long long int left=maxST(node*2, L, M, i, j);
		long long int right=maxST(node*2 + 1, M + 1, R, i, j);
		return max(left,right);
	}
    
    void Update(int node, int L, int R, int i, int j, int mn)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return;
		if(i<=L && R<=j)
		{
			shouldUpdate[node] = 1;
			lazyUpdate[node] = mn;
			propagate(node, L, R);
			return;
		}
		int M = (L + R)/2;
		Update(node*2, L, M, i, j, mn);
		Update(node*2 + 1, M + 1, R, i, j, mn);
		tree[node]=max(tree[node*2], tree[node*2 + 1]);
	}
    void updateUtil(int l,int r, int value) {
        Update(1,1,n,l,r,value);
    }
    long long int maxUtil(int l , int r){
      return maxST(1,1,n,l,r);
    }
};
struct LazySegmentTreeSum{
    const int ZERO  = 0;
    int MINN=-1*1e9;
    int n;
    vector<long long int> tree;
    vector<long long int> lazyUpdate;
    vector<bool> shouldUpdate;
    LazySegmentTreeSum(int noOfElements){
        n=noOfElements;
        tree.assign(4*n,0);
        lazyUpdate.assign(4*n,0);
        shouldUpdate.assign(4*n,false);
    }
    
    void buildInner(const vector<long long int>&a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } 
        else {
            int tm = (tl + tr) / 2;
            buildInner(a, v*2, tl, tm);
            buildInner(a, v*2+1, tm+1, tr);
            tree[v] = tree[2*v]+tree[2*v+1]; 
        }
    }

    //propagate chages for SUM 
    void propagate(int node, int l, int r)
	{
		if(l != r)
		{
			shouldUpdate[node*2] = true;
			shouldUpdate[node*2 + 1] = true;
			lazyUpdate[node*2] += lazyUpdate[node];
			lazyUpdate[node*2 + 1] += lazyUpdate[node]; 
		}
		tree[node] += (r-l+1)*lazyUpdate[node];
		lazyUpdate[node] = 0;
		shouldUpdate[node] = false;
	}

    long long int sum(int node, int L, int R, int i, int j)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return ZERO; // min  INF, max - -INF....
		if(i<=L && R<=j)return tree[node];
		int M = (L + R)/2;
		long long int left=sum(node*2, L, M, i, j);
		long long int right=sum (node*2 + 1, M + 1, R, i, j);
		return left +right;
	}
    //Range Update
    void Update(int node, int L, int R, int i, int j, int mn)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return;
		if(i<=L && R<=j)
		{
			shouldUpdate[node] = true;
			lazyUpdate[node] = mn;
			propagate(node, L, R);
			return;
		}
		int M = (L + R)/2;
		Update(node*2, L, M, i, j, mn);
		Update(node*2 + 1, M + 1, R, i, j, mn);
		tree[node]=tree[node*2]+ tree[node*2 + 1];
	}

    //Utility functions for smaller Function call and clean code in Main 
    void updateUtil(int l,int r, int value) {
        Update(1,1,n,l,r,value);
    }
    long long int sumUtil(int l , int r){
      return sum(1,1,n,l,r);
    }
    void build(const vector<long long int> &v){
        this->buildInner(v,1,0,v.size()-1);
    }
};

int main(){
    vector<long long int> x{1,4,2,3,5,6};
    LazySegmentTreeSum stsum(6);
    stsum.build(x);
    
    //cout<<stmax.maxUtil(1,4)<<" "<<stmin.minUtil(1,4)<<endl;
    stsum.updateUtil(1,3,4);
    // stmax.updateUtil(2,6,-1);
    // stmin.updateUtil(1,3,4);
    // stmin.updateUtil(2,6,-1);
    forn(i,6){
        cout<<stsum.sumUtil(i+1,i+1)<<" ";
    }
    cout<<endl;
    forn(i,5){
        cout<<stsum.sumUtil(i+1,i+2)<<" ";
    }
}