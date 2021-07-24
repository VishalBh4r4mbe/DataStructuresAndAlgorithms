#include <bits/stdc++.h>
using namespace std;

int n,l;
vector<vector<int>> graph;
int timer=0;
vector<int> tin,tout;
vector<vector<int>> up;

void dfs(int cur, int parent=-1){
    tin[cur]=++timer;
    up[cur][0]=parent;
    for(int i=1;i<l;i++){
        up[cur][i]=up[up[cur][i-1]][i-1];
    }
    for(int u: graph[cur]){
        if(u!=parent){
            dfs(u,cur);
        }
    }
    tout[cur]=++timer;
}
bool ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v){
    if (ancestor(u, v))
        return u;
    if (ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void LCAPreprocessing(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}