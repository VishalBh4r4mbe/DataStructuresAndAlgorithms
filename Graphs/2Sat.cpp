#include "bits/stdc++.h"
using namespace std;
class TwoSat{ 
    private:
        int n;
        vector<vector<int>> graph,ReverseGraph;
        vector<int> ComponentID,TopologicalOrder;
        vector<bool> visited,assignment;
        void addEdge(int u,int v){graph[u].push_back(v);ReverseGraph[v].push_back(u);}
    public:
        TwoSat(){}
        TwoSat(int _n):n(_n){
            graph.assign(2*n,vector<int>());
            ReverseGraph.assign(2*n,vector<int>());
            ComponentID.assign(2*n,0);
            visited.assign(2*n,false);
            assignment.assign(2*n,false);
        }   
        vector<bool> getAnswer(){
            return assignment;
        }
        void OR(int a,bool valuea,int b, bool valueb){
            addEdge(a+(valuea?n:0),b+(valueb?0:n));
            addEdge(b+(valueb?n:0),a+(valuea?0:n));
        }
        void XOR(int a,bool valuea,int b, bool valueb){
            OR(a,valuea,b,valueb);      
            OR(a,!valuea,b,!valueb);
        }
        //AND Rather means Same value than Both have to be true.
        void AND(int a, bool valuea,int b, bool valueb){
            XOR(a,!valuea,b,valueb);
        }
        void topo(int node){
            visited[node]=true;
            for(auto to: graph[node]){
                if(!visited[to]){
                    topo(to);
                }
            }
            TopologicalOrder.push_back(node);
        }
        void getStronglyConnectedComponents(int node,int SCC_ID){
            visited[node]=true;
            ComponentID[node]=SCC_ID;
            for(auto to: ReverseGraph[node]){
                if(!visited[to]){
                    getStronglyConnectedComponents(to,SCC_ID);
                }
            }
        }
        bool isSatisfiable(){
            visited.assign(visited.size(),false);
            for(int i=0;i<2*n;i++)if(!visited[i])topo(i);
            visited.assign(visited.size(),false);
            reverse(TopologicalOrder.begin(),TopologicalOrder.end());
            int curSCC_ID=0;
            for(auto node: TopologicalOrder){
                if(!visited[node]){
                    getStronglyConnectedComponents(node,curSCC_ID);
                    curSCC_ID++;
                }
            }
            for(int i=0;i<n;i++){
                if(ComponentID[i]==ComponentID[i+n])return false;
                else{
                    assignment[i] = ComponentID[i]>ComponentID[i+n];
                }
            }
            return true;
        }


};

int main(){
    TwoSat ts(2);
    // ts.AND(0,true,0,true);
    // ts.AND(1,true,1,true);
    cout<<boolalpha<<ts.isSatisfiable()<<endl;
    for(auto x:ts.getAnswer()){
        cout<<x<<" ";
    }
}