#include <bits/stdc++.h>
using namespace std;
template <class Node,class Update>
struct LazySegmentTree{
    private:
    
    Node node_id;
    int n;
    vector<Node> tree;
    vector<Update> lazyUpdate;
    vector<bool> shouldUpdate;
    Node apply_update(Node node,Update u,int l, int r){
        return node + u*1LL*(r-l+1);
    }
    Update compose_update(Update child,Update node,int l,int r){
        return child+node;
    }

    Node combine(Node left,Node right){
        return left+right;
    }
    /**1 indexed **/
    public:
    LazySegmentTree(int noOfElements,Node _node_id){
        n=noOfElements;
        node_id=_node_id;    
        tree.assign(4*n,node_id);
        lazyUpdate.assign(4*n,0);
        shouldUpdate.assign(4*n,false);
    }
    void build(const vector<Node>&a, int v, int tl, int tr) {
        if (tl == tr)tree[v] = a[tl];
        else {
            int tm = tl + (tr - tl)/2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            tree[v] = combine(tree[2*v],tree[2*v+1]); 
        }
    }
    void propagate(int node, int l, int r)
	{
		if(l != r)
		{
			shouldUpdate[node*2] = true;
			shouldUpdate[node*2 + 1] = true;
			lazyUpdate[node*2] = compose_update(lazyUpdate[node*2],lazyUpdate[node],l,r);
			lazyUpdate[node*2 + 1] += compose_update(lazyUpdate[node*2 + 1 ],lazyUpdate[node],l,r);
		}
		tree[node] = apply_update(tree[node],lazyUpdate[node],l,r);
		lazyUpdate[node] = 0;
		shouldUpdate[node] = false;
	}
    Node query(int node, int L, int R, int i, int j)   // l-> tl, r->tr, i->ql, j->qr
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return node_id; // min  INF, max - -INF....
		if(i<=L && R<=j)return tree[node];
		int M = (L + R)/2;
		Node left=query(node*2, L, M, i, j);
		Node right=query(node*2 + 1, M + 1, R, i, j);
		return combine(left,right);
	}
    //Range Update
    void update(int node, int L, int R, int i, int j, int mn)
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
		update(node*2, L, M, i, j, mn);
		update(node*2 + 1, M + 1, R, i, j, mn);
		tree[node]=combine(tree[node*2],tree[node*2 + 1]);
	}
    
    //Utility functions for smaller Function call and clean code in Main 
    void update(int l,int r, Update value) {
        update(1,1,n,l,r,value);
    }
    Node query(int l , int r){
      return query(1,1,n,l,r);
    }
    void build(const vector<Node> &v){
        this->build(v,1,0,v.size()-1);
    }
    void set(int node ,Node val){
        Node x = this->query(node,node);
        Update delta = val-x;
        this->update(node,node,delta);
    }
};

int main(){
    
    
    vector<long long int> arr{5, 3 ,4 ,5, 9, 2, 1, 9, 8, 1 }; 
    LazySegmentTree<long long int , long long int> st(arr.size(),0LL);
    st.build(arr);
    st.update(1,3,2);
    st.set(1,-2);
    for(auto i=1;i<=arr.size();i++)cout<<st.query(i,i)<<" ";
    cout<<endl<<st.query(1,2);
    // cout<<endl;
    // cout<<st.query(1,2);

}

#include <bits/stdc++.h>
using namespace std;
struct LazySegmentTree{
    private:
    
    long long int node_id;
    int n;
    vector<long long int> tree;
    vector<long long int> lazyUpdate;
    vector<bool> shouldUpdate;
    long long int apply_update(long long int node,long long int u,int l, int r){
        return node + u*1LL*(r-l+1);
    }
    long long int compose_update(long long int child,long long int node,int l,int r){
        return child+node;
    }

    long long int combine(long long int left,long long int right){
        return left+right;
    }
    /**1 indexed **/
    public:
    LazySegmentTree(int noOfElements,long long int _node_id){
        n=noOfElements;
        node_id=_node_id;    
        tree.assign(4*n,node_id);
        lazyUpdate.assign(4*n,0);
        shouldUpdate.assign(4*n,false);
    }
    void build(const vector<long long int>&a, int v, int tl, int tr) {
        if (tl == tr)tree[v] = a[tl];
        else {
            int tm = tl + (tr - tl)/2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            tree[v] = combine(tree[2*v],tree[2*v+1];) 
        }
    }
    void propagate(int node, int l, int r)
	{
		if(l != r)
		{
			shouldUpdate[node*2] = true;
			shouldUpdate[node*2 + 1] = true;
			lazyUpdate[node*2] = compose_update(lazyUpdate[node*2],lazyUpdate[node],l,r);
			lazyUpdate[node*2 + 1] += compose_update(lazyUpdate[node*2 + 1 ],lazyUpdate[node],l,r);
		}
		tree[node] = apply_update(tree[node],lazyUpdate[node],l,r);
		lazyUpdate[node] = 0;
		shouldUpdate[node] = false;
	}
    long long int query(int node, int L, int R, int i, int j)   // l-> tl, r->tr, i->ql, j->qr
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return node_id; // min  INF, max - -INF....
		if(i<=L && R<=j)return tree[node];
		int M = (L + R)/2;
		long long int left=query(node*2, L, M, i, j);
		long long int right=query(node*2 + 1, M + 1, R, i, j);
		return combine(left,right);
	}
    //Range Update
    void update(int node, int L, int R, int i, int j, int mn)
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
		update(node*2, L, M, i, j, mn);
		update(node*2 + 1, M + 1, R, i, j, mn);
		tree[node]=combine(tree[node*2],tree[node*2 + 1]);
	}
    
    //Utility functions for smaller Function call and clean code in Main 
    void update(int l,int r, int value) {
        update(1,1,n,l,r,value);
    }
    long long int query(int l , int r){
      return query(1,1,n,l,r);
    }
    void build(const vector<long long int> &v){
        this->build(v,1,0,v.size()-1);
    }
    void set(int node ,int val){
        long long int x = this->query(node,node);
        long long int delta = val-x;
        this->update(node,node,delta);
    }
};

int main(){
    
    
    vector<long long int> arr{5, 3 ,4 ,5, 9, 2, 1, 9, 8, 1 }; 
    LazySegmentTree st(arr.size(),0LL);
    st.build(arr);
    for(auto i=1;i<=arr.size();i++)cout<<st.query(i,i)<<" ";
    // cout<<endl;
    // cout<<st.query(1,2);

}