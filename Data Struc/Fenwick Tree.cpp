#include <bits/stdc++.h>
using namespace std;
struct FenwickTree {
    vector<int> bit;int n;
    FenwickTree(int n) {this->n = n;bit.assign(n, 0);}
    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)add(i, a[i]);}
    int sum(int r) {int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)ret += bit[r];
        return ret;}
    int sum(int l, int r) {return sum(r) - sum(l - 1);}
    void range_add(int l, int r, int val) {add(l, val);add(r + 1, -val);}//ONLY TO BE USED WHEN THERE ARE POINT QUERIES
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))bit[idx] += delta;}};

struct FenwickTreeMin {
    vector<int> bit;int n;const int INF = (int)1e9;
    FenwickTreeMin(int n) {this->n = n;bit.assign(n, INF);}
    FenwickTreeMin(vector<int> a) : FenwickTreeMin(a.size()) {
        for (size_t i = 0; i < a.size(); i++)update(i, a[i]);}
    int getmin(int r) {int ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)ret = min(ret, bit[r]);
        return ret;}
    void update(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))bit[idx] = min(bit[idx], val);}};

struct FenwickTree2D{
    vector<vector<int>> bit;int n, m;
    FenwickTree2D(int n,int m){this->n=n;this->m=m;
        for(int i=0;i<n;i++){bit.assign(n,vector<int> (m,0));}}
    FenwickTree2D(vector<vector<int>> a): FenwickTree2D(a.size(),a[0].size()){
        for(int i=0;i<n;i++){for(int j =0;j<m;j++){add(i,j,a[i][j]);}}}
    int sum(int x, int y) {int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)for (int j = y; j >= 0; j = (j & (j + 1)) - 1)ret += bit[i][j];
        return ret;}
    void add(int x, int y, int delta) {for (int i = x; i < n; i = i | (i + 1))for (int j = y; j < m; j = j | (j + 1))bit[i][j] += delta;}};
//Just in case
struct FenwickTreeOneBasedIndexing { 
    vector<int> bit; int n;
    FenwickTreeOneBasedIndexing(int n) {this->n = n + 1;bit.assign(n + 1, 0);}
    FenwickTreeOneBasedIndexing(vector<int> a): FenwickTreeOneBasedIndexing(a.size()) {for (size_t i = 0; i < a.size(); i++)add(i, a[i]);}
    int sum(int idx) {int ret = 0;for (++idx; idx > 0; idx -= idx & -idx)ret += bit[idx];
        return ret;}
    int sum(int l, int r) {return sum(r) - sum(l - 1);}
    void add(int idx, int delta) {for (++idx; idx < n; idx += idx & -idx)bit[idx] += delta;}};