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
int main(){

}