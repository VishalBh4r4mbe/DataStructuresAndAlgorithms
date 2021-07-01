#include <bits/stdc++.h>
using namespace std;
//pass Update_id for namesake like just in case you use a different class for Updates
template<class Node, class Update,class MakeNode,class CombineNodes,class ApplyUpdate,class ComposeUpdates = std::nullptr_t>
struct LazySegmentTree{
    public:
    
    LazySegmentTree(int noOfElements,const MakeNode _make_node,const CombineNodes _combine_nodes,const ApplyUpdate _apply_update,const ComposeUpdates _compose_updates,const Node _node_id,const Update _update_id):n(noOfElements),make_node(_make_node),combine_nodes(_combine_nodes),node_id(node_id),apply_update(_apply_update),compose_updates(_compose_updates){
        tree.assign(4*n,node_id); // init to Node_id in main struct..............
        lazyUpdate.resize(4*n);
        shouldUpdate.assign(4*n,false);
    }
    void buildInner(const vector<Node>&a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } 
        else {
            int tm = (tl + tr) / 2;
            buildInner(a, v*2, tl, tm);
            buildInner(a, v*2+1, tm+1, tr);
            tree[v] = combine_nodes(tree[2*v],tree[2*v+1]); 
        }
    }

    //propagate chages for SUM 

    void propagate(int node, int l, int r)
	{
		if(l != r)
		{
			shouldUpdate[node*2] = true;
			shouldUpdate[node*2 + 1] = true;
			lazyUpdate[node*2]  = compose_updates(lazyUpdate[node*2],lazyUpdate[node],l,r);
			lazyUpdate[node*2 + 1] =compose_updates(lazyUpdate[node*2+1],lazyUpdate[node],l,r); 
		}
		tree[node] =  apply_update(tree[node],lazyUpdate[node],l,r);
		lazyUpdate[node] = 0;
		shouldUpdate[node] = false;
	}

    Node query(int node, int L, int R, int i, int j)
	{
		if(shouldUpdate[node])propagate(node, L, R);
		if(j<L || i>R)return node_id; // min  INF, max - -INF....
		if(i<=L && R<=j)return tree[node];
		int M = (L + R)/2;
		Node left=query(node*2, L, M, i, j);
		Node right=query (node*2 + 1, M + 1, R, i, j);
		return combine_nodes(left,right);
	}
    //Range Update
    void update(int node, int L, int R, int i, int j, Update mn)
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
		tree[node]=combine_nodes(tree[node*2], tree[node*2 + 1]);
	}

    //Utility functions for smaller Function call and clean code in Main 
    void update(int l,int r, Update value) {
        update(1,1,n,l,r,value);
    }
    Node query(int l , int r){
      return query(1,1,n,l,r);
    }
    void build(const vector<Node> &v){
        this->buildInner(v,1,0,v.size()-1);
    }
    private:
    const int ZERO  = 0;
    int n;
    const MakeNode make_node;
    const ApplyUpdate apply_update;
    const Node node_id;
    const CombineNodes combine_nodes;
    const ComposeUpdates compose_updates;
    vector<Node> tree;
    vector<Update> lazyUpdate;
    vector<bool> shouldUpdate;
};


int main(){
    
    //freopen( "output.txt", "w", stdout );
    freopen( "error.txt", "w", stderr );
    using Node = int;
    using Base = int;
    const Node _node_id = 0;
    const Base _base_id = 0;
    auto make_node = [&](const Node& val){
        return Node(val);
    };
    auto combine = [&](const Node& a, const Node& b){
        return a+b;
    };
    // auto combine_different = [&](const Base&a, const Base&b){
    //     return a+b;
    // };
    using Update =int;

    const Update update_id = 0;
    //for sum you will need a property -> size;
    auto apply_update = [&](const Node& nd , const Update& u,int l,int r){
        return nd + u*(r-l+1);
    };
    auto compose_updates= [&](const Node& nd , const Update& u,int l,int r){
        return nd+u;
    };
    
    vector<int> arr{3,12,3,5,6,1,55,7,98,5,3}; 
    LazySegmentTree st(arr.size(),make_node,combine,apply_update,compose_updates,_node_id,update_id);
    st.build(arr);
    st.update(1,4,3);
    for(auto i=1;i<=arr.size();i++)cout<<st.query(i,i)<<" ";
    cout<<endl;
    cout<<st.query(1,2);
    //cout<<endl<<st.is_lazy<<endl;

}