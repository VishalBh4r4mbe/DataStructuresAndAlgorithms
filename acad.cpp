#include <bits/stdc++.h>
using namespace std;
class SegmentTree{
    public:
    int n;
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
    void prangeAdd(int l,int r, int value) {for (l += n, r += n; l < r; l >>= 1, r >>= 1) {if (l&1) tree[l++] += value;if (r&1) tree[--r] += value;}}       //Use to see the increase for a particulare element
    int pQuery(int l){long long int res = 0;for (l += n;l > 0; l >>= 1) res += tree[l];return res;}

};
class HLD{
    using graph = std::vector<std::vector<int>>;
    static constexpr bool vals_in_edges = false;
    private:

    int N;
    graph g;
    std::vector<int> par, start, depth, sz, in_time;
    SegmentTree tree;
    int timer;
    long long int id_node;
    long long int combine(long long int x, long long int y){
        return max(x,y);
    }
    public:
        HLD(const graph &G,int root,vector<long long int> vertex_vals,long long int _id_node):N(G.size()),tree(N){
            id_node = _id_node;
            g=G;
            par.assign(N,-1);
            start.resize(N);
            timer = 0;
            depth.resize(N);
            sz.resize(N);
            in_time.resize(N);
            dfs_sz(root);
            start[root] =root;
            dfs_hld(root);
            vector<long long int> perm(N);
            for (int i = 0; i < N; ++i) perm[in_time[i]] = vertex_vals[i];
            tree.build(perm);
        }
        bool is_anc(int u, int v) {
        return in_time[u] <= in_time[v] && in_time[u] + sz[u] >= in_time[v];
        }
    
        // void update_path(int u, int v, long long int val) {
        //     for (; start[u] != start[v]; v = par[start[v]]) {
        //         if (depth[start[u]] > depth[start[v]]) swap(u, v);
        //         tree.update(in_time[start[v]]+1, in_time[v] + 1, val);
        //     }
        //     if (depth[u] > depth[v]) swap(u, v);
        //     tree.update(in_time[u]+1 + vals_in_edges, in_time[v] + 1, val);
        // }
        long long int query_path(int u, int v) {
            long long int ans = id_node;
            for (; start[u] != start[v]; v = par[start[v]]) {
                if (depth[start[u]] > depth[start[v]]) swap(u, v);
                ans = combine(ans, tree.query(in_time[start[v]], in_time[v]+1));
            }
            if (depth[u] > depth[v]) swap(u, v);
            return combine(ans,tree.query(in_time[u] + vals_in_edges, in_time[v]+1));
        }
        //long long int query_vertex(int u) { retusrn tree.query(in_time[u]+1,in_time[u] + 1); }
        void update_vertex(int u, long long int val) { tree.set(in_time[u], val); }
        // void update_subtree(int u, long long int val) {
        //     int l = in_time[u] + vals_in_edges+1;
        //     int r = in_time[u] + sz[u];
        //     tree.update(l, r, val);
        // }
        // long long int query_subtree(int u) {
        //     return tree.query(in_time[u] + vals_in_edges+1, in_time[u] + sz[u]);
        // }
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

}