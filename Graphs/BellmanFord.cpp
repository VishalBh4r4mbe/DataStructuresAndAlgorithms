#include <bits/stdc++.h>
using namespace std;
vector<int> dist;
vector<int> parent;
vector<pair<int,pair<int,int> > > graph;
const int INF = 1e9+7;
int n,m;
void BellmanFord(int source){
    dist.resize(n,INF);
    dist[source]=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++){
            if(dist[graph[j].first]!=INF){
                dist[graph[j].second.first]=min(dist[graph[j].second.first],dist[graph[j].first]+graph[j].second.second);
            }   
        }
    }

}

void BellmanFordWithPathRetrieval(int source){
    dist.resize(n,INF);
    dist[source]=0;
    parent.resize(n,-1);
    for(int i=0;i<n-1;i++){
        for(int j=0;j<graph.size();j++){
            if(dist[graph[j].first]!=INF&&dist[graph[j].second.first]>dist[graph[j].first]+graph[j].second.second){
                dist[graph[j].second.first]=min(dist[graph[j].second.first],dist[graph[j].first]+graph[j].second.second);
                parent[graph[j].second.first]=graph[j].first;
            }     
        }
    }
    
}
vector<int> NegativeCycle;
bool checkNegativeCycle(){
    x = -1;
    for (int j=0; j<graph.size(); ++j)if (dist[graph.first] < INF)if (dist[graph[j].second.first] > dist[graph[j].first] + graph[j].second.second)x = e[j].b;
    if(x==-1)return false;
    else{
        int start = x;
        for(int i=0;i<n;i++){
            start = parent[start];
        }
        int cur = start;
        while(!(cur==start&&NegativeCycle.size()>1)){
            NegativeCycle.push_back(cur);
            cur = parent[cur];
        }
        reverse(NegativeCycle.begin(),NegativeCycle.end());
        return true;
        
    }           
}

vector<int> path(int v){
    vector<int> ans;
    while(v!=-1){
        ans.push_back(v);
        v = parent[v];
    }   
    reverse(ans.begin(),ans.end()); 
    return ans;
}
int main(){
    cin>>n>>m;
    graph.resize(m);
    for(int i=0;i<m;i++){
        cin>>graph[i].first;
        cin>>graph[i].second.first;
        cin>>graph[i].second.second;
    }
    BellmanFordWithPathRetrieval(0);
    vector<int> pathi = path(3);
    for(auto x:pathi){
        cout<<x<<" ";
    }
}