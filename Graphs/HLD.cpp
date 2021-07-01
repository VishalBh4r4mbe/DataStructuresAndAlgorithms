#include "bits/stdc++.h"




using namespace std;
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
    void set(int node,int value){
        int cur = this->query(node,node);
        int delta = value-cur;
        this->update(node,node,delta);
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
template <class Node,class Update,class MakeNode,class CombineNodes,class CombineDifferent,class ApplyUpdate,class ComposeUpdates = std::nullptr_t>
class HLD{
    using graph = std::vector<std::vector<int>>;
    static constexpr bool vals_in_edges = false; // make true if vals in edges
    public:
    HLD(const graph& G, int root, std::vector<Node>& vertex_vals,const Node& _id_node,const MakeNode& _make_node,const CombineNodes& _combine,const CombineDifferent& _combine_different,const Update& _id_update,const ApplyUpdate& _apply_update,const ComposeUpdates& _compose_updates = nullptr): N(G.size()),g(G),par(N),start(N),sz(N),in_time(N),combine(_combine), combine_different(_combine_different),id_node(_id_node),tree(N,_make_node,_combine,_apply_update,_compose_updates,_id_node,_id_update){
        par[root]=-1;
        timer =1;
        dfs_sz(root);
        start[root]=root;
        dfs_hld(root);
        vector<Node> perm(N);
        for (int i = 0; i < N; ++i) perm[in_time[i]] = vertex_vals[i];
        tree.build(perm);
    }
    bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] >= in_time[v];
    }
    void update_path(int u, int v, Update val) {
        for (; start[u] != start[v]; v = par[start[v]]) {
            if (depth[start[u]] > depth[start[v]]) swap(u, v);
            tree.update(in_time[start[v]], in_time[v], val);
        }
        if (depth[u] > depth[v]) swap(u, v);
        tree.update(in_time[u] + vals_in_edges, in_time[v], val);
    }
    Node query_path(int u, int v) {
        Node ans = id_node;
        for (; start[u] != start[v]; v = par[start[v]]) {
            if (depth[start[u]] > depth[start[v]]) swap(u, v);
            ans = combine(ans, tree.query(in_time[start[v]], in_time[v]));
        }
        if (depth[u] > depth[v]) swap(u, v);
        return combine(ans,
                       tree.query(in_time[u] + vals_in_edges, in_time[v]));
    }
    Node query_vertex(int u) { return tree.query(in_time[u],in_time[u]); }
    void update_vertex(int u, Update val) { tree.set(in_time[u], val); }
    void update_subtree(int u, Node val) {
        int l = in_time[u] + vals_in_edges;
        int r = in_time[u] + sz[u];
        tree.update(l, r, val);
    }
    Node query_subtree(int u) {
        return tree.query(in_time[u] + vals_in_edges, in_time[u] + sz[u]);
    }
    void dfs_sz(int u) {
        sz[u] = 1;
        for (auto& v : g[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            g[v].erase(find(begin(g[v]), end(g[v]), u));
            dfs_sz(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    void dfs_hld(int u) {
        in_time[u] = timer++;
        for (auto& v : g[u]) {
            start[v] = (v == g[u][0] ? start[u] : v);
            dfs_hld(v);
        }
    }
    int lca(int u, int v) {
        for (; start[u] != start[v]; v = par[start[v]])
            if (depth[start[u]] > depth[start[v]]) swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

   
    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    const CombineNodes combine;
    const CombineDifferent combine_different;
    const Node id_node;
    LazySegmentTree< Node, Update,MakeNode,CombineNodes,ApplyUpdate,ComposeUpdates>tree;
    int timer;
};

int main(){
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
    auto combine_different = [&](const Node &a, const Node &b){
        return a+b;
    };
    using Update =int;

    const Update update_id = 0;
    //for sum you will need a property -> size;
    auto apply_update = [&](const Node& nd , const Update& u,int l,int r){
        return nd + u*(r-l+1);
    };
    auto compose_updates= [&](const Node& nd , const Update& u,int l,int r){
        return nd+u;
    };
    int n;
    cin>>n;
    vector<vector<int>> graph(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> vals(n);
    for(int i=0;i<n;i++){
        cin>>vals[i];
    }

    HLD hld(graph,0,vals,_node_id,make_node,combine,combine_different,update_id,apply_update,compose_updates);
    for(auto x:hld.in_time){
        cout<<x<<" ";
    }
    cout<<hld.query_path(0,2);

}