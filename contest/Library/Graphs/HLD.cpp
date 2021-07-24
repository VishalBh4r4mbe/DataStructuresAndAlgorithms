#include <bits/stdc++.h>
using namespace std;
class LazySegmentTree{
    private:
    
    long long int node_id;
    int n;
    vector<long long int> tree;
    vector<long long int> lazyUpdate;
    vector<bool> shouldUpdate;
    long long int apply_update(long long int node,long long int u,int l, int r){
        return node+u*(r-l+1);
    }
    long long int compose_update(long long int child,long long int node,int l,int r){
        return child + node;
    }

    long long int combine(long long int left,long long int right){
        return max(left,right);
    }
    /** **/
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
    long long int query(int node, int L, int R, int i, int j)
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

class HLD{
    using graph = std::vector<std::vector<int>>;
    static constexpr bool vals_in_edges = false;
    private:

    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    LazySegmentTree tree;
    int timer;
    long long int id_node;
    long long int combine(long long int x, long long int y){
        return max(x,y);
    }
    public:
        HLD(const graph &G,int root,vector<long long int> vertex_vals,long long int _id_node):N(G.size()),tree(N,_id_node){
            id_node = _id_node;
            g=G;
            //Init
            par.assign(N,-1);
            start.resize(N);
            timer = 0;
            depth.resize(N);
            sz.resize(N);
            in_time.resize(N);
            dfs_sz(root);
            start[root] =root;
            dfs_hld(root);
            //Segtree init
            vector<long long int> perm(N);
            for (int i = 0; i < N; ++i) perm[in_time[i]] = vertex_vals[i];
            tree.build(perm);
        }
        bool is_anc(int u, int v) {
            return in_time[u] <= in_time[v] && in_time[u] + sz[u] >= in_time[v];
        }
    
        void update_path(int u, int v, long long int val) {
            for (; start[u] != start[v]; v = par[start[v]]) {
                if (depth[start[u]] > depth[start[v]]) swap(u, v);
                tree.update(in_time[start[v]]+1, in_time[v] + 1, val);
            }
            if (depth[u] > depth[v]) swap(u, v);
            tree.update(in_time[u]+1 + vals_in_edges, in_time[v] + 1, val);
        }
        long long int query_path(int u, int v) {
            long long int ans = id_node;
            for (; start[u] != start[v]; v = par[start[v]]) {
                if (depth[start[u]] > depth[start[v]]) swap(u, v);
                ans = combine(ans, tree.query(in_time[start[v]]+1, in_time[v]+1));
            }
            if (depth[u] > depth[v]) swap(u, v);
            return combine(ans,tree.query(in_time[u] + vals_in_edges+1, in_time[v]+1));
        }
        long long int query_vertex(int u) { return tree.query(in_time[u]+1,in_time[u] + 1); }
        void update_vertex(int u, long long int val) { tree.set(in_time[u]+1, val); }
        void update_subtree(int u, long long int val) {
            int l = in_time[u] + vals_in_edges+1;
            int r = in_time[u] + sz[u];
            tree.update(l, r, val);
        }
        long long int query_subtree(int u) {
            return tree.query(in_time[u] + vals_in_edges+1, in_time[u] + sz[u]);
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
};
int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    int q;
    cin>>q;
 
    vector<long long int> vals(n);
    for(int i=0;i<n;i++){
        cin>>vals[i];
    }
 
    vector<vector<int>> graph(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    HLD hld(graph,0,vals,0);
    //cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int s,x;
            cin>>s>>x;
            hld.update_vertex(s-1,x);
        }
        else{
            int u,v;
            cin>>u>>v;
            cout<<hld.query_path(u-1,v-1)<<endl;
        }
    }

}s