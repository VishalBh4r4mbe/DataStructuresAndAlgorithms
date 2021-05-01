#include<bits/stdc++.h>
using namespace std;
vector<vector<pair<int,int>>> graph;
vector<int> primMST(int source){
    priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>>>pq;
    vector<bool> inMST(graph.size(),false);
    vector<int> parent(graph.size(),-1),key(graph.size(),1e9 + 7);
    pq.push({0,source});
    key[source]=0;
    while(!pq.empty()){
        auto  p = pq.top();
        pq.pop();
        inMST[p.second]=true;
        for(auto x: graph[p.second]){
            if(!inMST[x.first]&&key[x.first]>x.second){
                key[x.first]=x.second;
                pq.push({x.second,x.first});
                parent[x.first] = p.second;
            }
        }
    }
    return parent;
}

int main(){
    cout<<"IDK";
}