#include <bits/stdc++.h>
using namespace std;
vector<bool> vis(N);
vector<int> ti(N),low(N);
vector<vector<int>> graph(N);
set<pair<int,int>> bridge;
int timer=0;
void dfs(int node, int parent=-2){
    vis[node]=true;
    ti[node]= low[node]=timer++;
    for(int to : graph[node]){
        if(to==parent){
            continue;
        }
        if(vis[to]){
            low[node]=min(low[node],ti[to]);

        }
        else{
            dfs(to,v);
            low[node]= min(low[node],low[to]);
            if(low[to]>ti[node]){
                bridge.insert({node,to});
            }
        }

    }
}

//Online 

class BridgeFinder {
    vector<int> par,dsu_2ecc, dsu_cc,dsu_cc_size;
    int bridges,lcaIteration;
    vector<int> lastVisit;
    BridgeFinder(int n){
        par.assign(n,-1);
        dsu_2ecc.resize(n);
        dsu_cc.resize(n);
        dsu_cc_size.assign(n,1);
        lcaIteration=0;
        lastVisit.assign(n,0);
        iota(dsu_cc.begin(),dsu_cc.end(),0);
        iota(dsu_2ecc.begin(),dsu_2ecc.end(),0);
        bridges=0;
    }
    find2ecc(int node){
        if(node==-1)return -1;
        return dsu_2ecc[node]==node?node:dsu_2ecc[node]=find2ecc(dsu_2ecc[node]);
    }
    findcc(int node){
        node = find2ecc(node);
        return dsu_cc[node]==node?node:dsu_cc[node]=findcc(dsu_cc[node]);
    }
    void make_root(int v) {
        v = find2ecc(v);
        int root = v;
        int child = -1;
        while (v != -1) {
            int p = find2ecc(par[v]);
            par[v] = child;
            dsu_cc[v] = root;
            child = v;
            v = p;
        }
    dsu_cc_size[root] = dsu_cc_size[child];
    }
    void merge_path(int a ,int b) {
        ++lcaIteration;
        vector<int> path_a,path_b;
        int lca=-1;
        while(lca==-1){
            if(a!=-1){
                a = find2ecc(a);
                path_a.push_back(a);
                if(lastVisit[a]==lcaIteration){
                    lca=a;
                    break;
                }
                lastVisit[a]=lcaIteration;
                a = par[a];
            }
            if(b!=-1){
                b = find2ecc(b);
                path_b.push_back(b);
                if(lastVisit[b]==lcaIteration){
                    lca=b;
                    break;
                }
                lastVisit[b]=lcaIteration;
                b = par[b];
            }

        }
        for (int v : path_a) {
            dsu_2ecc[v] = lca;
            if (v == lca)
                break;
            --bridges;
        }
        for (int v : path_b) {
            dsu_2ecc[v] = lca;
            if (v == lca)
                break;
            --bridges;  
        }
    }
    void add_edge(int a, int b) {
        a = find2ecc(a);
        b = find2ecc(b);
        if (a == b)
            return;

        int ca = findcc(a);
        int cb = findcc(b);

        if (ca != cb) {
            ++bridges;
            if (dsu_cc_size[ca] > dsu_cc_size[cb]) {
                swap(a, b);
                swap(ca, cb);
            }
            make_root(a);
            par[a] = dsu_cc[a] = b;
            dsu_cc_size[cb] += dsu_cc_size[a];
        } else {
            merge_path(a, b);
        }
    }



};
int main(){

}