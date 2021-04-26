vector<int> order; //Stores the Topological Order
bool toposort(int n) //Returns 1 if there exists a toposort, 0 if there is a cycle
{   
    order.clear();
    queue<int> q;
    vector<int> indeg(n , 0);
    for(int i = 0 ; i < n; i++)
        //assume graph g has the input
        for(auto &it:g[i])
            indeg[it]++;
    for(int i = 0; i < n; i++)
    {
        if(!indeg[i])
            q.push(i);
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for(auto &v:g[u])
        {
            indeg[v]--;
            if(!indeg[v])
                q.push(v);
        }
    }
    return (order.size() == n);
    
}