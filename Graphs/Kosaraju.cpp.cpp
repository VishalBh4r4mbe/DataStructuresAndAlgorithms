#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph(N);
vector<vector<int>> GraphRev(N);
vector<int> component;
//dfs1 to make the stack
stack<int> st;
bool vis[N]={false};
void dfs1(int node){
    vis[node]=true;
    for(auto x: graph[node]){
        if(!vis[x]){
            dfs(x);
        }
        st.push(node);
    }
}
//dfs2 to build the connected components
void dfs2(int node){
    vis[node]=true;
    component.push_back(node);
    for(auto x: graphRev[node]){
        if(!vis[x])dfs2(x);
    }
}
int main(){
    //Input for the graph and then Kosaraju(dfs1 for every node, clear vis to false then dfs2 for every node)
    for(int i=0;i<n;i++){
        if(!vis[i])dfs1(i);
    }
    while(!st.empty())
        int i= st.top();
        if(!vis[i]){
            dfs2(i);
            //bakwaas with next component
            component.clear();
        }
        st.pop();
    }
}