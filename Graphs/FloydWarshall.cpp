#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> dist;
vector<vector<int>> graphMatrix;
void FloydWarshall(){
    const INF   = 1e9+7;
    dist = graphMatrix;

    for(int k = 0; k <graphMatrix.size();k++){
        for(int i = 0; i <graphMatrix.size();i++){
            for(int j = 0; j <graphMatrix.size();j++){
                if(dist[i][j]>dist[i][k]+dist[k][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                }
            }
        }
    }
}

//with path retrieval function;
vector<vector<int>> next;
void FloydWarshallWithPathRetrieval(){
    const INF   = 1e9+7;
    dist = graphMatrix;
    next.resize(graphMatrix.resize(),vector<int>(graphMatrix.size(),-1));
    for(int i= 0; i < graphMatrix.size(); i++){
        for(int j=0;j<graphMatrix.size();j++){
            if(graphMatrix[i][j]!=INF){
                next[i][j]=j;
            }
        }
    }
    for(int i= 0; i < graphMatrix.size(); i++){
        next[i][i]=i;
    }

    for(int k = 0; k <graphMatrix.size();k++){
        for(int i = 0; i <graphMatrix.size();i++){
            for(int j = 0; j <graphMatrix.size();j++){
                if(dist[i][j]>dist[i][k]+dist[k][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                    next[i][j]  = next[i][k];
                }
            }
        }
    }
}


vector<int> retrievePath(int u ,int v){
    if(next[u][v]==-1)return vector<int>(1,-1);
    vector<int> path(1,u);
    else{
        while(u!=v){
            u = next[u][v];
            path.push_back(u);
        }
    }
    return path ;
}