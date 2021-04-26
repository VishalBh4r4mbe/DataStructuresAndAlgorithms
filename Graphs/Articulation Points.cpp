#include <bits/stdc++.h>
using namespace std;
vector<int> ti(N),low(N);
vector<bool> vis(N);
vector<vector<int>> graph(N);
int timer=0;
vector<bool> polar_bear(N);

void dfs(int node,int parent=-1){
    vis[node]=true;
    ti[node] = low[node]=timer++;
    int children=0;
    for(auto to : graph[node]){
        if(to==parent){
            continue;
        }
        if(vnodeis[to]){
            low[node]= min(low[node],ti[to]);
        }
        else{
            dfs(to,v);
            low[node]=min(low[node],low[to]);
            if(low[to]>=ti[v]&&parent!=-1){
                polar_bear[node]=true;               
            }
            ++children;
        }

    }
    if(p==-1 && children>1){
        polar_bear[node]=true;
    }
}
int main(){
    //Input graph
    //dfs beb
    forn(){
        if(!vis[i]){
            dfs(i);
        }
    }
}