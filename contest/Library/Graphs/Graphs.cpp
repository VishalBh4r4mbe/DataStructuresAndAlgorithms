//Diameter
#include<bits/stdc++.h> 
using namespace std; 
 
vector<vector<int> > g; 
int n; 
 
pair<int, int> bfs(int root){ 
    vector<int> dist(n+1, 0); 
    dist[root] = 1; 
    queue<int> q; 
    q.push(root); 
    while(!q.empty()){ 
        int curr = q.front(); 
        for(auto it : g[curr]){ 
            if(dist[it] != 0){ 
                continue; 
            } 
            q.push(it); 
            dist[it] = dist[curr] + 1; 
        } 
        q.pop(); 
    } 
    int mx = INT_MIN, vertex = -1; 
    for(int i=1 ; i<=n ; i++){ 
        if(mx < dist[i]){ 
            mx = dist[i]; 
            vertex = i; 
        } 
    } 
    return make_pair(mx, vertex); 
} 
 
int diameter(int root){ 
    pair<int, int> p1 = bfs(root), p2; 
    p2 = bfs(p1.second); 
    return p2.first; 
} 
 
//Centers
/*1) EVERY DIAMETER PASSES THROUGH A CENTER
2) THERE CAN BE AT MOST 2 CENTERS IN A TREE
*/
vector<int> treeCenter(){
    int n=g.size()
    vector<int> degree(n,0);
    vector<int> leaves;
    for(int i=0;i<n;i++){
        if(degree[i]==0||degree[i]==1){
            leaves.push_back(i);
            degree[i]=0;
        }
    }
    int count = leaves.size();
    while(count<n){
        vector<int> new_leaves;
        for(int node:leaves){
            for(int neighbour in g[node]){
                degree[neighbour]= degree[neighbour]-1;
                if(degree[neighbour]==1){
                    new_leaves.push_back(neighbour);
                }
            }
        }
        count+=new_leaves.size();
        leaves=new_leaves;
    }
    return leaves;
}




//Centroid
//Node when removed minimises the largest remaining component
    
//At most 2
//Size [n/2]
vector<int> Centroid(){
    
}