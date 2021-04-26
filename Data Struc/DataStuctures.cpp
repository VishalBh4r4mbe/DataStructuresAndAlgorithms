#include <bits/stdc++.h>
using namespace std;

namespace DataStructures{
    //Overload Operators in case of Custom Structs
    //1-indexed everything 
    template <typename T> struct SegmentTree{
        int MAXN=1e9;
        int n;
        vector<T> tree;
        SegmentTree(int noOfElements){
            n=noOfElements;
            tree = vector<T>(4*n);
        }
        //change merge as per use
        T merge(T &a,T &b){
            return a+b;
        }
        void build(const vector<T>&a, int v, int tl, int tr) {
            if (tl == tr) {
                tree[v] = a[tl];
            } 
            else {
                int tm = (tl + tr) / 2;
                build(a, v*2, tl, tm);
                build(a, v*2+1, tm+1, tr);
                tree[v] = merge(tree[2*v],tree[2*v+1]); 
            }
        }
        T sumUtil(int l, int r){
            return sum(1,1,n,l,r);
        }
        T sum(int v, int tl, int tr, int l, int r) {
            if (l > r) 
                return 0;
            if (l == tl && r == tr) {
                return tree[v];
            }
            int tm = (tl + tr) / 2;
            return sum(v*2, tl, tm, l, min(r, tm))+sum(v*2+1, tm+1, tr, max(l, tm+1), r);
        }
        T minUtil(int l , int r){
        return minST(1,1,n,l,r);
        }
        T minST(int v, int tl, int tr, int l, int r) {
            if (l > r) 
                return 0; // change in case of Sum as for sum , it needs to be 0 similar for MAX
            if (l == tl && r == tr) {
                return tree[v];
            }
            int tm = (tl + tr) / 2;
            return merge(minST(v*2, tl, tm, l, min(r, tm)),minST(v*2+1, tm+1, tr, max(l, tm+1), r));
        }
        void updateUtil(int position, T value) {
            update(1,1,n,position,value);
        }
        void update(int v, int tl, int tr, int pos, T new_val) {
            if (tl == tr) {
                tree[v] = new_val;
            } 
            else {
                int tm = (tl + tr) / 2;
                if (pos <= tm)
                    update(v*2, tl, tm, pos, new_val);
                else
                    update(v*2+1, tm+1, tr, pos, new_val);
                tree[v] = merge(tree[v*2],tree[v*2+1]);
            }
        }
    };
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
        
        void build(const vector<long long int>&a, int v, int tl, int tr) {
            if (tl == tr) {
                tree[v] = a[tl];
            } 
            else {
                int tm = (tl + tr) / 2;
                build(a, v*2, tl, tm);
                build(a, v*2+1, tm+1, tr);
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
            if(j<L || i>R)return ZERO;
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
    };
}
using namespace DataStructures;

int main(){
    SegmentTree<int> idk(6);
    vector<int> offo{1,2,4,5,6,3};
    idk.build(offo,1,0,5);
    cout<<idk.sumUtil(1,5);
}