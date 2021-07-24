//NAIVE DSU

struct DSU{
    vector<int> parent;
    DSU(int n){
        parent.resize(n);
        iota(parent.begin(),parent.end(),0);
    }    
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            parent[b] = a;
    }
};
    

//Union by Rank/Size
struct DSU{
    vector<int> parent;
    vector<int> size;
    DSU(int n){
        parent.resize(n);
        iota(parent.begin(),parent.end(),0);
        size.resize(n);
        size.assign(n,1);
    }    
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};


//RANK
void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}