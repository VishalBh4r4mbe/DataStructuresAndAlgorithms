/* 
    KEEP IN MIND THAT SPARSE MATRIX ONLY SUPPORTS IDEMPOTENT FUNCTIONS
*/
#include <bits/stdc++.h>
using namespace std;
// define a function f() to be performed
// long long int MAXN = 1e5;
// int f(int x, int y=0){
//     //function 
//     //for ex. return(x+y);
//     return __gcd(x,y);
// }
// int log[MAXN+1];
// log[1] = 0;
// for (int i = 2; i <= MAXN; i++)
//     log[i] = log[i/2] + 1;
// }
// //Pre-Computation
// K = log[n];
// long long int st[MAXN+1][K+1];
// for (int i = 0; i < N; i++)
//     st[i][0] = f(array[i]);

// for (int j = 1; j <= K; j++)
//     for (int i = 0; i + (1 << j) <= N; i++)
//         st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);


// //If a minimum query , we can do computation in O(1) time , as you can just ask for a range min in overlap .
// int j = log[R - L + 1];
// int minimum = min(st[L][j], st[R - (1 << j) + 1][j]);

// //*****************************************************************//
//int sum(int L , int R){
//     long long sum = 0;
//     for (int j = K; j >= 0; j--) {
//         if ((1 << j) <= R - L + 1) {
//             sum += st[L][j];
//             L += 1 << j;
//         }
//     }
// }
class SparseMatrix {
    private:
    vector<vector<int>> st;
    int N, K;
    vector<int> logs;
    int combine(int l, int r=0){
        if(r==0)return l;
        return l+r;
    }
    public:
    SparseMatrix(int n){
        N=n;
        logs.resize(n+1);
        logs[1] = 0;
        for (int i = 2; i <= N; i++)
            logs[i] = logs[i/2] + 1;
        
        K = logs[n];
        st.assign(n+1,vector<int>(K+1));
    }
    SparseMatrix(vector<int> const &a){
        N = a.size();
        logs.resize(N+1);
        logs[1] = 0;
        for (int i = 2; i <= N; i++)
            logs[i] = logs[i/2] + 1;
        K = logs[N];
        st.assign(N+1,vector<int>(K+1,0));
        for (int i = 0; i < N; i++)st[i][0] = combine(a[i]);
        for (int j = 1; j <= K; j++)for (int i = 0; i + (1 << j) <= N; i++)st[i][j] = combine(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
    }
    void build(vector<int> const &a){
        
       for (int i = 0; i < N; i++)st[i][0] = combine(a[i]);
        for (int j = 1; j <= K; j++)for (int i = 0; i + (1 << j) <= N; i++)st[i][j] = combine(st[i][j-1], st[i + (1 << (j - 1))][j - 1]); 
    }
    int query(int l, int r){
        if(l>r){
            return combine(query(l,N-1),query(0,r));
        }
        long long ans = 0;
        for (int j = K; j >= 0; j--) {
            if ((1 << j) <= r - l + 1) {
                ans = combine(ans,st[l][j]);
                l += 1 << j;
            }
        }
        return ans;   
    }
    int fastQuery(int l, int r) {
        if(l>r){
            return combine(fastQuery(l,N-1),fastQuery(0,r));
        }

        int j = logs[r - l + 1];
        int ans = combine(st[l][j], st[r - (1 << j) + 1][j]);
        return ans;
    }
};
int main(){
    vector<int> arr{1,2,3,4,55,6};
    SparseMatrix sm(arr);
    cout<<sm.query(5,1)<<endl;
}